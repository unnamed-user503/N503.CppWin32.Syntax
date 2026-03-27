#pragma once

#include <N503/Syntax/TokenType.hpp>
#include <string_view>

namespace N503::Syntax
{

    /// @brief 字句解析によって抽出されたトークン情報を保持する構造体
    struct Token final
    {
        /// @brief トークンの種類
        TokenType Type;

        /// @brief ソースコード内における実際の文字列（字句）
        std::string_view Lexeme;

        /// @brief ソースコード内におけるこのトークンの出現位置
        std::size_t Position;
    };

    /// @brief トークンの種類（TokenType）に対応する識別名を取得します
    /// @param Type トークンの種類
    /// @return トークンの種類を表す文字列（デバッグ用などに利用）
    [[nodiscard]]
    inline auto GetTokenNameFromTokenType(const TokenType type) -> std::string_view
    {
        switch (type)
        {
        case TokenType::Unknown:
            return "Unknown";

        case TokenType::Done:
            return "Done";

        case TokenType::Whitespace:
            return "Whitespace";

        case TokenType::Identifier:
            return "Identifier";

        case TokenType::Number:
            return "Number";

        case TokenType::Operator:
            return "Operator";

        default:
            return "Invalid";
        }
    }

} // namespace N503::Syntax
