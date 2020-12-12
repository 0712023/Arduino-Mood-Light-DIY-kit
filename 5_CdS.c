#include <Adafruit_NeoPixel.h>  // 네오픽셀 LED 사용하기 위해 헤더파일 선언
int RGB_PIN = 3;  // RGB 핀번호 (D3)
int NUMPIXELS = 8;  // 네오픽셀 개수
Adafruit_NeoPixel pixels = Adafruit_NeoPixel(NUMPIXELS, RGB_PIN, NEO_GRB + NEO_KHZ800);

int CDS_PIN = A0;

void setup() {
  pixels.begin();  // 네오픽셀 제어 시작
  pixels.show();  // 네오픽셀 초기화
  Serial.begin(9600);  // 시리얼 통신 시작
}

void loop() {
  int cds = analogRead(CDS_PIN);  // CDS_PIN(A0)에서 값 읽어들여 cds에 저장
  Serial.print("cds : ");
  Serial.print(cds);

  if (cds > 800) {  // cds값 800보다 크면 빨간색 LED ON
    for ( int i = 0; i < NUMPIXELS; i++ ) { // 네오픽셀 동작 (1번째부터 8번째까지)
      pixels.setPixelColor(i, pixels.Color( 255 , 0 , 0) );  // 네오픽셀 색 지정
      pixels.show(); // 네오픽셀 ON
    }
    Serial.println("     LED ON");
  }
  else {  // cds값 800이하이면 빨간색 LED OFF
    for ( int i = 0; i < NUMPIXELS; i++ ) { // 네오픽셀 동작 (1번째부터 8번째까지)
      pixels.setPixelColor(i, pixels.Color( 0 , 0 , 0) );  // 네오픽셀 색 지정
      pixels.show(); // 네오픽셀 ON
    }
    Serial.println("     LED OFF");
  }
  delay(200);
}
