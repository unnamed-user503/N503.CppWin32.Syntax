#pragma once

#include <N503/Syntax/Lexing/LexerTrait.hpp>

namespace N503::Syntax::Lexing
{

    /// @brief 指定した述語の判定結果を反転（NOT）させる述語クラスです。
    /// @tparam T 反転対象となる LexerTrait を満たす述語型
    template <LexerTrait T> struct Not
    {
        /// @brief 述語の否定判定を行います。
        /// @param c 判定対象の文字
        /// @param h 補助的な文字（ルックアヘッドなど）
        /// @return 元の述語が偽を返せば true、真を返せば false
        [[nodiscard]]
        auto operator()(char c, char h) const noexcept -> bool
        {
            return !T{}(c, h);
        }
    };

} // namespace N503::Syntax::Lexing
