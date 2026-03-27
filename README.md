# N503::Syntax Library

C++20 で実装された、字句解析（Lexing）および構文解析（Parsing）のための軽量で柔軟なフレームワークです。テンプレートと演算子オーバーロードを活用し、宣言的な文法定義と型安全な AST 構築を実現します。

---

## 主な特徴

* **C++20 準拠**: Concepts や可変引数テンプレートをフル活用。
* **直感的な文法 DSL**: `+` (連続), `|` (選択), `*` (繰り返し) 等の演算子で文法を記述可能。
* **柔軟なノード管理**: `.As<NodeType::X>()` メソッドにより、解析結果を特定の意味を持つノードとして構造化。
* **メモリアリーナ対応**: 構文解析時のノード生成に `Arena` 等のカスタムストレージを利用可能。

---

## 基本コンポーネント

### 1. 字句解析 (Lexing & Scanning)
ソース文字列を意味のある単位（トークン）に分解します。
* `Lexer<TRules...>`: 登録されたスキャナールールを順次適用。
* 提供スキャナー: `Identifier`, `Number`, `String`, `Operator`, `Ignore` (空白・コメント等)

### 2. 構文解析 (Grammar & Parsing)
トークンの並びをツリー構造（AST）へ変換します。
* `Parser<TRule>`: 定義された規則に基づき解析を実行。
* `Node`: 種類 (`NodeType`)、関連トークン、子ノードのリストを保持。

---

## 実装例

以下は、代入文 (`result = 404`) を解析する最小構成の例です。

### 文法定義
`N503::Syntax::Grammar` を使用して、ルールを宣言的に記述します。

```cpp
namespace MyProject::Grammar {
    using namespace N503::Syntax::Grammar;

    // (識別子 + 等号 + 数値) を一つの "Statement" ノードとして定義
    inline constexpr auto Assignment = (Identifier + Equals + Number).As<NodeType::Statement>();
}
```

### 解析の実行
字句解析器 (Lexer) と 構文解析器 (Parser) を構成し、ソースコードを解析します。

```cpp
#include <N503/Diagnostics.hpp>
#include <N503/Memory.hpp>
#include <N503/Syntax.hpp>
#include <iostream>

int main()
{
    using namespace N503::Syntax;
    
    // 1. Lexer の構成 (適用順にルールを並べる)
    Lexing::Lexer<
        Scanning::Identifier,
        Scanning::Number,
        Scanning::Operator,
        Scanning::Ignore
    > lexer;

    // 2. Parser の構成
    using MyRule = Grammar::RuleOf<MyProject::Grammar::Assignment>;
    Parsing::Parser<MyRule> parser;

    // 3. 解析実行
    std::string_view source = " result = 404 ";
    N503::Diagnostics::Sink sink;
    N503::Memory::Storage::Arena arena(4096);

    std::vector<Token> tokens = lexer.Tokenize(source, sink);
    Node* root = parser.Parse(tokens, arena, sink);

    // 4. AST の検証
    if (root && !root->GetChildren().empty())
    {
        Node* statement = root->GetChildren()[0];

        if (statement->GetType() == NodeType::Statement)
        {
            std::cout << "Successfully parsed statement!" << std::endl;
        }
    }

    return 0;
}
```

---

## ライブラリの構造 (Namespaces)

* `N503::Syntax`: コアクラス (`Node`, `Token`)
* `N503::Syntax::Lexing`: 文字判定述語 (`IsAlnum`, `Not`, `AnyOf` 等)
* `N503::Syntax::Scanning`: 字句抽出ルール (`DefaultScanner`, `EnclosureScanner`)
* `N503::Syntax::Parsing`: 字句解析 (`Parser` 等)
* `N503::Syntax::Grammar`: 文法構築コンビネータ (`Sequence`, `Alternative`, `Repeat`)

---

## 動作環境
* **言語規格**: C++20
* **プラットフォーム**: Windows (Visual Studio 2026 推奨)
* **アーキテクチャ**: x64
