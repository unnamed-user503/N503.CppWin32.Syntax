#pragma once

#include <N503/Syntax/Lexing/IsWhitespace.hpp>
#include <N503/Syntax/Lexing/Not.hpp>
#include <N503/Syntax/Scanning/DefaultScanner.hpp>
#include <N503/Syntax/TokenType.hpp>

namespace N503::Syntax::Scanning
{

    /// @brief
    using Whitespace = DefaultScanner<
        TokenType::Whitespace,
        Lexing::IsWhitespace,
        Lexing::IsWhitespace,
        Lexing::Not<Lexing::IsWhitespace>>;

} // namespace N503::Syntax::Scanning
