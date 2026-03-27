#pragma once

// --- 1. Base Definitions (Data & Traits) ---
#include <N503/Syntax/Node.hpp>
#include <N503/Syntax/NodeType.hpp>
#include <N503/Syntax/NodeVisitor.hpp>
#include <N503/Syntax/Token.hpp>
#include <N503/Syntax/TokenType.hpp>

// --- 2. State & Guards ---
#include <N503/Syntax/Reader/Guard/ExpectationGuard.hpp>
#include <N503/Syntax/Reader/Guard/ProgressGuard.hpp>
#include <N503/Syntax/Reader/Guard/RecursionGuard.hpp>
#include <N503/Syntax/Reader/Reader.hpp>
#include <N503/Syntax/Reader/State.hpp>
#include <N503/Syntax/Reader/Traits.hpp>
#include <N503/Syntax/Reader/Transaction.hpp>

// --- 3. Lexing Components (Traits & Scanners) ---
#include <N503/Syntax/Lexing/Always.hpp>
#include <N503/Syntax/Lexing/AnyOf.hpp>
#include <N503/Syntax/Lexing/IsAlnum.hpp>
#include <N503/Syntax/Lexing/IsAlpha.hpp>
#include <N503/Syntax/Lexing/IsDigit.hpp>
#include <N503/Syntax/Lexing/IsEnclosed.hpp>
#include <N503/Syntax/Lexing/IsNewline.hpp>
#include <N503/Syntax/Lexing/IsNumberBody.hpp>
#include <N503/Syntax/Lexing/IsNumberHead.hpp>
#include <N503/Syntax/Lexing/IsNumberSeparate.hpp>
#include <N503/Syntax/Lexing/IsQuote.hpp>
#include <N503/Syntax/Lexing/IsSameAsHead.hpp>
#include <N503/Syntax/Lexing/IsWhitespace.hpp>
#include <N503/Syntax/Lexing/LexerTrait.hpp>
#include <N503/Syntax/Lexing/Never.hpp>
#include <N503/Syntax/Lexing/Not.hpp>

// --- 4. Lexing Engine ---
#include <N503/Syntax/Lexing/Lexer.hpp>

// --- 5. Scanning -
#include <N503/Syntax/Scanning/DefaultScanner.hpp>
#include <N503/Syntax/Scanning/EnclosureScanner.hpp>
#include <N503/Syntax/Scanning/Identifier.hpp>
#include <N503/Syntax/Scanning/Ignore.hpp>
#include <N503/Syntax/Scanning/Number.hpp>
#include <N503/Syntax/Scanning/Operator.hpp>
#include <N503/Syntax/Scanning/String.hpp>
#include <N503/Syntax/Scanning/Whitespace.hpp>

// --- 6. Parsing Engine & Traits ---
#include <N503/Syntax/Parsing/FixedString.hpp>
#include <N503/Syntax/Parsing/IsLexeme.hpp>
#include <N503/Syntax/Parsing/IsType.hpp>
#include <N503/Syntax/Parsing/Parser.hpp>

// --- 7. Productions ---
#include <N503/Syntax/Production/Alternative.hpp>
#include <N503/Syntax/Production/Deferred.hpp>
#include <N503/Syntax/Production/Expect.hpp>
#include <N503/Syntax/Production/Maybe.hpp>
#include <N503/Syntax/Production/Repetition.hpp>
#include <N503/Syntax/Production/Sequence.hpp>
#include <N503/Syntax/Production/Terminal.hpp>

// --- 8. Grammar/DSL ---
// Combinators
#include <N503/Syntax/Grammar/And.hpp>
#include <N503/Syntax/Grammar/Any.hpp>
#include <N503/Syntax/Grammar/Atom.hpp>
#include <N503/Syntax/Grammar/Definition.hpp>
#include <N503/Syntax/Grammar/Lazy.hpp>
#include <N503/Syntax/Grammar/Many.hpp>
#include <N503/Syntax/Grammar/Optional.hpp>
#include <N503/Syntax/Grammar/Or.hpp>
#include <N503/Syntax/Grammar/Required.hpp>

// Terminals
#include <N503/Syntax/Grammar/Done.hpp>
#include <N503/Syntax/Grammar/Equals.hpp>
#include <N503/Syntax/Grammar/Identifier.hpp>
#include <N503/Syntax/Grammar/Lexeme.hpp>
#include <N503/Syntax/Grammar/NotEquals.hpp>
#include <N503/Syntax/Grammar/Number.hpp>
#include <N503/Syntax/Grammar/Operator.hpp>
#include <N503/Syntax/Grammar/String.hpp>
#include <N503/Syntax/Grammar/Type.hpp>
#include <N503/Syntax/Grammar/Unknown.hpp>
#include <N503/Syntax/Grammar/Whitespace.hpp>
