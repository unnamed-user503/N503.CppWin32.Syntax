#pragma once

namespace N503::Syntax::Lexing
{

    /// @struct Never
    /// @brief 常に偽を返す述語（Predicate）クラスです。
    /// @details 任意の文字の組み合わせに対して常に false を返します。
    struct Never
    {
        /// @brief 条件判定を行います。
        /// @param char 判定対象の文字（未使用）
        /// @param char 判定対象の文字（未使用）
        /// @return 常に false
        [[nodiscard]]
        constexpr auto operator()(char, char) const noexcept -> bool
        {
            return false;
        }
    };

} // namespace N503::Syntax::Lexing
