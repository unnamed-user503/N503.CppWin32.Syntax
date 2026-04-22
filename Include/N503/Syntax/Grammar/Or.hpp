#pragma once

#include <N503/Syntax/Grammar/Definition.hpp>
#include <N503/Syntax/Production/Alternative.hpp>

namespace N503::Syntax::Grammar
{

    /// @brief A または B (Or / Alternative) を生成する Factory です。
    /// @tparam T 左辺の Production 型
    /// @tparam U 右辺の Production 型
    /// @return いずれかの文法にマッチする選択肢を定義した Definition オブジェクト
    template <typename T, typename U>
    [[nodiscard]]
    constexpr auto Or() noexcept -> Definition<Production::Alternative<T, U>>
    {
        return {};
    }

    /// @brief インスタンスを受け取り、A または B の選択肢を生成するオーバーロードです。
    /// @tparam T 左辺の Production 型
    /// @tparam U 右辺の Production 型
    /// @return いずれかの文法にマッチする選択肢を定義した Definition オブジェクト
    template <typename T, typename U>
    [[nodiscard]]
    constexpr auto Or(const T&, const U&) noexcept
    {
        return Or<T, U>();
    }

} // namespace N503::Syntax::Grammar
