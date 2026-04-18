#pragma once

#include <span>
#include <string_view>
#include <vector>

namespace N503::Syntax
{

    /// @brief
    struct Token;

} // namespace N503::Syntax

namespace N503::Syntax::Reader
{

    /// @brief 文字入力ストリーム用のトレイト定義
    struct CharacterTraits
    {
        /// @brief 要素の型（文字）
        using ValueType = char;

        /// @brief ソースデータの型（文字列ビュー）
        using SourceType = std::string_view;

        /// @brief 切り出した範囲を示すビューの型（文字列ビュー）
        using ViewType = std::string_view;
    };

    /// @brief トークン入力ストリーム用のトレイト定義
    struct TokenTraits
    {
        /// @brief 要素の型（トークン構造体）
        using ValueType = Token;

        /// @brief ソースデータの型（トークンの動的配列）
        using SourceType = std::vector<Token>;

        /// @brief 切り出した範囲を示すビューの型（トークンの読み取り専用スパン）
        using ViewType = std::span<const Token>;
    };

} // namespace N503::Syntax::Reader
