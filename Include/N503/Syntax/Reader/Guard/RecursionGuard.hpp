#pragma once

#include <N503/Diagnostics/Sink.hpp>
#include <stdexcept>

namespace N503::Syntax::Reader::Guard
{

    /// @class RecursionGuard
    /// @brief パース時の再帰深度を監視し、スタックオーバーフローを防止するためのガードクラスです。
    /// @tparam TReader リーダーの型
    template <typename TReader> class RecursionGuard final
    {
    public:
        /// @brief ガードを初期化し、現在の再帰深度をインクリメントします。
        /// @details 制限値を超えた場合は例外をスローします。
        /// @param reader 監視対象のリーダー
        /// @param limit 再帰深度の許容制限値
        /// @throw std::runtime_error 再帰深度が制限値を超えた場合にスローされます。
        explicit RecursionGuard(TReader& reader, const std::size_t limit) : m_Reader{ reader }
        {
            auto state = m_Reader.GetState();
            state.Depth++; // 深度をインクリメント

            if (state.Depth > limit)
            {
                throw std::runtime_error{ "N503::Syntax::Parsing::Failsafe: Recursion limit exceeded." };
            }

            m_Reader.SetState(state);
        }

        /// @brief デストラクタ。スコープを抜ける際に再帰深度をデクリメントします。
        ~RecursionGuard()
        {
            auto state = m_Reader.GetState();
            if (state.Depth > 0)
            {
                state.Depth--;
                m_Reader.SetState(state);
            }
        }

        /// @brief コピーコンストラクタ（禁止）
        RecursionGuard(const RecursionGuard&) = delete;

        /// @brief コピー代入演算子（禁止）
        auto operator=(const RecursionGuard&) -> RecursionGuard& = delete;

    private:
        /// @brief 監視対象のリーダーへの参照
        TReader& m_Reader;
    };

} // namespace N503::Syntax::Reader::Guard
