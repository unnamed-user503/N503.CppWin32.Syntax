#pragma once

#include <N503/Syntax/Lexing/Always.hpp>
#include <N503/Syntax/Lexing/AnyOf.hpp>
#include <N503/Syntax/Lexing/IsAlnum.hpp>
#include <N503/Syntax/Lexing/IsQuote.hpp>
#include <N503/Syntax/Lexing/IsWhitespace.hpp>
#include <N503/Syntax/Lexing/Never.hpp>
#include <N503/Syntax/Lexing/Not.hpp>
#include <N503/Syntax/Scanning/DefaultScanner.hpp>
#include <N503/Syntax/TokenType.hpp>

namespace N503::Syntax::Scanning
{

    /// @brief
    using Operator = DefaultScanner<TokenType::Operator, Lexing::Not<Lexing::AnyOf<Lexing::IsAlnum, Lexing::IsWhitespace, Lexing::IsQuote>>, Lexing::Never, Lexing::Always>;

} // namespace N503::Syntax::Scanning
