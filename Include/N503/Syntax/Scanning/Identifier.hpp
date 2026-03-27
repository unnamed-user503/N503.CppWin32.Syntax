#pragma once

#include <N503/Syntax/Lexing/IsAlnum.hpp>
#include <N503/Syntax/Lexing/IsAlpha.hpp>
#include <N503/Syntax/Lexing/Not.hpp>
#include <N503/Syntax/Scanning/DefaultScanner.hpp>
#include <N503/Syntax/TokenType.hpp>

namespace N503::Syntax::Scanning
{

    /// @brief
    using Identifier = DefaultScanner<TokenType::Identifier, Lexing::IsAlpha, Lexing::IsAlnum, Lexing::Not<Lexing::IsAlnum>>;

} // namespace N503::Syntax::Scanning
