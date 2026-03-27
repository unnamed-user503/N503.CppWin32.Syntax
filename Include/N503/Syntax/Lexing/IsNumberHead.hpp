#pragma once

namespace N503::Syntax::Lexing
{

    /// @struct IsNumberHead
    /// @brief 数値リテラルの開始文字として妥当であるか判定する述語クラスです。
    struct IsNumberHead
    {
        /// @brief 数値の開始文字判定を行います。
        /// @param c 判定対象の文字
        /// @param char 第2引数（未使用）
        /// @return 数値リテラルの開始（0-9）であれば true
        [[nodiscard]]
        auto operator()(char c, char) const -> bool
        {
            return (c >= '0' && c <= '9');
        }
    };

} // namespace N503::Syntax::Lexing
