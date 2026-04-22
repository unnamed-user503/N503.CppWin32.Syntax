#pragma once

#include <N503/Syntax/Grammar/Definition.hpp>
#include <N503/Syntax/Production/Repetition.hpp>

namespace N503::Syntax::Grammar
{

    /// @brief 0回以上の繰り返し (Any) を生成する Factory です。
    /// @tparam T Productionクラス (生身の型)
    /// @return 0回以上の繰り返しを定義した Definition オブジェクト
    template <typename T>
    [[nodiscard]]
    constexpr auto Any() noexcept -> Definition<Production::Repetition<T, 0>>
    {
        return {};
    }

    /// @brief インスタンスを受け取り、0回以上の繰り返しを生成するオーバーロードです。
    /// @tparam T Productionクラス (生身の型)
    /// @return 0回以上の繰り返しを定義した Definition オブジェクト
    template <typename T>
    [[nodiscard]]
    constexpr auto Any(const T&) noexcept
    {
        return Any<T>();
    }

} // namespace N503::Syntax::Grammar
