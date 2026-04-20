#pragma once

#include <N503/Syntax/Reader/Guard/ProgressGuard.hpp>
#include <N503/Syntax/Reader/Reader.hpp>
#include <N503/Syntax/Token.hpp>
#include <N503/Syntax/TokenType.hpp>
#include <optional>

namespace N503::Syntax::Scanning
{

    /// @brief 開始文字と終了文字で囲まれた範囲（文字列リテラルや括弧など）をスキャンするテンプレート構造体
    /// @tparam TType 生成されるトークンの種類（TokenType）
    /// @tparam THead 開始文字の妥当性を判定する関数オブジェクト型
    /// @tparam TContent 内部に含まれる文字の妥当性を判定する関数オブジェクト型
    /// @tparam TEnd 終了文字（閉じ文字）の妥当性を判定する関数オブジェクト型
    template <TokenType TType, typename THead, typename TContent, typename TEnd> struct EnclosureScanner
    {
        /// @brief リーダーから囲み構造を読み取り、トークンを抽出します
        /// @param reader 文字入力ストリーム
        /// @return トークンが抽出された場合は Token オブジェクト、開始文字が適合しない場合は std::nullopt
        [[nodiscard]]
        static auto Scan(Reader::CharacterReader& reader) -> std::optional<Token>
        {
            const auto startState = reader.GetState();
            const auto head = reader.Peek();

            // 1. 開始文字の判定
            // 開始文字が条件に合致しない場合は、このスキャナーの対象外として nullopt を返す
            if (!head || !THead{}(*head, *head))
            {
                return std::nullopt;
            }

            // 開始文字を消費してスキャンを確定させる
            reader.Advance();

            // 2. 内部コンテンツおよび終了判定ループ
            while (reader.CanRead())
            {
                // 無限ループ防止用のガード
                auto progressGuard = Reader::Guard::ProgressGuard{ reader };

                const auto current = reader.Peek();
                if (!current)
                {
                    break;
                }

                // 終了判定（閉じ文字）を優先的にチェック
                if (TEnd{}(*current, *head))
                {
                    reader.Advance(); // 閉じ文字を消費
                    break;            // 正常に囲みが閉じたためループ終了
                }

                // 内部コンテンツとして許可されている文字か判定
                if (TContent{}(*current, *head))
                {
                    reader.Advance();
                }
                else
                {
                    // 予期しない文字（例：文字列中の改行など）が現れた場合、
                    // 文法エラーの可能性があるが、そこまでをトークンとして区切る
                    break;
                }

                // 読み取り位置が進んでいない場合は例外を投げる
                progressGuard.Verify();
            }

            // 少なくとも開始文字（Head）は消費しているため、不完全な囲みであっても
            // 読み取れた範囲を一つのトークンとして生成し、後続の解析（Parser等）に委ねる
            return Token{ .Type = TType, .Lexeme = reader.View(startState), .Position = startState.Position };
        }
    };

} // namespace N503::Syntax::Scanning
