#pragma once

#include <cctype>

namespace N503::Syntax::Lexing
{

    /// @struct IsDigit
    /// @brief 与えられた文字が数字（0-9）であるか判定する述語クラスです。
    struct IsDigit
    {
        /// @brief 数字判定を行います。
        /// @param c 判定対象の文字
        /// @param char 第2引数（未使用）
        /// @return 数字であれば true
        [[nodiscard]]
        auto operator()(char c, char) const noexcept -> bool
        {
            return std::isdigit(static_cast<unsigned char>(c)) != 0;
        }
    };

} // namespace N503::Syntax::Lexing
