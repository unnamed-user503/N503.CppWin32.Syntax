#pragma once

namespace N503::Syntax::Lexing
{

    /// @struct IsNumberSeparate
    /// @brief 数値リテラルの終端を識別する区切り文字であるか判定する述語クラスです。
    struct IsNumberSeparate
    {
        /// @brief 区切り文字の判定を行います。
        /// @param c 判定対象の文字
        /// @param char 第2引数（未使用）
        /// @return 空白、カンマ、閉じ括弧、セミコロンなどの区切り文字であれば true
        [[nodiscard]]
        auto operator()(char c, char) const -> bool
        {
            return c == ' ' || c == '\t' || c == '\n' || c == ',' || c == ')' || c == ';';
        }
    };

} // namespace N503::Syntax::Lexing
