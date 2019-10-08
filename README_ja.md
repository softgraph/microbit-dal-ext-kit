[ [English](README.md) ] [ 日本語 ]

# microbit-dal-ext-kit

`microbit-dal` (別名 micro:bit runtime) を使う C++ アプリケーションのためのコンポーネント・ユーティリティ集

## 概要

`microbit-dal-ext-kit` は BBC micro:bit と互換性のあるコンポーネント・ユーティリティを提供します。また非公式にですが、いくつかの拡張ボード・ハードウェアモジュールをサポートしています。Kit は小さな C++ クラスと関数で構成されていて、必要な部分だけを `microbit-dal` や Arm Mbed OS と組み合わせて利用することができます。

### 構造

<table>
	<tr><td align="center">
<code>microbit-dal-ext-kit-example</code>
	<br>
(または C++ で書かれた任意のモジュール)
	</td></tr>
	<tr><td align="center">
<code>microbit-dal-ext-kit</code>
	</td></tr>
	<tr><td align="center">
<code>microbit</code>
・
<code>microbit-dal</code>
	<br>
(別名 micro:bit runtime)
	</td></tr>
	<tr><td align="center">
Arm Mbed OS
	</td></tr>
	<tr><td align="center">
BBC micro:bit デバイス
	</td></tr>
	<tr><td align="center">
拡張ボード・ハードウェアモジュール (オプション)
	</td></tr>
	<tr><td align="center">
入出力 (オプション)
	</td></tr>
	</table>

### モジュール概略

+ [`microbit-dal-ext-kit-example` (github.com/softgraph)](https://github.com/softgraph/microbit-dal-ext-kit-example)  
`microbit-dal-ext-kit` の利用例

+ [`microbit-dal-ext-kit` (github.com/softgraph)](https://github.com/softgraph/microbit-dal-ext-kit)  
`microbit-dal` (別名 micro:bit runtime) を使う C++ アプリケーションのためのコンポーネント・ユーティリティ集  
`microbit` の併用も可能

+ [`microbit-dal` (github.com/lancaster-university)](https://github.com/lancaster-university/microbit-dal)  
The core set of drivers, mechanisms and types that make up the micro:bit runtime.  
micro:bit runtime を構成する基本部分です。

+ [`microbit` (github.com/lancaster-university)](https://github.com/lancaster-university/microbit)  
A collection of the commonly used components of the micro:bit runtime with a standard configuration, to provide an easy to use interface for programming the micro:bit in C/C++.  
micro:bit runtime を標準的な構成で利用する C/C++ 向けモジュールです。

### 非公式にサポートする拡張ボード・ハードウェアモジュール

+ ElecFreaks Joystick:bit
+ Kitronik Zip Halo
+ SparkFun moto:bit
+ Waveshare Mini Piano Module
+ 汎用ブザー
+ 汎用 NeoPixel (WS2812B) LED 列
+ 汎用ソナーモジュール (HC-SR04)

## ライセンス

MIT

## リソース

### Wiki

[microbit-dal-ext-kit と example のためのノート](https://github.com/softgraph/microbit-dal-ext-kit-example/wiki/Home-(ja)) を参照ください。

### ドキュメント

ドキュメントを生成するには、プロジェクトルートの `Doxyfile` を使って [Doxygen (doxygen.nl)](http://www.doxygen.nl/download.html#latestsrc) を実行してください。Doxygen version 1.8.0 以上が必要です。

### 利用例

モジュール       | URL
-------------- | ---
`microbit-dal-ext-kit-example` | <https://github.com/softgraph/microbit-dal-ext-kit-example>

### 必要なモジュール

モジュール       | URL | Version
-------------- | --- | -------
`microbit`     | <https://github.com/lancaster-university/microbit>     | v2.1.1
`microbit-dal` | <https://github.com/lancaster-university/microbit-dal> | v2.1.1

© 2019 Softgraph, Inc.
