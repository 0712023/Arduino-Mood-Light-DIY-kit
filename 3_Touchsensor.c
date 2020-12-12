#include <Adafruit_NeoPixel.h>  // 네오픽셀 LED 사용하기 위해 헤더파일 선언
int RGB_PIN = 3;  // RGB 핀번호 (D3)
int NUMPIXELS = 8;  // 네오픽셀 개수
Adafruit_NeoPixel pixels = Adafruit_NeoPixel(NUMPIXELS, RGB_PIN, NEO_GRB + NEO_KHZ800);

int TOUCH_PIN = 4;  // 터치센서 핀번호 (D4)
int touch_count;
boolean up = true;

void setup() {
  pixels.begin();  // 네오픽셀 제어 시작
  pixels.show();  // 네오픽셀 초기화
}

void loop() {
  if ( digitalRead(TOUCH_PIN) == 1 ) {  // 터치 동안

    for ( int i = 0; i < NUMPIXELS; i++ ) { // 네오픽셀 동작 (1번째부터 8번째까지)
      pixels.setPixelColor(i, pixels.Color( touch_count , 0 , 0) );  // 네오픽셀 색 지정
      pixels.show(); // 네오픽셀 ON
    }  // 빨간색 LED의 밝기가 'touch_count'를 통해 0에서 255까지 증가했다가 감소

    if ( up ) {  // 'touch_count'증가
      touch_count++;
      if ( touch_count == 255 )
        up = false;
    }
    else if ( !up ) {  // 'touch_count'감소
      touch_count--;
      if ( touch_count == 0 )
        up = true;
    }
  }
}
