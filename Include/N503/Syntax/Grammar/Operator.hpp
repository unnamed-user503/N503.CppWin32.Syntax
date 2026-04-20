#pragma once

#include <N503/Syntax/Grammar/Atom.hpp>
#include <N503/Syntax/Parsing/IsType.hpp>
#include <N503/Syntax/TokenType.hpp>

namespace N503::Syntax::Grammar
{

    /// @brief トークンが演算子（Operator）であるか判定する述語のエイリアスです。
    using IsOperator = Parsing::IsType<TokenType::Operator>;

    /// @brief
    inline constexpr auto Operator = Atom<IsOperator>();

} // namespace N503::Syntax::Grammar
