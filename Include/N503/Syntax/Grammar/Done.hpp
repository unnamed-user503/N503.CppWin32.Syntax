#pragma once

#include <N503/Syntax/Grammar/Atom.hpp>
#include <N503/Syntax/Parsing/IsType.hpp>
#include <N503/Syntax/TokenType.hpp>

namespace N503::Syntax::Grammar
{

    /// @brief トークンリストの終端（Done）であるか判定する述語のエイリアスです。
    using IsDone = Parsing::IsType<TokenType::Done>;

    /// @brief
    inline constexpr auto Done = Atom<IsDone>();

} // namespace N503::Syntax::Grammar
