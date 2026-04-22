#pragma once

#include <N503/Syntax/Grammar/Definition.hpp>
#include <N503/Syntax/Production/Deferred.hpp>

namespace N503::Syntax::Grammar
{

    /// @brief 遅延評価（再帰参照用）を行う Factory です。
    /// @details 相互参照や自己参照を含む文法を定義する際、実体の構築を遅延させるために使用します。
    /// @tparam T 最終的に参照する Production 型
    /// @param ppReal 構築後に実体化された Production へのポインタのポインタ
    /// @return 遅延評価を定義した Definition オブジェクト
    template <typename T>
    [[nodiscard]]
    constexpr auto Lazy(const T** ppReal) noexcept -> Definition<Production::Deferred<T>>
    {
        return { ppReal };
    }

} // namespace N503::Syntax::Grammar
