#pragma once

#include <N503/Syntax/Grammar/Definition.hpp>
#include <N503/Syntax/Production/Terminal.hpp>

namespace N503::Syntax::Grammar
{

    /// @brief 最小単位の文法パーツ (Atom) を生成する Factory です。
    /// @tparam TTrait Token が一致するか判定する述語クラス
    /// @return 最小単位を定義した Definition オブジェクト
    template <typename TTrait>
    [[nodiscard]]
    constexpr auto Atom() noexcept -> Definition<Production::Terminal<TTrait>>
    {
        return {};
    }

    /// @brief インスタンスを受け取って型を推論するオーバーロードです。
    /// @tparam TTrait Token が一致するか判定する述語クラス
    /// @return 最小単位を定義した Definition オブジェクト
    template <typename TTrait>
    [[nodiscard]]
    constexpr auto Atom(const TTrait&) noexcept
    {
        return Atom<TTrait>();
    }

} // namespace N503::Syntax::Grammar
