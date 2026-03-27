#pragma once

#include <cstdint>

namespace N503::Syntax
{

    /// @brief 字句解析におけるトークンの種類を定義する列挙型
    enum class TokenType : std::uint32_t
    {
        Unknown = 0,          ///< 未定義または判別不能なトークン
        Done,                 ///< 入力の終端（EOF）
        None,                 ///< スキップされたトークン
        Identifier,           ///< 識別子（変数名、関数名など）
        Number,               ///< 数値リテラル
        String,               ///< 文字列リテラル
        Operator,             ///< 演算子や記号
        Whitespace,           ///< 空白、タブ、改行など
        UserDefined = 0xff00, ///< ユーザー定義拡張用の開始値
    };

} // namespace N503::Syntax
