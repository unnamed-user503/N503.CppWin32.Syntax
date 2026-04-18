#pragma once

#include <N503/Diagnostics/Sink.hpp>
#include <N503/Memory/Storage/Arena.hpp>
#include <N503/Syntax/Node.hpp>
#include <N503/Syntax/Reader/Guard/ProgressGuard.hpp>
#include <N503/Syntax/Reader/Reader.hpp>
#include <vector>

namespace N503::Syntax::Production
{

    /// @brief 複数のプロダクション候補から最初に成功したものを選択するクラスです。
    /// @details 各候補を記述順に試行し、いずれかがノードを生成した時点で確定します（優先順位付き選択）。
    /// @tparam TProducers 試行対象となるプロダクション型のリスト
    template <typename... TProducers> struct Alternative final
    {
        /// @brief 候補を順番に実行し、最初に成功した結果を返します。
        /// @param reader トークンリーダー
        /// @param arena ノード生成に使用するメモリ管理アリーナ
        /// @param sink 診断情報を記録するシンク
        /// @return 生成されたノードのリスト。いずれも成功しなかった場合は空のリスト
        [[nodiscard]]
        auto Produce(Reader::TokenReader& reader, Memory::Storage::Arena& arena, Diagnostics::Sink& sink) const -> std::vector<Node*>
        {
            auto finalResult = std::vector<Node*>{};

            (void)([&]
            {
                // 既に結果が得られている場合は後続の試行をスキップ
                if (!finalResult.empty())
                {
                    return;
                }

                auto branchGuard = Reader::Guard::ProgressGuard{ reader };
                auto transaction = reader.BeginTransaction();

                // プロダクションの実行
                auto branchResult = TProducers{}.Produce(reader, sink, arena);

                if (!branchResult.empty())
                {
                    transaction.Commit();
                    finalResult = branchResult;
                }
            }(), ...);

            return finalResult;
        }
    };

} // namespace N503::Syntax::Production
