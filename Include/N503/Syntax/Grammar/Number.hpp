#pragma once

#include <N503/Syntax/Grammar/Atom.hpp>
#include <N503/Syntax/Parsing/IsType.hpp>
#include <N503/Syntax/TokenType.hpp>

namespace N503::Syntax::Grammar
{

    /// @brief トークンが数値リテラル（Number）であるか判定する述語のエイリアスです。
    using IsNumber = Parsing::IsType<TokenType::Number>;

    /// @brief
    inline constexpr auto Number = Atom<IsNumber>();

} // namespace N503::Syntax::Grammar
