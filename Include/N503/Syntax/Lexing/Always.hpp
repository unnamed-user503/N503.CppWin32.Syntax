#pragma once

namespace N503::Syntax::Lexing
{

    /// @struct Always
    /// @brief 常に真を返す述語（Predicate）クラスです。
    /// @details 任意の文字の組み合わせに対して常に true を返します。
    struct Always
    {
        /// @brief 条件判定を行います。
        /// @param char 判定対象の文字（未使用）
        /// @param char 判定対象の文字（未使用）
        /// @return 常に true
        [[nodiscard]]
        constexpr auto operator()(char, char) const noexcept -> bool
        {
            return true;
        }
    };

} // namespace N503::Syntax::Lexing
