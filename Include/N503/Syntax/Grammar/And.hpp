#pragma once

#include <N503/Syntax/Grammar/Definition.hpp>
#include <N503/Syntax/NodeType.hpp>
#include <N503/Syntax/Production/Sequence.hpp>

namespace N503::Syntax::Grammar
{

    /// @brief Aの次にBが続く (And / Sequence) を生成する Factory です。
    /// @tparam T 左辺のProduction型
    /// @tparam U 右辺のProduction型
    /// @return AとBの連結を定義した Definition オブジェクト
    template <typename T, typename U>
    [[nodiscard]]
    constexpr auto And() noexcept -> Definition<Production::Sequence<NodeType::Unknown, T, U>>
    {
        return {};
    }

    /// @brief インスタンスを受け取り、Aの次にBが続く定義を生成するオーバーロードです。
    /// @tparam T 左辺のProduction型
    /// @tparam U 右辺のProduction型
    /// @return AとBの連結を定義した Definition オブジェクト
    template <typename T, typename U>
    [[nodiscard]]
    constexpr auto And(const T&, const U&) noexcept
    {
        return And<T, U>();
    }

} // namespace N503::Syntax::Grammar
