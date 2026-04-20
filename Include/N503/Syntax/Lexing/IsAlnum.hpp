#pragma once

#include <cctype>

namespace N503::Syntax::Lexing
{

    /// @struct IsAlnum
    /// @brief 与えられた文字が英数字であるか判定する述語クラスです。
    struct IsAlnum
    {
        /// @brief 英数字判定を行います。
        /// @param c 判定対象の文字
        /// @param char 判定対象の文字（未使用）
        /// @return 英数字であれば true
        [[nodiscard]]
        auto operator()(char c, char) const noexcept -> bool
        {
            return std::isalnum(static_cast<unsigned char>(c)) != 0;
        }
    };

} // namespace N503::Syntax::Lexing
