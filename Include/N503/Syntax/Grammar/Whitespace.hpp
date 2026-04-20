#pragma once

#include <N503/Syntax/Grammar/Atom.hpp>
#include <N503/Syntax/Parsing/IsType.hpp>
#include <N503/Syntax/TokenType.hpp>

namespace N503::Syntax::Grammar
{

    /// @brief トークンが空白（Whitespace）であるか判定する述語のエイリアスです。
    using IsWhitespace = Parsing::IsType<TokenType::Whitespace>;

    /// @brief
    inline constexpr auto Whitespace = Atom<IsWhitespace>();

} // namespace N503::Syntax::Grammar
