#include <MsTimer2.h>
#include <SoftwareSerial.h>
SoftwareSerial BT(8, 7);

#include <Adafruit_NeoPixel.h>  // 네오픽셀 LED 사용하기 위해 헤더파일 선언
int RGB_PIN = 3;  // RGB 핀번호 (D3)
int NUMPIXELS = 8;  // 네오픽셀 개수
Adafruit_NeoPixel pixels = Adafruit_NeoPixel(NUMPIXELS, RGB_PIN, NEO_GRB + NEO_KHZ800);

#include <DHT.h> // DHT11 온도센서 사용하기 위해 헤더파일 선언
int DHT_PIN = 5;  // DHT 핀번호 (D5)
DHT dht(DHT_PIN, DHT11);

int TRIG_PIN = 10;  // 초음파센서 TRIG 핀번호 (D10)
int ECHO_PIN = 12;  // 초음파센서 ECHO 핀번호 (D12)
int CDS_PIN = A0;  // 조도센서 핀번호 (A0)
int temp_1 = 23, temp_2 = 26;  // 기준 온도값 변수
int cds_1 = 530, cds_2 = 950;  // 기준 조도값 변수
int dis_1 = 100, dis_2 = 300, dis_3 = 500;  // 기준 거리값 변수
int r, g, b, celsius; // 변수 선언
double cds_cur, cds_pre = cds_1;
boolean DEBUG = true, RGB_Completed = false;
int rainbow[6][3] = {
  {255, 0, 0},     //빨
  {255, 50, 0},    //주
  {255, 150, 0},   //노
  {0, 255, 0},     //초
  {0, 0, 255},     //파
  {100, 0, 200},   //보
};  // 무지개 색 배열 선언
String RGB = "";


void setup() {
  pinMode(TRIG_PIN, OUTPUT);  // TRIG핀(D7) 출력 모드
  pinMode(ECHO_PIN, INPUT);  // ECHO(D8) 입력 모드
  pixels.begin();  // 네오픽셀 제어 시작
  pixels.show();  // 네오픽셀 초기화
  BT.begin(9600);
  RGB.reserve(30);
}


void loop() {
  while (BT.available()) {
    char ReadChar = (char)BT.read();

    if (ReadChar == ')')
      RGB_Completed = true;
    else
      RGB += ReadChar;
  }

  if (RGB_Completed) {
    DEBUG = true;
    MsTimer2::stop();

    if (RGB == "CH1_5") {
      MsTimer2::set(200, random_set);
      MsTimer2::start();
    }
    else if (RGB == "CH1_6") {
      MsTimer2::set(50, rain_set);
      MsTimer2::start();
    }
    else if (RGB == "CH2_2") {
      DEBUG = false;
      MsTimer2::set(1000, temp_set);
      MsTimer2::start();
    }
    else if (RGB == "CH2_3") {
      r = random(255);
      g = random(255);
      b = random(255);
      MsTimer2::set(60, cds_set);
      MsTimer2::start();
    }
    else if (RGB == "CH2_4") {
      MsTimer2::set(90, ultra_set);
      MsTimer2::start();
    }
    else rgb_set();

    RGB = "";
    RGB_Completed = false;
  }

  if ( !DEBUG )
    celsius = dht.readTemperature();  // 변수 celsius에 온도 값 저장
}


//------------------ RGB 동작 함수 ------------------//
void rgb_set() {
  int SP1 = RGB.indexOf(' ');
  int SP2 = RGB.indexOf(' ', SP1 + 1);
  int SP3 = RGB.indexOf(' ', SP2 + 1);
  int SP4 = RGB.indexOf(' ', SP3 + 1);
  String Red = RGB.substring(0, SP1);
  String Green = RGB.substring(SP1 + 1, SP2);
  String Blue = RGB.substring(SP2 + 1, SP3);
  String Bright = RGB.substring(SP3 + 1, SP4);

  for ( int i = 0; i < NUMPIXELS; i++ ) { // 네오픽셀 동작 (1번째부터 8번째까지)
    pixels.setPixelColor(i, pixels.Color( map(Bright.toInt(), 0, 255, 0, Red.toInt()), map(Bright.toInt(), 0, 255, 0, Green.toInt()), map(Bright.toInt(), 0, 255, 0, Blue.toInt()) ) ); // 네오픽셀 색 지정
    pixels.show(); // 네오픽셀 ON
  }
}


//---------------- 무작위 색 변화 동작 함수 ----------------//
void random_set() {
  r = random(255);
  g = random(255);
  b = random(255);

  for ( int i = 0; i < NUMPIXELS; i++ ) { // 네오픽셀 동작 (1번째부터 8번째까지)
    pixels.setPixelColor(i, pixels.Color( r, g, b ) );  // 네오픽셀 색 지정
    pixels.show(); // 네오픽셀 ON
  }
}


//---------------- 무지개 색 변화 동작 함수 ----------------//
void rain_set() {
  static int rainbow_count;
  static int rain;

  if ( DEBUG ) {
    rainbow_count += 2;
    if ( rainbow_count >= 100 ) {
      rainbow_count = 100;
      DEBUG = false;
    }
  }
  else if ( !DEBUG ) {
    rainbow_count -= 1;
    if ( rainbow_count == 0 ) {
      DEBUG = true;
      rain++;
      if ( rain == 6)
        rain = 0;
    }
  }

  for ( int i = 0; i < 8; i++ ) { // 네오픽셀 동작 (1번째부터 8번째까지)
    pixels.setPixelColor(i, pixels.Color( map(rainbow_count, 0, 100, 0, rainbow[rain][0]) , map(rainbow_count, 0, 100, 0, rainbow[rain][1]) , map(rainbow_count, 0, 100, 0, rainbow[rain][2]) ) );  // 네오픽셀 색 지정
    pixels.show(); // 네오픽셀 ON
  }

}


//------------------- 온도 센서 함수 -------------------//
void temp_set() {

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

  for ( int i = 0; i < NUMPIXELS; i++ ) { // 네오픽셀 동작 (1번째부터 8번째까지)
    pixels.setPixelColor(i, pixels.Color( r, g, b ) );  // 네오픽셀 색 지정
    pixels.show(); // 네오픽셀 ON
  }
}


//---------------- 조도 센서 함수 ----------------//
void cds_set() {
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
