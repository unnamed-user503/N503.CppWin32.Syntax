#pragma once

#include <N503/Syntax/Lexing/IsNewline.hpp>
#include <N503/Syntax/Lexing/LexerTrait.hpp>

namespace N503::Syntax::Lexing
{

    /// @brief 特定の終端条件に達するまでの「囲まれた内容」を判定する述語クラスです。
    /// @details 終端判定（TEnd）および改行（IsNewline）のいずれにも該当しない場合に真を返します。
    /// @tparam TEnd 終端（閉じ記号など）を判定する LexerTrait 述語
    template <LexerTrait TEnd> struct IsEnclosed
    {
        /// @brief 囲みの中身として継続可能か判定します。
        /// @param c 判定対象の文字
        /// @param h 補助的な文字
        /// @return 終端でも改行でもなければ true
        [[nodiscard]]
        auto operator()(char c, char h) const noexcept -> bool
        {
            return !TEnd{}(c, h) && !IsNewline{}(c, h);
        }
    };

} // namespace N503::Syntax::Lexing
