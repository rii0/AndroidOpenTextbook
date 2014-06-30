= Androidアプリのバックグラウンド

本章では、Androidアプリケーションの非同期処理、バックグラウンド処理を解説します。
UIスレッドで時間のかかる処理を行うと、その処理が終わるまでユーザの操作を受け付けなくなります。Androidには時間のかかる処理、たとえばデータ通信やディスクアクセスなどを非同期で行う仕組みがあります。
また常駐型アプリケーションではServiceを使い、バックグラウンドで処理を行えます。
ここでは快適なアプリケーションを作るために、Androidのもつ非同期通信、バックグラウンド処理の概要を理解したあと、AsyncTaskやServiceなど実際のAPIについて学んでいきましょう。

== 非同期処理とバックグラウンド
はじめに、本章で取り扱う機能やメソッドについて特徴を紹介します。


#@# 全部かいてあとで戻ってきて書こう。

=== フォアグラウンドとバックグラウンド
フォアグラウンドとは、ユーザーインターフェイス（UI）や操作できる画面や処理、状態を指します。
バックグラウンドとは、ユーザーにみせるUIの裏側で動作し、ユーザーに意識させずに行われる処理、状態です。バックグラウンドではUIを持たない性質上、ユーザーとの対話なしに行えるタスク（処理）に向いています。

AndroidではActivityがフォアグラウンド処理を、Serviceがバックグラウンド処理を担当します。バックグラウンド処理をもつAndroidアプリケーションとしては、Musicアプリなどが代表的です。

現在のコンピュータの多くは複数の作業を切り替えて実行するマルチタスク環境を持っており、それはAndroidも同様です。
コンピュータのCPUやI/O（ファイル入出力）など限りあるリソースを効率的に利用するために、マルチタスク環境では待ち時間の合間に他のタスクを実行しています。
一般的にフォアグラウンド処理はUIを担当するため、バックグラウンド処理より優先度が高く設定されています。


=== プロセスとスレッド
Androidアプリケーションではプロセスはアプリケーションごとの実行単位、実行環境です。基本的に1つのアプリケーションに対して1つのプロセスが割りあてられます。
アプリを実行するために必要なリソース（メモリやCPUなど）は、プロセスごとに管理されています。
またプロセスは新しいプロセス（子プロセス）を生成できます。子プロセスは、生成元となったプロセス（親プロセス）とは異なるリソースを利用します。
このため、複数のプロセスで同じメモリ空間を読み書きするといったリソースの共有はできません。

プログラムが動く仕組みを理解するうえで重要な考え方です。

スレッドとは処理の単位のことです。プロセスAndroidのActivityに関する処理は通常mainスレッドで動作しています。
onCreateやonPauseメソッド、各UIパーツ（ボタン、Viewなど）の描画処理などなどはmainスレッドで動いています。


===[column] デーモンスレッドとユーザースレッド
スレッドの種類は2つに分類されます。デーモンスレッドとは、プログラム終了時にスレッドの実行終了を待ちません。
プログラム終了のタイミングでデーモンスレッドの処理は中断され、終わることになります。生成したスレッドで終了処理を意識しないで済むので使い勝手がよい側面があります。

ユーザースレッドは、デーモンスレッドの反対でプログラムを終わるときに、スレッドの実行終了を待ちます。プログラムを終了しようとしても、
ユーザースレッドの処理が終わるまで終了できません（ユーザースレッドが生き残っている間は、プログラム実行状態です）。
さきほど説明にでてきた、UIスレッドはユーザースレッドです。プログラム終了にあたっては、すべてのユーザースレッドできちんと終了処理がハンドリングできていないといけません。
利点として、処理が中断してしまう恐れはないので紛失できない大事な処理などに適しています。
===[/column]


=== 同期と非同期処理
同期処理、非同期処理と



== 基本的な非同期処理


== AsynctaskとLoader


== ExecutorService、Thread

== Androidでの優先度制御


== Handler


== Service


== IntentService


== プロセス間通信（AIDL）

