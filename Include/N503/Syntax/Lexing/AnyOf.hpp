#pragma once

#include <N503/Syntax/Lexing/LexerTrait.hpp>

namespace N503::Syntax::Lexing
{

    /// @brief 複数の述語のいずれか（OR）を満たすか判定する述語クラスです。
    /// @tparam Ts 判定に使用する LexerTrait を満たす述語群
    template <LexerTrait... Ts> struct AnyOf
    {
        /// @brief 指定されたいずれかの述語が真を返すか判定します。
        /// @param c 判定対象の文字
        /// @param h 補助的な文字（Lookahead等）
        /// @return いずれかが真であれば true、すべて偽であれば false
        [[nodiscard]]
        auto operator()(char c, char h) const noexcept -> bool
        {
            return (Ts{}(c, h) || ...);
        }
    };

} // namespace N503::Syntax::Lexing
