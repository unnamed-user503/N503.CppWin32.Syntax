#pragma once

#include <N503/Diagnostics.hpp>
#include <N503/Memory.hpp>
#include <N503/Syntax/Node.hpp>
#include <N503/Syntax/NodeType.hpp>
#include <N503/Syntax/Reader/Guard/ProgressGuard.hpp>
#include <N503/Syntax/Reader/Reader.hpp>
#include <vector>

namespace N503::Syntax::Production
{

    /// @brief 特定の要素が任意（0回または1回）存在することを許容するクラスです。
    /// @details
    /// 解析に成功した場合は生成されたノードを返し、
    /// 失敗した場合はリーダーの状態を巻き戻した上で空のリストを返します。
    /// @tparam TElement プロダクション型、またはトークンを判定する述語型
    template <typename TElement> struct Maybe final
    {
        /// @brief 要素の解析を試みます。
        /// @param reader トークンリーダー
        /// @param arena ノード生成に使用するメモリ管理アリーナ
        /// @param sink 診断情報を記録するシンク
        /// @return 生成されたノードのリスト。存在しない場合は空のリスト
        [[nodiscard]]
        auto Produce(Reader::TokenReader& reader, Memory::Storage::Arena& arena, Diagnostics::Sink& sink) const -> std::vector<Node*>
        {
            auto guard = Reader::Guard::ProgressGuard{ reader };
            auto transaction = reader.BeginTransaction();
            auto resultNodes = std::vector<Node*>{};

            // プロダクションとしての試行
            if constexpr (requires { TElement{}.Produce(reader, arena, sink); })
            {
                resultNodes = TElement{}.Produce(reader, arena, sink);
            }
            // トークン述語としての試行
            else if (const auto token = reader.Peek(); token && TElement{}(*token))
            {
                resultNodes.push_back(arena.Create<Node>(NodeType::Terminal, *token));
                reader.Advance();
            }

            if (!resultNodes.empty())
            {
                transaction.Commit();
                return resultNodes;
            }

            // 失敗してもトランザクションはコミットされず、
            // Reader は元の位置に維持されたまま空リストが返される
            return {};
        }
    };

} // namespace N503::Syntax::Production
