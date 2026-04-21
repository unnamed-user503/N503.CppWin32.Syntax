#pragma once

#include <N503/Syntax/Reader/State.hpp>

namespace N503::Syntax::Reader
{

    /// @brief リーダーの状態を一時的に保存し、必要に応じてロールバックを行うためのトランザクション・クラス
    /// @tparam TReader 操作対象となるリーダーの型
    template <typename TReader> class Transaction final
    {
    public:
        /// @brief コンストラクタ。現在のリーダーの状態を保存します。
        /// @param reader 操作対象のリーダー
        explicit Transaction(TReader &reader) : m_Reader{reader}, m_SavedState{reader.GetState()}, m_IsCommitted{false}
        {
        }

        /// @brief トランザクションをコミットします。
        /// 呼び出し後は、デストラクタによる状態のリセット（ロールバック）が行われません。
        auto Commit() noexcept -> void
        {
            m_IsCommitted = true;
        }

        /// @brief デストラクタ。
        /// Commit() が呼び出されていない場合、リーダーの状態をコンストラクタ呼び出し時の時点まで巻き戻します。
        ~Transaction()
        {
            if (!m_IsCommitted)
            {
                m_Reader.SetState(m_SavedState);
            }
        }

        /// @brief コピーコンストラクタ（禁止）
        Transaction(const Transaction &) = delete;

        /// @brief コピー代入演算子（禁止）
        /// @return Transaction&
        auto operator=(const Transaction &) -> Transaction & = delete;

    private:
        /// @brief 操作対象のリーダーへの参照
        TReader &m_Reader;

        /// @brief コンストラクタ呼び出し時に保存されたリーダーの状態
        const State m_SavedState;

        /// @brief トランザクションが成功したかどうかを示すフラグ
        bool m_IsCommitted;
    };

} // namespace N503::Syntax::Reader
