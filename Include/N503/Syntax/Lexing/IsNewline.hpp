#pragma once

namespace N503::Syntax::Lexing
{

    /// @struct IsNewline
    /// @brief 与えられた文字が改行文字（LF または CR）であるか判定する述語クラスです。
    struct IsNewline
    {
        /// @brief 改行文字判定を行います。
        /// @param c 判定対象の文字
        /// @param char 第2引数（未使用）
        /// @return 改行文字（'\n' または '\r'）であれば true
        [[nodiscard]]
        constexpr auto operator()(char c, char) const noexcept -> bool
        {
            return c == '\n' || c == '\r';
        }
    };

} // namespace N503::Syntax::Lexing
