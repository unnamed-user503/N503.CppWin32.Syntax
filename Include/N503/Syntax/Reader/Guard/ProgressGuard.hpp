#pragma once

#include <N503/Syntax/Reader/State.hpp>
#include <stdexcept>

namespace N503::Syntax::Reader::Guard
{

    /// @class ProgressGuard
    /// @brief リーダーのパース進捗を監視し、無限ループを防止するためのガードクラスです。
    /// @tparam TReader リーダーの型
    template <typename TReader> class ProgressGuard final
    {
    public:
        /// @brief ガードを初期化し、現在のリーダーの状態を保存します。
        /// @param reader 監視対象のリーダー
        explicit ProgressGuard(const TReader& reader) : m_Reader{ reader }, m_StartState{ reader.GetState() }
        {
        }

        /// @brief パースが開始時より進行しているか検証します。
        /// @details 位置が更新されていない（進んでいない）場合、無限ループの可能性があるとして例外をスローします。
        /// @throw std::runtime_error 進捗が確認できない場合にスローされます。
        auto Verify() const -> void
        {
            if (m_Reader.GetState().Position <= m_StartState.Position)
            {
                throw std::runtime_error{ "N503::Syntax::Parsing::Failsafe: Progress verification failed." };
            }
        }

        /// @brief コピーコンストラクタ（禁止）
        ProgressGuard(const ProgressGuard&) = delete;

        /// @brief コピー代入演算子（禁止）
        auto operator=(const ProgressGuard&) -> ProgressGuard& = delete;

    private:
        /// @brief 監視対象のリーダーへの参照
        const TReader& m_Reader;

        /// @brief ガード開始時のリーダーステート
        const State m_StartState;
    };

} // namespace N503::Syntax::Reader::Guard
