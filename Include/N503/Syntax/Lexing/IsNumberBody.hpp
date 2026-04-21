#pragma once

namespace N503::Syntax::Lexing
{

    /// @struct IsNumberBody
    /// @brief 数値リテラル（整数、16進数、小数）を構成する文字であるか判定する述語クラスです。
    struct IsNumberBody
    {
        /// @brief 数値の構成要素判定を行います。
        /// @param c 判定対象の文字
        /// @param char 第2引数（未使用）
        /// @return 数値リテラルの一部として妥当な文字であれば true
        [[nodiscard]]
        auto operator()(char c, char) const -> bool
        {
            return (c >= '0' && c <= '9') || (c >= 'a' && c <= 'f') || (c >= 'A' && c <= 'F') ||
                   (c == 'x' || c == 'X') || (c == '.');
        }
    };

} // namespace N503::Syntax::Lexing
