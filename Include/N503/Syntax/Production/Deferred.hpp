#pragma once

#include <N503/Diagnostics/Sink.hpp>
#include <N503/Memory/Storage/Arena.hpp>
#include <N503/Syntax/Node.hpp>
#include <N503/Syntax/Reader/Guard/RecursionGuard.hpp>
#include <N503/Syntax/Reader/Reader.hpp>
#include <vector>

namespace N503::Syntax::Production
{

    /// @brief プロダクションの実行を遅延させ、再帰的な定義を可能にするクラスです。
    /// @details 相互参照や自己再帰を含む文法規則において、ポインタを介して実行時にターゲットを解決します。
    /// @tparam TProducer 遅延実行の対象となるプロダクション型
    template <typename TProducer> struct Deferred final
    {
        /// @brief 実行対象となるプロダクションへのポインタ
        const TProducer* const* const m_target;

        /// @brief 保持しているターゲットのプロダクションを実行します。
        /// @param reader トークンリーダー
        /// @param arena ノード生成に使用するメモリ管理アリーナ
        /// @param sink 診断情報を記録するシンク
        /// @return 生成されたノードのリスト。ターゲットが無効な場合は空のリスト
        [[nodiscard]]
        auto Produce(Reader::TokenReader& reader, Memory::Storage::Arena& arena, Diagnostics::Sink& sink) const -> std::vector<Node*>
        {
            // 無限再帰を防ぐためのスタック深さ制限
            auto recursionGuard = Reader::Guard::RecursionGuard{ reader, 512 };

            if (m_target && *m_target)
            {
                return (*m_target)->Produce(reader, arena, sink);
            }

            return {};
        }
    };

} // namespace N503::Syntax::Production
