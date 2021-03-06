// フォントライブラリ利用サンプル
// 作成 2016/07/02 by Tamakichi
//

#include <espfonts.h>

//
// ビットパターン表示
// d: 8ビットパターンデータ
//
void bitdisp(uint8_t d) {
  for (uint8_t i=0; i<8;i++) {
    if (d & 0x80>>i) 
      Serial.print("#");
    else
      Serial.print(".");
  }
}

//
// フォントデータの表示
// buf(in) : フォント格納アドレス
//
void fontdisp2(uint8_t* buf) {
  uint8_t bn= ESPfonts.getRowLength();                // 1行当たりのバイト数取得
  Serial.print(ESPfonts.getWidth(),DEC);             // フォントの幅の取得
  Serial.print("x");      
  Serial.print(ESPfonts.getHeight(),DEC);            // フォントの高さの取得
  Serial.print(" ");      
  Serial.println((uint16_t)ESPfonts.getCode(), HEX); // 直前し処理したフォントのUTF16コード表示

  for (uint8_t i = 0; i < ESPfonts.getLength(); i += bn ) {
      for (uint8_t j = 0; j < bn; j++) {
        bitdisp(buf[i+j]);
      }
      Serial.println("");
  }
  Serial.println("");
} 

//
// 指定した文字列を指定したサイズで表示する
// pUTF8(in) UTF8文字列
// sz(in)    フォントサイズ(8,10,12,14,16,20,24)
//
void fontDump(char* pUTF8, uint8_t sz) {
  uint8_t buf[MAXFONTLEN]; // フォントデータ格納アドレス(最大24x24/8 = 72バイト)

  ESPfonts.open();                                   // フォントのオープン
  ESPfonts.setFontSize(sz);                          // フォントサイズの設定
  while ( pUTF8 = ESPfonts.getFontData(buf, pUTF8) ) // フォントの取得
    fontdisp2(buf);                                  // フォントパターンの表示
  ESPfonts.close();                                  // フォントのクローズ
}

void setup() {
  Serial.begin(115200);                   // シリアル通信の初期化
  ESPfonts.init();                         // フォント管理の初期化
  Serial.println(F("ESPfonts liblary"));

  fontDump("色は",16);
  fontDump("にほえど",20);
  fontDump("ちぬるを", 24);
}

void loop() {
}
