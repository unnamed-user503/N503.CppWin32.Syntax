#pragma once

#include <N503/Syntax/NodeType.hpp>
#include <N503/Syntax/Token.hpp>
#include <utility>
#include <vector>

namespace N503::Syntax
{

    /// @brief 構文解析木（AST）を構成するノード・クラス
    class Node final
    {
    public:
        /// @brief コンストラクタ
        /// @param Type ノードの種類（NodeType）
        /// @param token ノードに関連付けられたトークン（省略可能）
        explicit Node(const NodeType type, const Token &token = {})
            : m_Type{type}, m_Token{token}, m_Parent{}, m_Children{}
        {
        }

        /// @brief Copy禁止
        Node(const Node &) = delete;
        auto operator=(const Node &) -> Node & = delete;

        /// @brief Move禁止
        Node(Node &&) = delete;
        auto operator=(Node &&) -> Node & = delete;

        /// @brief ノードの種類を取得します
        /// @return ノードの種類
        [[nodiscard]]
        auto GetType() const noexcept -> NodeType
        {
            return m_Type;
        }

        /// @brief ノードに関連付けられたトークンを取得します
        /// @return トークンへの定数参照
        [[nodiscard]]
        auto GetToken() const noexcept -> const Token &
        {
            return m_Token;
        }

        /// @brief 子ノードを追加します
        /// @param child 追加する子ノードのポインタ
        auto AddChild(Node *child) noexcept -> void
        {
            if (!child)
            {
                return;
            }

            child->m_Parent = this;

            m_Children.push_back(child);
        }

        /// @brief 親のノードを取得します
        /// @return 親のノードへのポインタ
        auto GetParent() const noexcept -> Node *
        {
            return m_Parent;
        }

        /// @brief 全ての子ノードを取得します
        /// @return 子ノードのポインタを格納したベクトルへの定数参照
        [[nodiscard]]
        auto GetChildren() const noexcept -> const std::vector<Node *> &
        {
            return m_Children;
        }

    private:
        /// @brief ノードの型（種類）
        NodeType m_Type;

        /// @brief ノードが保持するトークン情報
        Token m_Token;

        /// @brief 親ノードへのポインタ
        Node *m_Parent;

        /// @brief 子ノードのリスト
        std::vector<Node *> m_Children;
    };

} // namespace N503::Syntax
