#pragma once

#include <N503/Syntax/Lexing/IsQuote.hpp>
#include <N503/Syntax/Lexing/Not.hpp>
#include <N503/Syntax/Scanning/EnclosureScanner.hpp>
#include <N503/Syntax/TokenType.hpp>

namespace N503::Syntax::Scanning
{

    /// @brief
    using String = EnclosureScanner<TokenType::String, Lexing::IsQuote, Lexing::Not<Lexing::IsQuote>, Lexing::IsQuote>;

} // namespace N503::Syntax::Scanning
