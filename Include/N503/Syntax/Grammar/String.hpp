#pragma once

#include <N503/Syntax/Grammar/Atom.hpp>
#include <N503/Syntax/Parsing/IsType.hpp>
#include <N503/Syntax/TokenType.hpp>

namespace N503::Syntax::Grammar
{

    /// @brief トークンが文字列リテラル（String）であるか判定する述語のエイリアスです。
    using IsString = Parsing::IsType<TokenType::String>;

    /// @brief
    inline constexpr auto String = Atom<IsString>();

} // namespace N503::Syntax::Grammar
