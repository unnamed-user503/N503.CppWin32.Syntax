#pragma once

#include <N503/Syntax/Parsing/FixedString.hpp>
#include <N503/Syntax/Token.hpp>

namespace N503::Syntax::Parsing
{

    /// @struct IsLexeme
    /// @brief トークンのレキシム（内容文字列）が特定の定数文字列と一致するか判定するトレイトです。
    /// @tparam TargetLexeme 比較対象となるコンパイル時定数文字列
    template <FixedString TargetLexeme> struct IsLexeme final
    {
        /// @brief トークンのレキシム比較を行います。
        /// @param token 判定対象のトークン
        /// @return レキシムが一致すれば true
        [[nodiscard]]
        auto operator()(const Token& token) const -> bool
        {
            return token.Lexeme == TargetLexeme.ToView();
        }
    };

} // namespace N503::Syntax::Parsing
