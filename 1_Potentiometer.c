int LED = 9; // 변수 LED를 9로 선언

void setup() {
  Serial.begin(9600); // 시리얼 통신 시작
  pinMode(LED, OUTPUT); // 9번 핀을 출력으로 설정
}

void loop() {
  int val = analogRead(A5) / 4; // 변수 val 값을 아날로그 핀 5(A5)에서 읽은값(max = 1024) / 4 (max = 255)
  Serial.println(val); // 시리얼 모니터로 변수 val 값을 출력
  analogWrite(LED, val); // 변수 val값을 9번핀으로 보내 출력
}
