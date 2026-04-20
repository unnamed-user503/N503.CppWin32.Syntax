#pragma once

#include <N503/Syntax/Grammar/Atom.hpp>
#include <N503/Syntax/Parsing/IsType.hpp>
#include <N503/Syntax/TokenType.hpp>

namespace N503::Syntax::Grammar
{

    /// @brief
    template <TokenType TTokenType> inline constexpr auto Type = Atom<Parsing::IsType<TTokenType>>();

} // namespace N503::Syntax::Grammar
