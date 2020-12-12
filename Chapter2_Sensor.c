#include <Adafruit_NeoPixel.h>  // 네오픽셀 LED 사용하기 위해 헤더파일 선언
int RGB_PIN = 3;  // RGB 핀번호 (D3)
int NUMPIXELS = 8;  // 네오픽셀 개수
Adafruit_NeoPixel pixels = Adafruit_NeoPixel(NUMPIXELS, RGB_PIN, NEO_GRB + NEO_KHZ800);

#include <DHT.h> // DHT11 온도센서 사용하기 위해 헤더파일 선언
int DHT_PIN = 5;  // DHT 핀번호 (D5)
DHT dht(DHT_PIN, DHT11);

int TOUCH_PIN = 4;  // 터치센서 핀번호 (D4)
int TRIG_PIN = 10;  // 초음파센서 TRIG 핀번호 (D10)
int ECHO_PIN = 12;  // 초음파센서 ECHO 핀번호 (D12)
int CDS_PIN = A0;  // 조도센서 핀번호 (A0)
int POTEN_PIN = A5;  // 가변저항 핀번호 (A5)
int r, g, b, R, G, B, Mode, touch_count;  // 변수선언
int Mode_EA = 5;  // 모드 개수 (5개)
int temp_1 = 23, temp_2 = 26;  // 기준 온도값 변수
int cds_1 = 530, cds_2 = 1000;  // 기준 조도값 변수
int dis_1 = 100, dis_2 = 300, dis_3 = 500;  // 기준 거리값 변수
boolean touch = true, cds_RGB = true;  // 참,거짓(불리언) 변수
double cds_cur, cds_pre = cds_1;

void setup() {
  pinMode(TRIG_PIN, OUTPUT);  // TRIG핀(D7) 출력 모드
  pinMode(ECHO_PIN, INPUT);  // ECHO(D8) 입력 모드
  pixels.begin();  // 네오픽셀 제어 시작
  pixels.show();  // 네오픽셀 초기화
}


void loop() {
  Mode_set();  // Mode_set함수 불러오기
  int poten = analogRead(POTEN_PIN);  // 가변저항값 변수 poten에 저장

  if ( Mode == 0 || Mode == 1 || Mode == 2 ) {  // 가변저항으로 밝기조절 (모드1 or 모드2)
    for ( int i = 0; i < NUMPIXELS; i++ ) { // 네오픽셀 동작 (1번째부터 8번째까지)
      pixels.setPixelColor(i, pixels.Color( map(poten, 0, 1023, 0, r) , map(poten, 0, 1023, 0, g) , map(poten, 0, 1023, 0, b) ) );  // 네오픽셀 색 지정
      pixels.show(); // 네오픽셀 ON
    }
  }

  //---------------- 터치 센서 ----------------//
  if ( digitalRead(TOUCH_PIN) == 1 ) {  // 터치 센서 ON
    touch_count++;  // 터치 카운트 +1
    delay(10);  // 1ms 딜레이

    if ( touch_count >= 100 ) {  // 터치 카운트 100이상이면 (1초)
      if ( r == 0 && g == 0 && b == 0 ) {  // 전원 'OFF'면 'ON'
        r = 1;
      }

      else if ( r != 0 || g != 0 || b != 0 ) {  // 전원 'ON'이면 'OFF'
        r = 0;
        g = 0;
        b = 0;
        Mode = 0;
      }

      touch_count = 0;  // 터치 카운트 초기화
    }

    else if ( touch && ( r != 0 || g != 0 || b != 0 ) ) {  // 전원 'ON'이면 모드변경
      Mode++;

      if ( Mode > Mode_EA ) {
        cds_RGB = true;
        Mode = 1;
      }

      touch = false;
    } else;                                                   // 모드 변경
  }

  else {
    touch = true;
    touch_count = 0 ;
  }
  //---------------- 터치 센서 ----------------//
}

//---------------- 모드 동작 함수 ----------------//
void Mode_set() {
  if ( Mode == 1) {
    r = 210;
    g = 100;
    b = 10;
  }

  else if ( Mode == 2 ) {
    temp_set();
  }

  else if ( Mode == 3 ) {
    cds_set();
  }

  else if ( Mode == 4 ) {
    ultra_set();
  }

  else if ( Mode == 5 ) {
    temp_set();
    cds_set();
  }
}


//---------------- 온도 센서 함수 ----------------//
void temp_set() {
  int celsius = dht.readTemperature();  // 변수 celsius에 온도 값 저장

  if ( celsius < temp_1 ) {  // 온도값이 temp_1(23) 미만이면
    r = 0;  // 빨간색 0
    g = 0;  // 초록색 0
    b = 255;  // 파란색 255
  }

  else if ( temp_1 <= celsius && celsius < temp_2 ) {  // 온도값이 temp_1(23)이상 temp_2(26)미만이면
    r = 0;
    g = 255;
    b = 0;
  }

  else if ( celsius >= temp_2 ) {  // 온도값이 temp_2(26)이상이면
    r = 255;
    g = 0;
    b = 0;
  }
}


//---------------- 조도 센서 함수 ----------------//
void cds_set() {

  if ( cds_RGB ) {
    r = random(255);
    g = random(255);
    b = random(255);
    cds_RGB = false;
  }

  int cds = analogRead(CDS_PIN);
  cds_cur = (0.99 * cds_pre) + (0.01 * cds);
  cds_pre = cds_cur;
  cds = cds_cur;

  if ( cds <= cds_1 )
    cds = cds_1;

  else if ( cds_2 < cds )
    cds = cds_2;

  for (int i = 0; i < NUMPIXELS; i++) {
    pixels.setPixelColor(i, pixels.Color( map(cds, cds_1, cds_2, 0 , r) , map(cds, cds_1, cds_2, 0 , g) , map(cds, cds_1, cds_2, 0 , b) ) );
    pixels.show();
  }
}


//---------------- 초음파 센서 함수 ----------------//
void ultra_set() {
  static long dis_pre;
  digitalWrite(TRIG_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG_PIN, LOW);
  long duration = pulseIn(ECHO_PIN, HIGH);
  long distance = ((float)(340 * duration) / 1000) / 2 ;
  delay(50);

  if ( distance > 2000 )
    distance = dis_pre;

  if ( distance < dis_1 )
    distance = dis_1;

  else if ( distance > dis_3 )
    distance = dis_3;

  dis_pre = distance;

  if ( dis_1 <= distance && distance <= dis_2 ) {
    for (int i = 0; i < NUMPIXELS; i++) {
      pixels.setPixelColor(i, pixels.Color( 255 - map(distance, dis_1, dis_2, 0, 255) , map(distance, dis_1, dis_2, 0, 255) , 0) );
      pixels.show();
    }
  }
  else if ( dis_2 <= distance && distance <= dis_3 ) {
    for (int i = 0; i < NUMPIXELS; i++) {
      pixels.setPixelColor(i, pixels.Color( 0 , 255 - map(distance, dis_2, dis_3, 0, 255) , map(distance, dis_2, dis_3, 0, 255) ) );
      pixels.show();
    }
  }
}
