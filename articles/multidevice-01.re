= マルチデバイス対応の基礎

Androidを搭載している端末の種類はものすごい勢いで増加しています。大きさや電池の持続時間などの他に、たとえば次のような違いが機種毎に存在します。

 * OSのバージョン
 * 画面サイズ
 * 通話機能やセンサーなどの有無

もし、このような違い、機種依存があることを考えずにAndroidアプリを開発した場合、すばらしいユーザー体験をできるのが一部の端末ユーザーのみとなります。
検証が足りていない端末を使っているユーザーからは低評価を受け、ユーザー体験の低下に繋がることでしょう。

本章では、作成したAndroidアプリをより多くの機種に、ユーザー体験を低下させずに提供するための方法を解説します。
サポートする機種を増やすための手法および、古いOSの機種はサポートしないといった、対応機種を制限する手法をみていきましょう。

== 定義

ここでは登場する言葉の定義を行います。

 * スクリーンサイズ

物理的な画面のサイズです。対角線の長さで表し、単位としてインチを用います。Androidでは、small、normal、large、extra largeの4つのグループで分類されています。
@<table>{screensize_inch}に、インチ数とグループの関係を示します。携帯電話の大部分は4〜5インチなので、まずはnormalで正しく表示されることを目指しましょう。@<fn>{device-large}

//table[screensize_inch][インチ数とグループの関係]{
グループ	インチ数
-----------------------
small	2〜3.5インチ程度
normal	3〜5インチ程度
large	4〜7インチ程度
extra large	7〜10インチ程度
//}

//footnote[device-large][最近の5インチ携帯電話はlargeに分類されそうですが、ピクセル密度が高いためnormalに分類されます。この理由は後で紹介します。]

 * ピクセル密度(density)

物理的な画面の中にピクセルがいくつ入っているかを表します。一般的にはdpi（dot per inch）という単位で、1インチの中に何ピクセル入っているかで表します。Androidでは、ldpi、mdpi、hdpi、xhdpi、xxhdpi、xxxhdpiというグループで分類されています。ピクセル密度の高い端末は、より精細な画像を表示することができます。

 *  dp（dip）

ピクセル密度に依存しない仮想的なピクセル単位（density-independent pixel）です。dp単位とピクセルの関係は、@<m>{px = dp * (dpi / 160)}で定義されています。この@<m>{dpi / 160}の部分とピクセル密度の関係を@<table>{density}に示します。

//table[density][dpi/160とピクセル密度の関係]{
ピクセル密度	dpi/160
-----------------------
ldpi	0.75
mdpi	1
hdpi	1.5
xhdpi	2
xxhdpi	3
xxxhdpi	4
//}

Androidでは、レイアウト時に長さの単位としてdpを用いると、実行時に端末のピクセル密度を用いて自動で適切なピクセル単位に変換してくれます。この機能により、ピクセル密度毎にレイアウトを作成する必要が無くなります。

== サポートする機種を増やす

ここからは、ユーザー体験の低下を防ぎつつ、動作する機種を増やすための手法を紹介します。

=== スクリーンサイズおよびピクセル密度の違いに対応する

作成したAndroidアプリは、さまざまな画面サイズやピクセル密度の端末上で実行されます。
レイアウトをピクセル単位で行ってしまうと、@<img>{width-pixel}のように、ある機種では画面の幅いっぱいに表示されるが、別の機種では画面の半分ほどのサイズで表示されるといった問題が発生します。

//image[width-pixel][ボタンの横幅をピクセルで指定した例][scale=0.35]{
//}

レイアウトが崩れてしまうと、ユーザー体験の低下に直結します。

これらの違いがあってもレイアウトが崩れないようにする手法のひとつがピクセル密度に依存しないレイアウトを行うことです。「Android搭載端末は、スクリーンサイズがばらばらで画面レイアウトが困難」とよく言われますが、販売されている携帯電話の大部分はスクリーンサイズnormalに分類されます。
つまり、多機種対応で最初に考慮すべき点はピクセル密度（density）の違いです。

ピクセル密度の異なる機種でも見え方、ユーザー体験の変わらないレイアウトの作り方をみていきましょう。

 * match_parentやwrap_contentを適切に使用する

Viewの幅を指定するandroid:layout_widthや、高さを指定するandroid:layout_heightは、単位付き数値（たとえば100pxなど）の他に、
match_parent（親Viewのサイズに合わせる）や、wrap_content（内部のコンテンツの大きさに合わせる。たとえば、TextViewであれば文字列の長さや高さ）が使用できます。
このmatch_parentやwrap_contentはピクセル密度を考慮にいれた上でサイズを決定するため、使用できる箇所では積極的に使用していきましょう。

//emlist[match_parentやwrap_contentを使用する]{
<Button
    android:layout_width="match_parent"
    android:layout_height="wrap_content"
    android:text="@string/login"
    />
//}

Javaプログラム中で動的にViewを生成する場合、@<list>{match_parent_java}のようにWRAP_CONTENT定数やMATCH_PARENT定数を使用してLayoutParamsオブジェクトを作成し、addView()でViewを追加する際、引数として渡します。

//list[match_parent_java][Javaプログラム中でmatch_parentを指定してViewを追加する]{
private void addButton(RelativeLayout parent, String label) {
    Button button = new Button(this);
    button.setText(label);

    RelativeLayout.LayoutParams params = new RelativeLayout.LayoutParams(
            RelativeLayout.LayoutParams.MATCH_PARENT,
            RelativeLayout.LayoutParams.WRAP_CONTENT
    );
    parent.addView(button, params);
}
//}

また、android:layout_marginやandroid:paddingの単位にpxを使用すると、ピクセル密度の高い端末で間隔が狭く見えたり、逆にピクセル密度の低い端末で間隔が広すぎたりしてしまいます。
この問題を解決するため、android:layout_marginやandroid:paddingには単位としてdpを使用しましょう。

=== 文字サイズの単位にspを使用する

Android 4.0より、ユーザーは文字の大きさを設定で変更できるようになりました。この設定をレイアウトに反映させるため、TextViewやButtonのandroid:textSizeには単位としてspを使用しましょう。
dpやpxを単位として使用した場合、せっかくユーザーが設定した文字サイズが反映されず、結果としてユーザー体験の低下につながります。

=== ピクセル密度に応じた画像を用意する

アプリ内で使用する画像は、res/drawable-mdpiフォルダや、res/drawable-xhdpiフォルダにいれて使用します。drawable-xhdpiにいれた画像は、端末のピクセル密度がxhdpiの時に使用されます。

ここで、次のような状況を考えてみます。

 1. res/drawable-mdpiフォルダに48 x 48pxのicon.pngを持つ
 2. res/drawable-xhdpiフォルダにはicon.pngを持たない
 3. ImageViewのandroid:srcに@drawable/iconを指定
 4. アプリをピクセル密度xhdpiの端末で実行する

この場合、res/drawable-xhdpiフォルダにicon.pngファイルが無いので、代わりにres/drawable-mdpiフォルダにあるicon.pngを2倍に拡大してImageViewに使用されます。
つまり、ピクセル密度の高い端末では画像が拡大されて、ぼやけてしまうことになります。このような事態を避けるため、ピクセル密度に応じた画像を用意し、適切なフォルダに同名のファイルにして入れましょう。

ここで、「拡大すると画像がぼやけてしまうのなら、逆にxxhdpi向けの画像だけ用意すれば、後は縮小してくれるのでは？」と思うかもしれません。
この場合、次のような理由により、ピクセル密度の低い端末でユーザー体験が低下してしまう恐れがあります。

携帯電話のスクリーンサイズの向上とともにピクセル密度も高くなっています。つまりピクセル密度の低い端末は、旧世代の端末であることが多く、（ピクセル密度の高い端末に比べ）処理能力が低い傾向にあります。
処理能力に劣る端末で高解像度の画像を扱うと画像の縮小に時間がかかり、表示されるまでに時間がかかってしまう、アプリケーションの動作が緩慢だと捉えられるかもしれません。
このような挙動はエミュレータでは実感しにくく、実際に体験するまで問題と認識しない可能性もあるでしょう。

=== スクリーンサイズの最小値を把握する

各スクリーンサイズには最小サイズが定義されています。@<table>{screenMinSize}にグループ毎の最小値を示します。スクリーンサイズがnormalであれば、470dp x 320dpより大きいことが保証されています。

//table[screenMinSize][スクリーンサイズの最小値]{
グループ	最小サイズ
-------------------
small	426dp x 320dp
normal	470dp x 320dp
large	640dp x 480dp
xlarge	960dp x 720dp
//}

たとえば、最近の5インチフルHD（Full High Definition）端末は1920 x 1080pxでxxhdpiなので、640dp x 380dpとなり、largeではなくnormalに分類されます。

=== ScrollViewを使ってスクリーンサイズの違いに対応する

前段でスクリーンサイズ毎の最小サイズ（dp値）を紹介しましたが、あくまで最小値なので、実際に販売されている機種の画面サイズ（dp値）はこれより大きいことがほとんどです。
スクリーンサイズがnormalでは、長辺は最低470dp以上となっていますが、たとえばGoogleのリファレンス端末であるNexus 5の長辺は690dpです。

この違いにより、「手元の開発用端末では想定していたレイアウトになるが、長辺が短い端末だと下がはみ出てしまい、一部のボタンが押せない」といった問題が発生します（@<img>{scrollview}）

//image[scrollview][ボタンが端末によってはみ出てしまう例][scale=0.25]{
//}

この問題を解決するため、レイアウト自体を470dp以内に収めるようやりなおすという手も考えられますが、さまざまな事情によりレイアウトを変更できないこともあるでしょう。
その場合、レイアウト全体をScrollViewにいれてみましょう。長辺の短い機種では画面全体がスクロールするようになるため、はみ出てしまった部分が操作できないといったことは発生しなくなります。

=== OSバージョンの違いに対応する

AndroidはOSのバージョンアップに伴い、新しいAPIがどんどん追加されています。各APIは追加されたOSのバージョンに対応するAPI Levelが設定されています。

たとえば、API Level 8のAPIはAndroid 2.2で新たに追加されたAPIで、Android 2.1以前の端末では使用することができません。

作成するAndroidアプリで使用できるAPIは、原則、サポートすると決めた最低のAPI Levelまでしか使用できません。たとえば、サポートする最低のAPI Levelを10（Android 2.3）と決めた上で、
ArrayAdapterクラスのaddAllメソッドを呼ぶコードを書いたとします。このAPIは意外にもAPI Level 11で追加されたAPIなので、Android 2.3でこのメソッドを呼ぼうとすると、NoSuchMethodErrorが発生してアプリはクラッシュしてしまいます。

しかし、「Android 2.3をサポートしたいが、Android 4.0以上でもよりよいユーザー体験を提供したい」という理由で、API Level 14以上のAPIを使用したい、といった状況も発生します。代表的な例はNotificationです。

これを実現するために、実行時に端末のAPI Levelを調べ、高API LevelのAPIが呼べる時だけ呼ぶといった処理を書くことができます。

@<list>{api_level}に、API Level 14以上の時のみ、Notificationに大きなアイコンを設定する例を示します。

//list[api_level][API Levelを調べて分岐する]{
private Notification createNotification(Bitmap bigIcon) {

    // API Level 14(IceCreamSandwich)前後で処理を分ける
    if (Build.VERSION.SDK_INT <
            Build.VERSION_CODES.ICE_CREAM_SANDWICH) {
        Notification notification = new Notification();
        notification.tickerText = "通知";
        // 中略
        return notification;
    } else {
        return new Notification.Builder(this)
                .setTicker("通知")
                // 中略
                .setLargeIcon(bigIcon)
                .getNotification();
    }
}
//}

//noindent

====[column] 横持ちに対応する

画面の上半分に情報を表示し、画面の下半分にボタンなどを配置した、縦持ちを考慮したレイアウトを作成したとします。
この画面を表示したまま、端末を横持ちにした場合、どうなるでしょうか？レイアウトの方法によって、情報部分しか表示されなかったり、横長の画面を上下に分割してしまったりします。
これではユーザー体験は著しく低下してしまうため、横持ちを考慮したレイアウトも作成しましょう。

縦持ちと横持ちで異なるレイアウトを使用する場合、res/layout-landフォルダを作成し、そこに縦持ち用と同じファイル名で横持ち用のレイアウトxmlファイルをいれます。
これだけで、setContentViewメソッドやinflater.inflateメソッドでレイアウトxmlファイルからViewを生成する時、画面の向きに応じて使用するレイアウトxmlファイルを切り替えてくれます。

====[/column]
//noindent
== 利用可能な端末を制限する

動作保証を確実にするために、インストール可能な端末を制限したり、特定の動作を制限したりする方法を紹介します。

 * インストール可能なOSのバージョンを制限する

「OSバージョンの違いに対応する」で紹介しましたが、作成するAndroidアプリが使用可能なAPI Levelの最低値を指定する必要があります。ADTではAndroidManifest.xml内のandroid:minSdkVersionで指定します。

 * 画面の向きを固定する

ハンドセット向けアプリで「横持ちでは十分なユーザー体験が提供できないので、画面の向きは縦持ちで固定したい」といったケースもあるでしょう。
画面の向きを固定するには、AndroidManifest.xmlのactivity要素にandroid:screenOrientation属性を追加します。@<list>{orientation}に、縦持ちで固定する例を示します。

//list[orientation][画面の向きを縦持ち固定にする]{
<activity
    android:name=".MainActivity"
    android:label="@string/app_name"
    android:screenOrientation="portrait">
    <intent-filter>
        <action android:name="android.intent.action.MAIN" />
        <category android:name="android.intent.category.LAUNCHER" />
    </intent-filter>
</activity>
//}

== エミュレーターでのテスト

作成しているAndroidアプリが正しく多機種対応できているかを、アプリを動作させて確認しましょう。OSバージョンやピクセル密度の異なる端末を用意するのは費用、手間の面で現実的ではありません、Android SDK付属のエミュレーターを使用しましょう。

 * エミュレーターのシステムイメージをインストールする

古いOSのエミュレーターを作成するために、Android SDK ManagerでOSバージョン毎にシステムイメージをインストールします。@<img>{install-emulator}に、Android 4.0.3（API Level 15）のシステムイメージをインストールする例を示します。

//image[install-emulator][システムイメージのインストール][scale=0.25]{
//}

 * エミュレーターのスクリーンサイズとピクセル密度を指定する

次に、テスト対象となるエミュレーターを作成しましょう。Android Virtual Device Managerを起動し、Createボタンをクリックします。クリックすると、@<img>{create-emulator}のダイアログが表示されるので、Device欄で端末の種類とピクセル密度を、Skin欄でスクリーンサイズを指定します。@<table>{skin-pixel}にSkinとピクセル数の関係を示します。

//image[create-emulator][エミュレーターの新規作成][scale=0.3]{
//}

//table[skin-pixel][Skinとピクセル数の関係]{
Skin	ピクセル数
------------------
Skin with dynamic hardware controls	Deviceで指定したサイズ
No skin	Deviceで指定したサイズ
HVGA	320 x 480
QVGA	240 x 320
WQVGA400	240 x 400
WQVGA432	240 x 432
WSVGA	1024 x 600
WVGA800	480 x 800
WVGA854	480 x 854
WXGA720	720 x 1280
WXGA800	1280 x 800
//}

 * ディスプレイ上にインチ数を指定してエミュレーターを起動する

エミュレーターの作成時にスクリーンサイズを指定しますが、指定したサイズをそのままPCのディスプレイで表示すると、
場合によってははみ出てしまい、画面全体を表示できないことがあります。これは、エミュレーターで設定したピクセル密度と、PCディスプレイのピクセル密度が異なるためです。

この問題を解決するため、エミュレーターの起動時に、指定したインチ数でディスプレイに表示するための設定を行います。Android Virtual Device ManagerでStartボタンを押すと、@<img>{real-size}のダイアログが表示されます。ここでScale display to real sizeにチェックをつけ、
インチ数とディスプレイのdpiを指定してエミュレーターを起動します。もしディスプレイのdpi値が分からない場合は、入力欄の右側にある「？」をクリックしましょう。ディスプレイのインチ数と解像度を指定するだけで、自動的にdpi値を計算してくれます（@<img>{monitor-density}）。この設定により、たとえばディスプレイ上で4インチ（約10cm）のエミュレーターを起動することができます。

//image[real-size][インチ数を指定する][scale=0.35]{
//}

//image[monitor-density][ディスプレイのdpiを調べる][scale=0.35]{
//}

=== まとめ

ここまでユーザー体験を低下させず、より多くの端末に提供するための手法を紹介しました。すべての端末をサポートするのは不可能なので、「Android 4.0以上で、縦持ちのみサポートする」のようにサポートする範囲を決めて、その中でよりよいユーザー体験を提供するよう心がけましょう。
