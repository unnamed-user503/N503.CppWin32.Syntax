#pragma once

#include <N503/Syntax/Grammar/Atom.hpp>
#include <N503/Syntax/Parsing/IsLexeme.hpp>

namespace N503::Syntax::Grammar
{

    /// @brief
    template <Parsing::FixedString TString> inline constexpr auto Lexeme = Atom<Parsing::IsLexeme<TString>>();

} // namespace N503::Syntax::Grammar
