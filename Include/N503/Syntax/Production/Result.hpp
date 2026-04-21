#pragma once
#include <N503/Syntax/Node.hpp>
#include <vector>

namespace N503::Syntax::Production
{
    struct Result
    {
        bool Succeeded; // 解析が文法に適合したか

        std::vector<Node *> Nodes; // 生成されたノード（空でも成功しうる）

        // 成功時のユーティリティ
        static auto Success(std::vector<Node *> nodes = {}) -> Result
        {
            return {true, std::move(nodes)};
        }

        // 失敗時のユーティリティ
        static auto Failure() -> Result
        {
            return {false, {}};
        }
    };
} // namespace N503::Syntax::Production
