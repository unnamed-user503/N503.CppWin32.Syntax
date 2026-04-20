#pragma once

#include <N503/Syntax/Grammar/Definition.hpp>
#include <N503/Syntax/Production/Expect.hpp>

namespace N503::Syntax::Grammar
{

    /// @brief 必須要素（失敗は許されない文法要素）を定義する Factory です。
    /// @details この要素のパースに失敗した場合、バックトラックせずにエラーとして報告されます。
    /// @tparam T Productionクラス (生身の型)
    /// @return 必須要素を定義した Definition オブジェクト
    template <typename T>
    [[nodiscard]]
    constexpr auto Required() noexcept -> Definition<Production::Expect<T>>
    {
        return {};
    }

    /// @brief インスタンスを受け取り、必須要素を生成するオーバーロードです。
    /// @tparam T Productionクラス (生身の型)
    /// @return 必須要素を定義した Definition オブジェクト
    template <typename T>
    [[nodiscard]]
    constexpr auto Required(const T&) noexcept
    {
        return Required<T>();
    }

} // namespace N503::Syntax::Grammar
