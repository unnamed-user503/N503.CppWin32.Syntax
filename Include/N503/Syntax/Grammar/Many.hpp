#pragma once

#include <N503/Syntax/Grammar/Definition.hpp>
#include <N503/Syntax/Production/Repetition.hpp>

namespace N503::Syntax::Grammar
{

    /// @brief 1回以上の繰り返し (Many) を生成する Factory です。
    /// @tparam T Productionクラス (生身の型)
    /// @return 1回以上の繰り返しを定義した Definition オブジェクト
    template <typename T>
    [[nodiscard]]
    constexpr auto Many() noexcept -> Definition<Production::Repetition<T, 1>>
    {
        return {};
    }

    /// @brief インスタンスを受け取り、1回以上の繰り返しを生成するオーバーロードです。
    /// @tparam T Productionクラス (生身の型)
    /// @return 1回以上の繰り返しを定義した Definition オブジェクト
    template <typename T>
    [[nodiscard]]
    constexpr auto Many(const T&) noexcept
    {
        return Many<T>();
    }

} // namespace N503::Syntax::Grammar
