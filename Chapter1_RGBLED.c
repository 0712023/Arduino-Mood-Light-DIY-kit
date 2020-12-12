#include <MsTimer2.h>  // MsTimer2 라이브러리 사용위한 헤더파일 선언
#include <Adafruit_NeoPixel.h>  // 네오픽셀 LED 사용하기 위해 헤더파일 선언
int RGB_PIN = 3;  // RGB 핀번호 (D3)
int NUMPIXELS = 8;  // 네오픽셀 개수
Adafruit_NeoPixel pixels = Adafruit_NeoPixel(NUMPIXELS, RGB_PIN, NEO_GRB + NEO_KHZ800);

int TOUCH_PIN = 4;  // 터치센서 핀번호 (D4)
int POTEN_PIN = A5;  // 가변저항 핀번호 (A5)
int Mode_EA = 6;  // 모드 개수 (6개)
int random_ms = 200;  // 모드5 : 무작위 색 변화 딜레이 설정 200ms(0.2초)
int rainbow[6][3] = {
  {255, 0, 0},     //빨
  {255, 50, 0},    //주
  {255, 150, 0},   //노
  {0, 255, 0},     //초
  {0, 0, 255},     //파
  {100, 0, 200},   //보
}; // 모드6 : 무지개 색 배열 선언

int r = 0 , g = 0 , b = 0, Mode, touch_count, rainbow_count, rain;  // 변수 선언
boolean touch = true, Mode_5 = true, up = true;  // 참,거짓 판별위한 변수 선언

void setup() {
  pixels.begin();  // 네오픽셀 제어 시작
  pixels.show();  // 네오픽셀 초기화
}


void loop() {
  Mode_set();  // 모드 함수 불러오기
  int poten = analogRead(POTEN_PIN);  // 가변저항 값 변수 poten에 저장

  if ( Mode != 6 ) {
    for ( int i = 0; i < NUMPIXELS; i++ ) { // 네오픽셀 동작 (1번째부터 8번째까지)
      pixels.setPixelColor(i, pixels.Color( map(poten, 0, 1023, 0, r) , map(poten, 0, 1023, 0, g) , map(poten, 0, 1023, 0, b) ) );  // 네오픽셀 색 지정
      pixels.show(); // 네오픽셀 ON
    }
    rain = 0;
  }

  if ( digitalRead(TOUCH_PIN) == 1 ) {
    touch_count++;
    delay(10);

    if ( touch_count >= 100 ) {
      if ( r == 0 && g == 0 && b == 0 ) {
        r = 255;
        //        Serial.println("전원 ON");
      }                                                    // 전원 ON

      else {
        r = 0;
        g = 0;
        b = 0;
        Mode = 0;
      }                                                   // 전원 OFF
      touch_count = 0;
    }

    else if ( touch && ( r != 0 || g != 0 || b != 0 ) ) {
      Mode++;

      if ( Mode > Mode_EA ) {
        Mode = 1;
      }

      touch = false;
    }                                                   // 모드 변경
  }

  else {
    touch = true;
    touch_count = 0;
  }

}

void Mode_set() {
  if ( Mode == 1) {
    r = 210;
    g = 100;
    b = 10;
  }

  else if ( Mode == 2 ) {
    r = 255;
    g = 20;
    b = 180;
  }

  else if ( Mode == 3 ) {
    r = 65;
    g = 255;
    b = 20;
  }

  else if ( Mode == 4 ) {
    r = 65;
    g = 216;
    b = 255;
  }

  else if ( Mode == 5 ) {
    if ( Mode_5 ) {
      MsTimer2::set(random_ms, random_set);
      MsTimer2::start();
      Mode_5 = false;
    }
  }

  else if ( Mode == 6 ) {
    if ( !Mode_5 ) {
      MsTimer2::stop();
      Mode_5 = true;
    }

    for ( int i = 0; i < NUMPIXELS; i++ ) { // 네오픽셀 동작 (1번째부터 8번째까지)
      pixels.setPixelColor(i, pixels.Color( map(rainbow_count, 0, 1023, 0, rainbow[rain][0]) , map(rainbow_count, 0, 1023, 0, rainbow[rain][1]) , map(rainbow_count, 0, 1023, 0, rainbow[rain][2]) ) );  // 네오픽셀 색 지정
      pixels.show(); // 네오픽셀 ON
    }

    if ( up ) {
      rainbow_count++;
      delayMicroseconds(500);
      if ( rainbow_count == 1023 )
        up = false;
    }

    else if ( !up ) {
      rainbow_count--;
      delayMicroseconds(2000);
      if ( rainbow_count == 0 ) {
        up = true;
        rain++;
        if ( rain == 6)
          rain = 0;
      }
    }
  }
}

void random_set() {
  r = random(255);
  g = random(255);
  b = random(255);
}
