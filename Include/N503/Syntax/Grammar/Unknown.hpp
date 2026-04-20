#pragma once

#include <N503/Syntax/Grammar/Atom.hpp>
#include <N503/Syntax/Parsing/IsType.hpp>
#include <N503/Syntax/TokenType.hpp>

namespace N503::Syntax::Grammar
{

    /// @brief トークンが未知の種別（Unknown）であるか判定する述語のエイリアスです。
    using IsUnknown = Parsing::IsType<TokenType::Unknown>;

    /// @brief
    inline constexpr auto Unknown = Atom<IsUnknown>();

} // namespace N503::Syntax::Grammar
