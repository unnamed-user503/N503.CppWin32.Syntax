#pragma once

#include <N503/Diagnostics.hpp>
#include <N503/Memory.hpp>
#include <N503/Syntax/Node.hpp>
#include <N503/Syntax/NodeType.hpp>
#include <N503/Syntax/Reader/Guard/ExpectationGuard.hpp>
#include <N503/Syntax/Reader/Reader.hpp>
#include <vector>

namespace N503::Syntax::Production
{

    /// @brief 特定の要素が解析されることを期待するプロダクション・クラスです。
    /// @details
    /// ターゲットがプロダクションであればそれを実行し、
    /// 述語であれば現在のトークンとの照合を試みます。
    /// 解析に失敗した場合は、ExpectationGuard を通じてエラー情報が記録されます。
    /// @tparam TElement プロダクション型、またはトークンを判定する述語型
    template <typename TElement> struct Expect final
    {
        /// @brief 要素の解析を試み、成功した場合はノードのリストを返します。
        /// @param reader トークンリーダー
        /// @param arena ノード生成に使用するメモリ管理アリーナ
        /// @param sink 診断情報を記録するシンク
        /// @return 生成されたノードのリスト。失敗した場合は空のリスト
        [[nodiscard]]
        auto Produce(Reader::TokenReader& reader, Memory::Storage::Arena& arena, Diagnostics::Sink& sink) const -> std::vector<Node*>
        {
            auto expectationGuard = Reader::Guard::ExpectationGuard{ reader, sink };
            auto finalResult = std::vector<Node*>{};

            // TElement が Produce メソッドを持っている場合はプロダクションとして実行
            if constexpr (requires { TElement{}.Produce(reader, arena, sink); })
            {
                finalResult = TElement{}.Produce(reader, arena, sink);
            }
            // そうでなければトークン述語として現在の位置を照合
            else if (const auto token = reader.Peek(); token && TElement{}(*token))
            {
                finalResult.push_back(arena.Create<Node>(NodeType::Terminal, *token));
                reader.Advance();
            }

            if (!finalResult.empty())
            {
                expectationGuard.Commit();
                return finalResult;
            }

            return {};
        }
    };

} // namespace N503::Syntax::Production
