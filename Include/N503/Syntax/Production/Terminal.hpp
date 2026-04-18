#pragma once

#include <N503/Diagnostics/Sink.hpp>
#include <N503/Memory/Storage/Arena.hpp>
#include <N503/Syntax/Node.hpp>
#include <N503/Syntax/NodeType.hpp>
#include <N503/Syntax/Reader/Reader.hpp>
#include <vector>

namespace N503::Syntax::Production
{

    /// @brief 特定の述語に一致するトークンを終端ノード（Leaf）として生成するクラスです。
    /// @tparam TTrait トークンを判定する述語型（LexerTrait 相当）
    template <typename TTrait> struct Terminal
    {
        /// @brief トークンの照合を行い、一致すれば終端ノードを生成します。
        /// @param reader トークンリーダー
        /// @param arena ノード生成に使用するメモリ管理アリーナ
        /// @param Diagnostics::Sink 診断情報を記録するシンク（未使用）
        /// @return 生成された単一ノードを含むリスト。一致しない場合は空のリスト
        [[nodiscard]]
        auto Produce(Reader::TokenReader& reader, Memory::Storage::Arena& arena, Diagnostics::Sink&) const -> std::vector<Node*>
        {
            if (const auto token = reader.Peek(); token && TTrait{}(*token))
            {
                auto* const node = arena.Create<Node>(NodeType::Terminal, *token);

                reader.Advance();

                return { node };
            }

            return {};
        }
    };

} // namespace N503::Syntax::Production
