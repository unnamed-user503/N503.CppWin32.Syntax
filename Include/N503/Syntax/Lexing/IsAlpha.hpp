#pragma once

#include <cctype>

namespace N503::Syntax::Lexing
{

    /// @struct IsAlpha
    /// @brief 与えられた文字が英字（A-Z, a-z）であるか判定する述語クラスです。
    struct IsAlpha
    {
        /// @brief 英字判定を行います。
        /// @param c 判定対象の文字
        /// @param char 第2引数（未使用）
        /// @return 英字であれば true
        [[nodiscard]]
        auto operator()(char c, char) const noexcept -> bool
        {
            return std::isalpha(static_cast<unsigned char>(c)) != 0;
        }
    };

} // namespace N503::Syntax::Lexing
