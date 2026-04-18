#pragma once

#include <cstdint>

namespace N503::Syntax
{

    /// @brief 構文解析木（AST）におけるノードの種類を定義する列挙型
    enum class NodeType : std::uint32_t
    {
        Unknown = 0,          ///< 未定義のノード
        Root,                 ///< 木の根（最上位ノード）
        Terminal,             ///< 終端記号（トークンを直接保持するリーフノード）

        Expression,           ///< 式（計算や値の評価）
        Statement,            ///< 文（処理の単位）
        Section,              ///< セクションまたはブロック

        SwitchOption,


        UserDefined = 0xff00, ///< ユーザー定義拡張用の開始値
    };

} // namespace N503::Syntax
