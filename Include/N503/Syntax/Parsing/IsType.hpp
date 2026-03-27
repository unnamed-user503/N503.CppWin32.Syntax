#pragma once

#include <N503/Syntax/Token.hpp>
#include <N503/Syntax/TokenType.hpp>

namespace N503::Syntax::Parsing
{

    /// @struct IsType
    /// @brief トークンの種類（TokenType）が指定したものと一致するか判定するトレイトです。
    /// @tparam TargetType 比較対象となるトークン種別
    template <TokenType TargetType> struct IsType final
    {
        /// @brief トークン種別の比較を行います。
        /// @param token 判定対象のトークン
        /// @return 種別が一致すれば true
        [[nodiscard]]
        auto operator()(const Token& token) const -> bool
        {
            return token.Type == TargetType;
        }
    };

} // namespace N503::Syntax::Parsing
