#pragma once

#include <N503/Syntax/Reader/Guard/ProgressGuard.hpp>
#include <N503/Syntax/Reader/Reader.hpp>
#include <N503/Syntax/Token.hpp>
#include <N503/Syntax/TokenType.hpp>
#include <optional>

namespace N503::Syntax::Scanning
{

    /// @brief 標準的な字句スキャン処理を定義するテンプレート構造体
    /// @tparam Type 生成されるトークンの種類（TokenType）
    /// @tparam THead 先頭文字の妥当性を判定する関数オブジェクト型
    /// @tparam TBody 2文字目以降の継続文字の妥当性を判定する関数オブジェクト型
    /// @tparam TSeparate トークンの区切り（終了条件）を判定する関数オブジェクト型
    template <TokenType Type, typename THead, typename TBody, typename TSeparate> struct DefaultScanner
    {
        /// @brief リーダーから特定のパターンを読み取り、トークンを抽出します
        /// @param reader 文字入力ストリーム
        /// @return トークンが抽出された場合は Token オブジェクト、失敗した場合は std::nullopt
        static auto Scan(Reader::CharacterReader& reader) -> std::optional<Token>
        {
            const auto startState = reader.GetState();

            // 1.Head の判定
            const auto head = reader.Peek();

            // 先頭文字が条件を満たさない場合は、即座に失敗として返す
            if (!head || !THead{}(*head, *head))
            {
                return std::nullopt;
            }
            else
            {
                reader.Advance();
            }

            // 継続文字（Body）の読み取りループ
            while (reader.CanRead())
            {
                // 無限ループ（位置が全く進まない状態）を監視するガードを配置
                auto progressGuard = Reader::Guard::ProgressGuard{ reader };

                // 2.Body の判定
                const auto current = reader.Peek();

                if (!current || !TBody{}(*current, *head))
                {
                    // 継続条件を満たさなくなった場合、ループを抜けてそこまでの範囲でトークン化する
                    break;
                }
                else
                {
                    reader.Advance();
                }

                // 3.Separate の判定
                const auto next = reader.Peek();

                if (next && TSeparate{}(*next, *head))
                {
                    // 明示的な区切り文字が現れた場合、ループを終了する
                    break;
                }

                // 4. Advance() が呼ばれていなければここで例外を投げ、無限解析を防止する
                progressGuard.Verify();
            }

            // 読み取り開始地点から現在の位置までのビューを使用してトークンを生成
            return Token{ .Type = Type, .Lexeme = reader.View(startState), .Position = startState.Position };
        }
    };

} // namespace N503::Syntax::Scanning
