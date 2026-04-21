#pragma once

#include <N503/Syntax/Node.hpp>
#include <N503/Syntax/NodeType.hpp>

#include <algorithm>
#include <functional>
#include <unordered_map>
#include <utility>

namespace N503::Syntax
{

    /// @brief ノードを巡回し、特定の NodeType に応じた処理を委譲する Visitor です。
    /// @tparam Context 巡回中に持ち回る状態（コンテキスト）の型
    template <typename Context> class NodeVisitor
    {
    public:
        // ハンドラの型：対象ノードと、ユーザー定義のコンテキストを受け取る
        using Handler = std::function<void(Node *, Context &)>;

    public:
        /// @brief 特定の NodeType に対する処理を登録します
        auto On(const NodeType type, Handler handler) -> void
        {
            m_Handlers[type] = std::move(handler);
        }

        /// @brief 未登録の NodeType に対して実行されるデフォルト処理を設定します
        auto OnDefault(Handler handler) -> void
        {
            m_DefaultHandler = std::move(handler);
        }

        /// @brief 指定したノードから再帰的に巡回を開始します
        /// @param node 開始ノード
        /// @param context 巡回中に使用する状態オブジェクト
        auto Visit(Node *node, Context &context) -> void
        {
            if (!node)
            {
                return;
            }

            // 1. 自身の処理を実行 (Register されたものがあれば優先)
            if (const auto it = m_Handlers.find(node->GetType()); it != m_Handlers.end())
            {
                it->second(node, context);
            }
            else if (m_DefaultHandler)
            {
                m_DefaultHandler(node, context);
            }

            // 2. 子ノードを再帰的に巡回
            for (auto *const child : node->GetChildren())
            {
                Visit(child, context);
            }
        }

    private:
        /// @brief
        std::unordered_map<NodeType, Handler> m_Handlers;

        /// @brief
        Handler m_DefaultHandler;
    };

} // namespace N503::Syntax
