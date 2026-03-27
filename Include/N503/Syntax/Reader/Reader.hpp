#pragma once

#include <N503/Syntax/Reader/State.hpp>
#include <N503/Syntax/Reader/Traits.hpp>
#include <N503/Syntax/Reader/Transaction.hpp>
#include <optional>
#include <type_traits>

namespace N503::Syntax::Reader
{

    /// @class Reader
    /// @brief ストリームから要素を読み取るための汎用リーダー・クラスです。
    /// @tparam TTraits リーダーが扱う型情報を定義するトレイト型
    template <typename TTraits> class Reader final
    {
    public:
        /// @brief 要素の型
        using ValueType = typename TTraits::ValueType;

        /// @brief 部分範囲（ビュー）の型
        using ViewType = typename TTraits::ViewType;

        /// @brief リーダーの状態（位置情報等）の型
        using StateType = State;

    public:
        /// @brief コンストラクタ
        /// @param source 読み取り対象のソース
        explicit Reader(const typename TTraits::SourceType source)
            : m_Source{ source }
        {
        }

        /// @brief 現在の位置の要素を消費せずに取得します。
        /// @return 現在の要素。終端に達している場合は std::nullopt
        [[nodiscard]]
        auto Peek() const noexcept -> std::optional<ValueType>
        {
            if (IsAtEnd())
            {
                return std::nullopt;
            }

            return m_Source[m_CurrentState.Position];
        }

        /// @brief 指定したオフセット先の要素を消費せずに取得します。
        /// @param offset 現在位置からのオフセット量
        /// @return 指定位置の要素。範囲外の場合は std::nullopt
        [[nodiscard]]
        auto Lookahead(const std::size_t offset = 0) const noexcept -> std::optional<ValueType>
        {
            const auto target = m_CurrentState.Position + offset;

            if (target >= m_Source.size())
            {
                return std::nullopt;
            }

            return m_Source[target];
        }

        /// @brief 現在の読み取り位置を1つ進めます。
        auto Advance() noexcept -> void
        {
            if (!IsAtEnd())
            {
                ++m_CurrentState.Position;
            }
        }

        /// @brief 現在のリーダーの状態を取得します。
        /// @return 現在の状態
        [[nodiscard]]
        auto GetState() const noexcept -> StateType
        {
            return m_CurrentState;
        }

        /// @brief リーダーの状態を任意の状態に設定（復元）します。
        /// @param state 設定する状態
        auto SetState(const StateType state) noexcept -> void
        {
            m_CurrentState = state;
        }

        /// @brief 次の要素が読み取り可能かどうかを判定します。
        /// @return 読み取り可能な場合は true
        [[nodiscard]]
        auto CanRead() const noexcept -> bool
        {
            // 1. 物理的な終端チェック
            if (IsAtEnd())
            {
                return false;
            }

            // 3. それ以外（CharacterReaderなど）は Peek できるなら読めると判断
            return true;
        }

        /// @brief リーダーが終端に達しているかを判定します。
        /// @return 終端に達している場合は true
        [[nodiscard]]
        auto IsAtEnd() const noexcept -> bool
        {
            return m_CurrentState.Position >= m_Source.size();
        }

        /// @brief 条件を満たしている間、要素をスキップします。
        /// @tparam TPredicate 条件判定を行う関数オブジェクトの型
        /// @param predicate 要素を引数に取り、スキップし続けるなら true を返す述語
        template <typename TPredicate> auto SkipWhile(const TPredicate predicate) -> void
        {
            while (const auto val = Peek())
            {
                if (!predicate(*val))
                {
                    break;
                }
                Advance();
            }
        }

        /// @brief 条件を満たしている間要素を読み進め、その範囲をビューとして返します。
        /// @tparam TPredicate 条件判定を行う関数オブジェクトの型
        /// @param predicate 要素を引数に取り、読み進めるなら true を返す述語
        /// @return 読み取られた範囲のビュー
        template <typename TPredicate> auto TakeWhile(const TPredicate predicate) -> ViewType
        {
            const auto start = GetState();

            while (const auto val = Peek())
            {
                if (!predicate(*val))
                {
                    break;
                }
                Advance();
            }

            return View(start);
        }

        /// @brief 指定された開始状態から現在の位置までの範囲をビューとして取得します。
        /// @param start 開始時の状態
        /// @return 指定範囲のビュー
        [[nodiscard]]
        auto View(const StateType start) const noexcept -> ViewType
        {
            const auto length = m_CurrentState.Position - start.Position;

            if constexpr (std::is_same_v<ValueType, char>)
            {
                return m_Source.substr(start.Position, length);
            }
            else
            {
                return m_Source.subspan(start.Position, length);
            }
        }

        /// @brief 状態の巻き戻しをサポートするトランザクションを開始します。
        /// @return トランザクション・オブジェクト
        [[nodiscard]]
        auto BeginTransaction() noexcept -> Transaction<Reader<TTraits>>
        {
            return Transaction<Reader<TTraits>>{ *this };
        }

    private:
        /// @brief ソースデータ本体
        typename TTraits::SourceType m_Source;

        /// @brief 現在のリーダーの状態
        StateType m_CurrentState{ .Position = 0, .Depth = 0 };
    };

    /// @brief 文字単位での読み取りを行うリーダーのエイリアス
    using CharacterReader = Reader<CharacterTraits>;

    /// @brief トークン単位での読み取りを行うリーダーのエイリアス
    using TokenReader = Reader<TokenTraits>;

} // namespace N503::Syntax::Reader
