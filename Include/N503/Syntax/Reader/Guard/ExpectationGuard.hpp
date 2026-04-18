#pragma once

#include <N503/Diagnostics/Severity.hpp>
#include <N503/Diagnostics/Sink.hpp>

namespace N503::Syntax::Reader::Guard
{

    /// @class ExpectationGuard
    /// @brief 特定の文法要素が「必須」であることを保証するためのガードクラスです。
    /// @details スコープを抜ける際に Commit されていない場合、エラーを診断情報（Sink）へ報告します。
    /// @tparam TReader リーダーの型
    template <typename TReader> class ExpectationGuard final
    {
    public:
        /// @brief ガードを初期化します。
        /// @param reader 現在の状態を取得するためのリーダー
        /// @param sink エラーを報告する先の診断シンク
        ExpectationGuard(const TReader& reader, Diagnostics::Sink& sink) : m_Reader{ reader }, m_Sink{ sink }, m_IsCommitted{ false }
        {
        }

        /// @brief ガードを正常に完了（コミット）します。
        /// @details これを呼び出した後は、デストラクタによるエラー報告は行われません。
        auto Commit() noexcept -> void
        {
            m_IsCommitted = true;
        }

        /// @brief デストラクタ。コミットされていない場合はエラーを報告します。
        ~ExpectationGuard()
        {
            if (!m_IsCommitted)
            {
                m_Sink.Report({ Diagnostics::Severity::Error, m_Reader.GetState().Position, "" });
            }
        }

        /// @brief コピーコンストラクタ（禁止）
        ExpectationGuard(const ExpectationGuard&) = delete;

        /// @brief コピー代入演算子（禁止）
        auto operator=(const ExpectationGuard&) -> ExpectationGuard& = delete;

    private:
        /// @brief 参照するリーダー
        const TReader& m_Reader;

        /// @brief 報告先の診断シンク
        Diagnostics::Sink& m_Sink;

        /// @brief コミット済みフラグ
        bool m_IsCommitted;
    };

} // namespace N503::Syntax::Reader::Guard
