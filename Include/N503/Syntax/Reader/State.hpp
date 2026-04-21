#pragma once

#include <cstddef>

namespace N503::Syntax::Reader
{

    /// @brief リーダーの現在の読み取り状態を保持する構造体
    struct State final
    {
        /// @brief ソース内における現在の絶対位置（インデックス）
        std::size_t Position{0};

        /// @brief 解析における現在の階層の深さ（ネストレベルなど）
        std::size_t Depth{0};
    };

    /// @brief ソース上の位置を示すための型エイリアス（Stateと同一）
    using Location = State;

} // namespace N503::Syntax::Reader
