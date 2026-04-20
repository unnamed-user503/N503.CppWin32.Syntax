#pragma once

#include <N503/Syntax/Grammar/Atom.hpp>
#include <N503/Syntax/Parsing/IsType.hpp>
#include <N503/Syntax/TokenType.hpp>

namespace N503::Syntax::Grammar
{

    /// @brief トークンが識別子（Identifier）であるか判定する述語のエイリアスです。
    using IsIdentifier = Parsing::IsType<TokenType::Identifier>;

    /// @brief
    inline constexpr auto Identifier = Atom<IsIdentifier>();

} // namespace N503::Syntax::Grammar
