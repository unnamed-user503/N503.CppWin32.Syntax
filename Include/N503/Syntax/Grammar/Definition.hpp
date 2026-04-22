#pragma once

#include <N503/Syntax/NodeType.hpp>
#include <N503/Syntax/Production/Alternative.hpp>
#include <N503/Syntax/Production/Maybe.hpp>
#include <N503/Syntax/Production/Repetition.hpp>
#include <N503/Syntax/Production/Sequence.hpp>

namespace N503::Syntax::Grammar
{

    /// @brief Definition コンセプト。
    /// @details Definition<T> 型、またはそれに準ずる「Type」エイリアスを持つ型を制約します。
    template <typename T>
    concept IsDefinition = requires { typename T::Type; };

    /// @struct Definition
    /// @brief 文法定義を包む「型の運び手（Type Carrier）」となる構造体です。
    /// @tparam T 内包する Production 型
    template <typename T> struct Definition
    {
        /// @brief 内包する Production の型エイリアスです。
        using Type = T;

        /// @brief デフォルトコンストラクタです。
        constexpr Definition() noexcept = default;

        // --- AST昇格 ---

        /// @brief 指定した NodeType への昇格（Sequence 化）を行います。
        /// @tparam NewType 昇格後のノード種別
        /// @return NodeType を付与した Definition オブジェクト
        template <NodeType NewType>
        [[nodiscard]]
        constexpr auto As() const noexcept -> Definition<Production::Sequence<NewType, T>>
        {
            return {};
        }

        // --- 単項演算子 (Many, Optional, AtLeastOne) ---

        /// @brief 0回以上の繰り返し (Many) を定義します。
        /// @return 0回以上の繰り返しを定義した Definition オブジェクト
        [[nodiscard]]
        constexpr auto operator*() const noexcept -> Definition<Production::Repetition<T, 0>>
        {
            return {};
        }

        /// @brief 1回以上の繰り返し (AtLeastOne) を定義します。
        /// @return 1回以上の繰り返しを定義した Definition オブジェクト
        [[nodiscard]]
        constexpr auto operator+() const noexcept -> Definition<Production::Repetition<T, 1>>
        {
            return {};
        }

        /// @brief オプション (Optional) を定義します。
        /// @return 任意性を定義した Definition オブジェクト
        [[nodiscard]]
        constexpr auto operator~() const noexcept -> Definition<Production::Maybe<T>>
        {
            return {};
        }
    };

    // --- 二項演算子 (Sequence, Alternative) ---

    /// @brief 連続 (A + B) を定義し、Sequence を生成します。
    /// @tparam T 左辺の Definition 型
    /// @tparam U 右辺の Definition 型
    /// @return 連続する文法を定義した Definition オブジェクト
    template <IsDefinition T, IsDefinition U>
    [[nodiscard]]
    constexpr auto operator+(const T&, const U&) noexcept -> Definition<Production::Sequence<NodeType::Unknown, typename T::Type, typename U::Type>>
    {
        return {};
    }

    /// @brief 選択 (A | B) を定義し、Alternative を生成します。
    /// @tparam T 左辺の Definition 型
    /// @tparam U 右辺の Definition 型
    /// @return 選択肢を定義した Definition オブジェクト
    template <IsDefinition T, IsDefinition U>
    [[nodiscard]]
    constexpr auto operator|(const T&, const U&) noexcept -> Definition<Production::Alternative<typename T::Type, typename U::Type>>
    {
        return {};
    }

    /// @brief 既存の Production 型から Definition を作成するヘルパー関数です。
    /// @tparam T 生成対象の Production 型
    /// @return 生成された Definition オブジェクト
    template <typename T>
    [[nodiscard]]
    constexpr auto Define(const T&) noexcept -> Definition<T>
    {
        return {};
    }

    /// @brief インスタンスから型情報を抽出するためのエイリアスです。
    /// @tparam RuleInstance 抽出対象のインスタンス
    template <auto RuleInstance> using RuleOf = typename decltype(RuleInstance)::Type;

} // namespace N503::Syntax::Grammar
