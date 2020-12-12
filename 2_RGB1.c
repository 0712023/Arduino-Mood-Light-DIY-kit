#include <Adafruit_NeoPixel.h>  // 네오픽셀 LED 사용하기 위해 헤더파일 선언
int RGB_PIN = 3;  // RGB 핀번호 (D3)
int NUMPIXELS = 8;  // 네오픽셀 개수
Adafruit_NeoPixel pixels = Adafruit_NeoPixel(NUMPIXELS, RGB_PIN, NEO_GRB + NEO_KHZ800);

void setup() {
  pixels.begin();  // 네오픽셀 제어 시작
  pixels.show();  // 네오픽셀 초기화
}

void loop() {
  for ( int i = 0; i < NUMPIXELS; i++ ) { // 네오픽셀 동작 (1번째부터 8번째까지)
    pixels.setPixelColor(i, 255 , 0 , 0 );  // 네오픽셀 색 지정
    pixels.show(); // 네오픽셀 ON
  }
  delay(1000);

  for ( int i = 0; i < NUMPIXELS; i++ ) { // 네오픽셀 동작 (1번째부터 8번째까지)
    pixels.setPixelColor(i, 0 , 255 , 0 );  // 네오픽셀 색 지정
    pixels.show(); // 네오픽셀 ON
  }
  delay(1000);

  for ( int i = 0; i < NUMPIXELS; i++ ) { // 네오픽셀 동작 (1번째부터 8번째까지)
    pixels.setPixelColor(i, 0 , 0 , 255 );  // 네오픽셀 색 지정
    pixels.show(); // 네오픽셀 ON
  }
  delay(1000);
}
