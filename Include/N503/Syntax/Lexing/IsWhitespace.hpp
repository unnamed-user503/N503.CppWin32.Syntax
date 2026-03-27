#pragma once

#include <cctype>

namespace N503::Syntax::Lexing
{

    /// @struct IsWhitespace
    /// @brief 与えられた文字が空白文字（スペース、タブ、改行、垂直タブ、送り、復帰）であるか判定する述語クラスです。
    struct IsWhitespace
    {
        /// @brief 空白文字判定を行います。
        /// @param c 判定対象の文字
        /// @param char 第2引数（未使用）
        /// @return 空白文字であれば true
        [[nodiscard]]
        auto operator()(char c, char) const noexcept -> bool
        {
            return std::isspace(static_cast<unsigned char>(c)) != 0;
        }
    };

} // namespace N503::Syntax::Lexing
