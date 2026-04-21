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

    /// @brief 複数の要素を順番に解析するシーケンス・プロダクション・クラスです。
    /// @details
    /// 指定されたすべての要素が順番に一致した場合のみ成功し、指定された NodeType の親ノードに
    /// 子要素を格納して返します。NodeType が Unknown の場合は、子要素のリストをそのまま返します。
    /// @tparam Type 生成される親ノードの型。Unknown の場合はノードをまとめずリストを返す
    /// @tparam ...TElements 連続して解析する要素（プロダクションまたは述語）のリスト
    template <NodeType Type, typename... TElements> struct Sequence final
    {
        /// @brief 要素を順番に解析し、ノードのツリーまたはリストを構築します。
        /// @param reader トークンリーダー
        /// @param arena ノード生成に使用するメモリ管理アリーナ
        /// @param sink 診断情報を記録するシンク
        /// @return 生成されたノードのリスト。途中で解析に失敗した場合は空のリスト
        [[nodiscard]]
        auto Produce(Reader::TokenReader &reader, Memory::Storage::Arena &arena, Diagnostics::Sink &sink) const
            -> std::vector<Node *>
        {
            auto transaction = reader.BeginTransaction();
            auto collectedNodes = std::vector<Node *>{};
            auto isFailed = false;

            // 各要素の順次試行
            (void)([&]
            {
                if (isFailed)
                {
                    return;
                }

                auto stepGuard      = Reader::Guard::ProgressGuard{ reader };
                auto currentResults = std::vector<Node*>{};

                // プロダクションとしての試行
                if constexpr (requires { TElements{}.Produce(reader, arena, sink); })
                {
                    currentResults = TElements{}.Produce(reader, arena, sink);
                }
                // トークン述語としての試行
                else if (const auto token = reader.Peek(); token && TElements{}(*token))
                {
                    currentResults.push_back(arena.Create<Node>(NodeType::Terminal, *token));
                    reader.Advance();
                }

                if (!currentResults.empty())
                {
                    for (auto* const node : currentResults)
                    {
                        collectedNodes.push_back(node);
                    }
                }
                else
                {
                    isFailed = true;
                }
            }(), ...);

            if (isFailed)
            {
                return {};
            }

            transaction.Commit();

            // NodeType::Unknown の場合はフラットなリストとして返す
            if constexpr (Type == NodeType::Unknown)
            {
                return collectedNodes;
            }
            // それ以外の場合は親ノードを生成して子要素を格納する
            else
            {
                auto *const containerNode = arena.Create<Node>(Type);

                for (auto *const childNode : collectedNodes)
                {
                    containerNode->AddChild(childNode);
                }

                return {containerNode};
            }
        }
    };

} // namespace N503::Syntax::Production
