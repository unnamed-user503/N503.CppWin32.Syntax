#pragma once

#include <N503/Syntax/Lexing/IsNumberBody.hpp>
#include <N503/Syntax/Lexing/IsNumberHead.hpp>
#include <N503/Syntax/Lexing/IsNumberSeparate.hpp>
#include <N503/Syntax/Scanning/DefaultScanner.hpp>
#include <N503/Syntax/TokenType.hpp>

namespace N503::Syntax::Scanning
{

    /// @brief
    using Number = DefaultScanner<TokenType::Number, Lexing::IsNumberHead, Lexing::IsNumberBody, Lexing::IsNumberSeparate>;

} // namespace N503::Syntax::Scanning
