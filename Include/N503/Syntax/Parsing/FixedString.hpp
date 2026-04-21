#pragma once

#include <algorithm>
#include <string_view>

namespace N503::Syntax::Parsing
{

    /// @struct FixedString
    /// @brief コンパイル時定数文字列を保持するクラスです。
    /// @details C++20 の CNTTP を利用して、テンプレート引数に文字列リテラルを渡すために使用します。
    /// @tparam N 文字列の長さ（終端ヌル文字を含む）
    template <std::size_t N> struct FixedString final
    {
        /// @brief 文字列データ本体
        char data[N]{};

        /// @brief 文字列リテラルから FixedString を構築します。
        /// @param str 構築元の文字列リテラル
        constexpr FixedString(const char (&string)[N])
        {
            std::copy_n(string, N, data);
        }

        /// @brief std::string_view として取得します。
        /// @return 終端ヌル文字を除いた文字列のビュー
        [[nodiscard]]
        constexpr auto ToView() const noexcept -> std::string_view
        {
            // 終端ヌル文字を除いたサイズで view を作成
            return {data, N - 1};
        }

        /// @brief 文字列の長さを返します（終端ヌル文字を除く）。
        /// @return 文字列の長さ
        [[nodiscard]]
        static constexpr auto Size() noexcept -> std::size_t
        {
            return N - 1;
        }
    };

} // namespace N503::Syntax::Parsing
