/*
 * RFC-2812: Internet Relay Chat: Client Protocol
 *
 * 2.3 Message
 * サーバーとクライアントは互いにメッセージを送り合う。
 * 後のセクションで説明するように、メッセージに有効なコマンドが含まれている場合、
 * クライアントは指定されたとおりの返信を期待すべきですが、返信をいつまでも待つことはお勧めできません；
 * クライアント、サーバー間、サーバー、サーバー間への通信は本質的に非同期です。
 * 各IRC メッセージは、prefix(オプション)、コマンド、コマンド・パラメーター(最大15個)の3つの部分から構成されます。
 * プレフィックス、コマンド、およびすべてのパラメータは、それぞれ1つのASCIIスペース文字(0x20)で区切られる。
 * prefixの存在は、先頭のASCIIコロン文字(':', 0x3b)1文字で示される。
 * コロンとprefixの間に空白があってはならない(MUST)。 
 * prefixは、サーバーがメッセージの本当の出所を示すために使われる。
 * prefixがメッセージにない場合、そのメッセージは受信元のコネクションから発信されたものとみなされる。
 * クライアントはメッセージを送るときにprefixを使うべきではありません(SHOULD NOT)。
 * もし使うのであれば、有効なprefixはそのクライアントに関連付けられた登録済みのニックネームだけです。
 *
 * コマンドは有効なIRCコマンドか、ASCIIテキストで表現された3桁の数字でなければならない(MUST)。
 *
 * IRCメッセージは常にCR-LF（キャリッジ・リターン-ライン・フィード）のペアで終端される文字の行であり、
 * これらのメッセージは、末尾のCR-LFを含むすべての文字を数えて、長さが512文字を超えてはならない（SHALL NOT）。
 * 従って、コマンドとそのパラメータに許される最大文字数は510文字である。
 * メッセージ行の続きの規定はない。
 * 現在の実装の詳細については、第６章「Current implementations」 を参照のこと。
 *
 * 2.3.1: Message format in Augmented BNF
 * プロトコル・メッセージは、オクテットの連続ストリームから抽出されなければならない。
 * 現在の解決策は、CRとLFという2つの文字をメッセージの区切り文字として指定することです。
 * 空のメッセージは黙って無視されるので、
 * 余計な問題を起こさずにメッセージ間でCR-LFシーケンスを使用することができます。
 *
 * 抽出されたメッセージは<prefix>、<command>、パラメーターのリスト(<params>)にパースされる。
 *
 *
 *
 *
 * この場合のAugmented BNF表現は次のようになる：
 *
 * message    = [ ":" prefix SPACE ] command [ params ] crlf
 *
 * prefix     = servername / ( nickname [ [ "!" user ] "@" host ] )
 *
 * command    = 1*letter / 3digit
 *
 * params     = *14( SPACE middle ) [ SPACE ":" trailing ]
 *            = / 14( SPACE middle ) [ SPACE [ ":" ] trailing ]
 *
 * nospcrlfcl = %x01-09 / %x0B-0C / %x0E-1F / %x21-39 / %x3B-FF ; any octet except NUL, CR, LF, " " and ":"
 *
 * middle     =  nospcrlfcl *( ":" / nospcrlfcl )
 * trailing   =  *( ":" / " " / nospcrlfcl )
 * SPACE      =  %x20        									; space character
 * crlf       =  %x0D %x0A   									; "carriage return" "linefeed"
 *
 * NOTE :
 * 1) パラメータリストを抽出した後、<middle>でマッチしても<trailing>でマッチしても、すべてのパラメータは等しくなる。
 *    <trailing>は、パラメータ内にスペースを入れるための構文上のトリックです。
 *
 * 2) NUL(%x00)文字はメッセージ・フレーミングでは特別な文字ではなく、基本的にパラメーターの中に入れることができますが、
 *    通常のCの文字列処理では余計な複雑さを引き起こすことになります。したがって、NUL はメッセージの中では使えません。
 *
 *
 *
 *
 * ほとんどのプロトコルメッセージは、リスト内の位置によって、抽出されたパラメータ文字列の追加のセマンティクスと構文を指定する。
 * 例えば、多くのサーバーコマンドは、コマンドの後の最初のパラメータがターゲットのリストであると仮定します：
 * target     =  nickname / server
 * msgtarget  =  msgto *( "," msgto )
 * msgto      =  channel / ( user [ "%" host ] "@" servername )
 * msgto      =/ ( user "%" host ) / targetmask
 * msgto      =/ nickname / ( nickname "!" user "@" host )
 * channel    =  ( "#" / "+" / ( "!" channelid ) / "&" ) chanstring [ ":" chanstring ]
 * servername =  hostname
 * host       =  hostname / hostaddr
 * hostname   =  shortname *( "." shortname )
 * shortname  =  ( letter / digit ) *( letter / digit / "-" ) *( letter / digit )	; as specified in RFC 1123 [HNAME]
 * hostaddr   =  ip4addr / ip6addr
 * ip4addr    =  1*3digit "." 1*3digit "." 1*3digit "." 1*3digit
 * ip6addr    =  1*hexdigit 7( ":" 1*hexdigit )
 * ip6addr    =/ "0:0:0:0:0:" ( "0" / "FFFF" ) ":" ip4addr
 * nickname   =  ( letter / special ) *8( letter / digit / special / "-" )
 * targetmask =  ( "$" / "#" ) mask													; see details on allowed masks in section 3.3.1
 * chanstring =  %x01-07 / %x08-09 / %x0B-0C / %x0E-1F / %x21-2B
 * chanstring =/ %x2D-39 / %x3B-FF													; any octet except NUL, BELL, CR, LF, " ", "," and ":"
 * channelid  = 5( %x41-5A / digit )   ; 5( A-Z / 0-9 )
 *
 * その他のパラメータ構文は以下の通り：
 * user       =  1*( %x01-09 / %x0B-0C / %x0E-1F / %x21-3F / %x41-FF )				; any octet except NUL, CR, LF, " " and "@"
 * key        =  1*23( %x01-05 / %x07-08 / %x0C / %x0E-1F / %x21-7F )				; any 7-bit US_ASCII character, except NUL, CR, LF, FF, h/v TABs, and " "
 * letter     =  %x41-5A / %x61-7A       ; A-Z / a-z
 * digit      =  %x30-39                 ; 0-9
 * hexdigit   =  digit / "A" / "B" / "C" / "D" / "E" / "F"
 * special    =  %x5B-60 / %x7B-7D													; "[", "]", "\", "`", "_", "^", "{", "|", "}"
 *
 * NOTE:
 * 1) <hostaddr>構文は、IPアドレスに従うべき書式を示すことを唯一の目的として、ここで与えられている。
 *    これは、このプロトコルの唯一の実装が、基礎となるネットワークプロトコルとしてTCP/IPを使用しているという事実を反映していますが、
 *    他のプロトコルの使用を妨げるものではありません。
 * 2) <ホスト名>の長さは最大63文字です。これはプロトコルの制限であり、インターネットのホスト名(特に)は長くなる可能性があるからです。
 *    IRCメッセージの長さは512文字に制限されているので、このような制限が必要なのです。
 *    ホスト名が63文字より長いホストから接続するクライアントは、ホスト名の代わりにホスト(数字)アドレスを使って登録されます。
 * 3) このドキュメントの以下のセクションで使用されているいくつかのパラメータは、便宜上使用されている名前以外に特別なものがないため、ここでは定義されていない。
 *    これらのパラメータは<params>で定義されている一般的な構文に従う。
 */

