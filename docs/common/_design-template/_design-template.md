---

title: "〇〇〇 設計書"
subject: ver.0.9.0
category: Confidential
author: "eSOL"
date: 2019/3/18
output:
  word_document:
    reference_doc: design-template.dotx
    toc: true

html:
  embed_local_images: true
  embed_svg: true
  offline: false
  toc: true

print_background: false

export_on_save:
  html: true
  
toc:
  depth_from: 2
  depth_to: 6
  ordered: true

---

# ○○○ 設計書

版数：Ver.0.9 rev.0

@import "../../common/style.less"
@import "../../common/js/sidebar-tocbot.js.html"
@import "../../common/signature.md"

---

## はじめに

### 本書の目的



### 用語の説明


@import "tables/概略/用語.csv"

### 関連ドキュメント

@import "tables/概略/関連ドキュメント.csv"

---

## 概要

### システム構成

@import "diagrams/システム構成図.puml"

---

## 要件

### 要求仕様

要求仕様を以下に示す。

@import "tables/概略/要求仕様.csv"

### 機能要件

ソフトウェアとして実現する機能は以下である。

@import "tables/概略/機能要件.csv"

---

## 前提条件

この設計における前提条件と制約を示す。

### 使用ソフトウェア

@import "tables/概略/使用ソフトウェア.csv"

---

## 影響範囲

この設計の影響範囲を以下に示す。

1. 影響１
1. 影響２

または、

この設計の影響範囲は**無し**。

---

## 設計方針

この設計の設計方針を示す。

### 方針１

### 方針２

---

## フォルダ・ファイル構成

フォルダ・ファイル構成を以下に示す。
ソースのルートフォルダは以下の通り。

```link
  ${root}/Solarmori/〇〇〇
```

ルートフォルダ配下のフォルダ、ファイル構成を示す

@import "tables/フォルダ・ファイル構成.csv"

---

## 外部仕様

### ビルドコンフィギュレーション

#### mbed_lib.json 設定

@import "tables/外部仕様/mbed_lib.json.csv"

#### マクロ設定

@import "tables/外部仕様/マクロ設定.csv"

#### 構造体

@import "tables/外部仕様/構造体.csv"

#### 列挙型

@import "tables/外部仕様/列挙型.csv"

### API

@import "API/API-template.md"

## 実装仕様

## 制限事項

この設計の制限事項を以下に示す。

1. 制限事項１
1. 制限事項２

または、

この設計の制限事項は**無し**。

## 特記事項

この設計の特記事項を示す

1. 特記事項１
1. 特記事項２

または、

この設計の特記事項は**無し**。

