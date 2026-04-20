#pragma once

namespace N503::Syntax::Lexing
{

    /// @struct IsQuote
    /// @brief 与えられた文字が引用符（" または '）であるか判定する述語クラスです。
    struct IsQuote
    {
        /// @brief 引用符判定を行います。
        /// @param c 判定対象の文字
        /// @param char 第2引数（未使用）
        /// @return ダブルクォートまたはシングルクォートであれば true
        [[nodiscard]]
        constexpr auto operator()(char c, char) const noexcept -> bool
        {
            return c == '"' || c == '\'';
        }
    };

} // namespace N503::Syntax::Lexing
