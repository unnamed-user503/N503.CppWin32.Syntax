#pragma once

#include <N503/Syntax/Grammar/Atom.hpp>
#include <N503/Syntax/Parsing/IsLexeme.hpp>

namespace N503::Syntax::Grammar
{

    /// @brief
    inline constexpr auto NotEquals = Atom<Parsing::IsLexeme<"!=">>();

} // namespace N503::Syntax::Grammar
