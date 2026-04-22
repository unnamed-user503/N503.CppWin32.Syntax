#pragma once

#include <N503/Diagnostics/Sink.hpp>
#include <N503/Memory/Storage/Arena.hpp>
#include <N503/Syntax/Node.hpp>
#include <N503/Syntax/NodeType.hpp>
#include <N503/Syntax/Reader/Guard/ProgressGuard.hpp>
#include <N503/Syntax/Reader/Reader.hpp>
#include <vector>

namespace N503::Syntax::Production
{

    /// @brief 指定された要素の繰り返しを解析するクラスです。
    /// @details
    /// 最小一致回数（MinCount）を満たすまで繰り返し解析を行い、
    /// 条件を満たした場合は累積されたノードリストを返します。
    /// @tparam TProducer 繰り返し対象となるプロダクション型、またはトークンを判定する述語型
    /// @tparam MinCount 成功と見なされるために必要な最小の一致回数（デフォルトは 0）
    template <typename TProducer, std::size_t MinCount = 0> struct Repetition final
    {
        /// @brief 要素の繰り返し解析を実行します。
        /// @param reader トークンリーダー
        /// @param arena ノード生成に使用するメモリ管理アリーナ
        /// @param sink 診断情報を記録するシンク
        /// @return 生成されたすべてのノードのリスト。最小回数に満たない場合は空のリスト
        [[nodiscard]]
        auto Produce(Reader::TokenReader& reader, Memory::Storage::Arena& arena, Diagnostics::Sink& sink) const -> std::vector<Node*>
        {
            auto totalResults = std::vector<Node*>{};
            auto matchCount = std::size_t{ 0 };

            while (!reader.IsAtEnd())
            {
                // ループがトークンを消費せずに回り続けるのを防ぐ
                auto progressGuard = Reader::Guard::ProgressGuard{ reader };
                auto transaction = reader.BeginTransaction();
                auto currentNodes = std::vector<Node*>{};

                // プロダクションとしての試行
                if constexpr (requires { TProducer{}.Produce(reader, arena, sink); })
                {
                    currentNodes = TProducer{}.Produce(reader, arena, sink);
                }
                // トークン述語としての試行
                else if (const auto token = reader.Peek(); token && TProducer{}(*token))
                {
                    currentNodes.push_back(arena.Create<Node>(NodeType::Terminal, *token));
                    reader.Advance();
                }

                if (!currentNodes.empty())
                {
                    transaction.Commit();

                    for (auto* const node : currentNodes)
                    {
                        totalResults.push_back(node);
                    }

                    matchCount++;
                }
                else
                {
                    // 一致しなくなったらループを終了
                    break;
                }

                progressGuard.Verify();
            }

            // 最小一致回数を満たしているかチェック
            if (matchCount >= MinCount)
            {
                return totalResults;
            }

            return {};
        }
    };

} // namespace N503::Syntax::Production
