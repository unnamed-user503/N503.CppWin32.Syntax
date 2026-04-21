#pragma once

#include <N503/Syntax/Grammar/Definition.hpp>
#include <N503/Syntax/Production/Maybe.hpp>

namespace N503::Syntax::Grammar
{

    /// @brief 0回または1回の出現 (Optional) を生成する Factory です。
    /// @tparam T Productionクラス (生身の型)
    /// @return 任意性を定義した Definition オブジェクト
    template <typename T>
    [[nodiscard]]
    constexpr auto Optional() noexcept -> Definition<Production::Maybe<T>>
    {
        return {};
    }

    /// @brief インスタンスを受け取り、0回または1回の出現を生成するオーバーロードです。
    /// @tparam T Productionクラス (生身の型)
    /// @return 任意性を定義した Definition オブジェクト
    template <typename T>
    [[nodiscard]]
    constexpr auto Optional(const T &) noexcept
    {
        return Optional<T>();
    }

} // namespace N503::Syntax::Grammar
