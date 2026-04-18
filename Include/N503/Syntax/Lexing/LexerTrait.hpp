#pragma once

#include <concepts>

namespace N503::Syntax::Lexing
{

    /// @brief 字句解析の述語（Predicate）が満たすべき制約を定義するコンセプトです。
    /// @details 2つの char 型引数を受け取り、bool 型に変換可能な値を返す関数呼び出し演算子を持つ必要があります。
    /// @tparam T 検証対象の型
    template <typename T>
    concept LexerTrait = requires(T t, char c, char h) {
        { t(c, h) } -> std::convertible_to<bool>;
    };

} // namespace N503::Syntax::Lexing
