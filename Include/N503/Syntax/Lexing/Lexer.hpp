#pragma once

#include <N503/Diagnostics.hpp>
#include <N503/Syntax/Reader/Reader.hpp>
#include <N503/Syntax/Token.hpp>
#include <N503/Syntax/TokenType.hpp>
#include <optional>
#include <string_view>
#include <utility>
#include <vector>

namespace N503::Syntax::Lexing
{

    /// @class Lexer
    /// @brief 複数のスキャンルールを束ねて字句解析を実行するエンジン・クラスです。
    /// @tparam TRules 適用するスキャナールールの可変長引数（記述順に優先される）
    template <typename... TRules> struct Lexer final
    {
        /// @brief ソースコードをスキャンしてトークン列に変換します。
        /// @param source 入力文字列（ソースコード）
        /// @param sink エラーや警告を記録するための診断シンク
        /// @return 抽出されたトークンのリスト
        [[nodiscard]]
        auto Tokenize(std::string_view source, Diagnostics::Sink& sink) const -> std::vector<Token>
        {
            Reader::CharacterReader reader{ source };
            std::vector<Token> tokens;

            // リーダーが終端に達するまで繰り返しスキャンを試行する
            while (reader.CanRead())
            {
                std::optional<Token> result;

                // C++20: ジェネリックラムダに対するテンプレート引数の明示と畳み込み式 (|| ...)
                // 可変長引数 TRules に含まれる各スキャナーの Scan メソッドを順番に実行する。
                // いずれかの T::Scan が値を返した時点で短絡評価により以降のスキャンはスキップされる。
                (void)((result = [&]<typename T>()
                {
                    return T::Scan(reader);
                }.template operator()<TRules>()) || ...);

                if (result)
                {
                    // TokenTypeがNoneであれば結果を連結しない
                    if (result->Type == TokenType::None)
                    {
                        continue;
                    }

                    // 適合するルールが見つかった場合、トークンをリストに追加
                    tokens.push_back(std::move(*result));
                }
                else
                {
                    // どのルール（識別子、数値、演算子等）にも適合しない場合のフォールバック
                    // 解析不能な文字として1文字消費し、Unknown トークンとして記録する
                    const auto state = reader.GetState();
                    reader.Advance();
                    tokens.push_back(Token{ .Type = TokenType::Unknown, .Lexeme = reader.View(state), .Position = state.Position });
                }
            }

            return tokens;
        }
    };

} // namespace N503::Syntax::Lexing
