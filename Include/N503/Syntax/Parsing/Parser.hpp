#pragma once

#include <N503/Diagnostics.hpp>
#include <N503/Memory.hpp>
#include <N503/Syntax/Node.hpp>
#include <N503/Syntax/NodeType.hpp>
#include <N503/Syntax/Reader/Guard/ProgressGuard.hpp>
#include <N503/Syntax/Reader/Reader.hpp>
#include <N503/Syntax/Token.hpp>
#include <vector>

namespace N503::Syntax::Parsing
{

    /// @class Parser
    /// @brief トークン列を解析し、抽象構文木（AST）を構築する汎用パーサー・クラスです。
    /// @tparam TProducers 構文規則を定義するプロデューサー（生成器）群
    template <typename... TProducers> struct Parser final
    {
        /// @brief 入力されたトークン列から構文解析を行い、ルートノードを返します。
        /// @param tokens 字句解析済みのトークンリスト
        /// @param arena ノードのメモリ割り当てに使用するアリーナ・アロケータ
        /// @param sink エラーや警告を報告するための診断シンク
        /// @return 構築されたASTのルートノードへのポインタ
        [[nodiscard]]
        auto Parse(const std::vector<Token>& tokens, Memory::Storage::Arena& arena, Diagnostics::Sink& sink) const -> Node*
        {
            Reader::TokenReader reader{ tokens };
            auto* const rootNode = arena.Create<Node>(NodeType::Root);

            // C++17: 畳み込み式を用いて、指定されたプロデューサーを順番に展開・実行
            // 各プロデューサーは特定の構文単位（文、宣言など）を生成する役割を担う
            (void)([&]
            {
                if (!reader.CanRead())
                {
                    return;
                }

                // 各プロデューサーがストリームを解析し、生成されたノード群を取得
                const auto results = TProducers{}.Produce(reader, arena, sink);

                for (auto* const node : results)
                {
                    rootNode->AddChild(node);
                }
            }(), ...);

            // --- エラーリカバリ ---
            // 全てのプロデューサーを適用した後、未消費のトークンが残っている場合の処理
            while (reader.CanRead())
            {
                // 無限ループを防止するための進捗監視
                auto recoveryGuard = Reader::Guard::ProgressGuard{ reader };

                if (const auto token = reader.Peek())
                {
                    // 解析不能なトークンを Unknown ノードとして救出し、ASTの一部に組み込む
                    rootNode->AddChild(arena.Create<Node>(NodeType::Unknown, *token));

                    // 診断シンクに予期せぬトークンの発生を報告
                    sink.Report({ N503::Diagnostics::Severity::Error, token->Position, "Unexpected token: Input could not be matched with any production." });
                }

                // 1トークン分強制的に進めて解析を続行
                reader.Advance();
                recoveryGuard.Verify();
            }

            return rootNode;
        }
    };

} // namespace N503::Syntax::Parsing
