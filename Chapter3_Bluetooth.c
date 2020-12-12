#include <SoftwareSerial.h>
SoftwareSerial BT(8, 7);

#include <Adafruit_NeoPixel.h>  // 네오픽셀 LED 사용하기 위해 헤더파일 선언
int RGB_PIN = 3;  // RGB 핀번호 (D3)
int NUMPIXELS = 8;  // 네오픽셀 개수
Adafruit_NeoPixel pixels = Adafruit_NeoPixel(NUMPIXELS, RGB_PIN, NEO_GRB + NEO_KHZ800);

String RGB = "";
boolean RGB_Completed = false;

void setup() {
  BT.begin(9600);
  RGB.reserve(30);
  pixels.begin();  // 네오픽셀 제어 시작
  pixels.show();  // 네오픽셀 초기화
}

void loop() {
  while (BT.available()) {
    char ReadChar = (char)BT.read();

    if (ReadChar == ')') {
      RGB_Completed = true;
    }

    else {
      RGB += ReadChar;
    }
  }

  if (RGB_Completed) {
    rgb_set();
    RGB = "";
    RGB_Completed = false;
  }
}

void rgb_set() {
  int SP1 = RGB.indexOf(' ');
  int SP2 = RGB.indexOf(' ', SP1 + 1);
  int SP3 = RGB.indexOf(' ', SP2 + 1);
  String Red = RGB.substring(0, SP1);
  String Green = RGB.substring(SP1 + 1, SP2);
  String Blue = RGB.substring(SP2 + 1, SP3);

  for ( int i = 0; i < NUMPIXELS; i++ ) { // 네오픽셀 동작 (1번째부터 8번째까지)
    pixels.setPixelColor(i, Red.toInt() , Green.toInt(), Blue.toInt() ); // 네오픽셀 색 지정
    pixels.show(); // 네오픽셀 ON
  }
}
