#pragma once

namespace N503::Syntax::Lexing
{

    /// @struct IsSameAsHead
    /// @brief 対象の文字が、比較対象の文字（開始文字等）と一致するか判定する述語クラスです。
    struct IsSameAsHead
    {
        /// @brief 文字の一致判定を行います。
        /// @param c 判定対象の文字
        /// @param h 比較対象の文字（Head文字など）
        /// @return 2つの文字が一致すれば true
        [[nodiscard]]
        constexpr auto operator()(char c, char h) const noexcept -> bool
        {
            return c == h;
        }
    };

} // namespace N503::Syntax::Lexing
