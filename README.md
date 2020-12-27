# Arduino Mood Light DIY kit
## Project Synopsis
- 행사명 : 2019 대학생 재능봉사 캠프
- 주최 : <a href="https://www.kosaf.go.kr/">한국 장학재단</a>
- 진행 기간 : '19.8.5 ~ '19.8.9
- 내용
  -  한국장학재단에서 매년 주최하는 대학생 재능봉사 캠프에 참여하여 고등학생 멘티들에게 대학 진로에 대한 조언, 대학 생활에 대한 궁금증을 해소해 주는 등의 다양한 프로그램을 진행했습니다. 각각의 프로그램들은 나만의 공부 방법, 대학 학과 소개와 같이 개인 발표 프로그램과, ‘너의 꿈을 보여줘’, ‘힐링 토크 콘서트’ 등 팀워크 프로그램도 있었습니다.
  - 약 일주일간의 멘토링 기간 동안 진행했던 다양한 프로그램 중 '아두이노를 활용한 DIY 무드등 만들기'가 가장 핵심 프로그램이었습니다. 아두이노 및 코딩이 생소할 수도 있는 고등학생들에게 보다 가시적이고 직관적인 블록코딩을 활용하여 진입 장벽을 낮추는 데 초점을 맞추었습니다.
  - 일상 속에서 자주 쓰일 수 있는 소재인 무드등을 활용하여 멘티들에게 좀 더 편하게 다가갈 수 있었고 led의 빛 밝기 및 색 조절 프로그래밍을 통해 팀별로 각자의 무드등을 설계하는 재미 또한 더했습니다. 팀별로 교육을 통해 간단한 과자 등을 상으로 걸고 최종 경연 대회를 진행하여 프로그램의 몰입감이 한층 높아졌습니다.
### Tools
- <a href="https://www.arduino.cc/en/Guide/ArduinoUno">Arduino Uno</a><br>
<img src="https://upload.wikimedia.org/wikipedia/commons/thumb/8/87/Arduino_Logo.svg/1280px-Arduino_Logo.svg.png" width = 100><br>
전 세계에서 가장 강력하고 널리 쓰이는 오픈소스 하드웨어인 아두이노 우노는 센서 제어 및 간단한 IoT환경 프로그래밍에 최적화된 기기입니다. 이 프로젝트에서 아두이노 우노보드를 활용하여 무드등의 led를 다양한 방식으로 제어했습니다.<br><br>
- 무드등 Kit<br>
시중에서 판매되는 교육용 DIY 무드등 kit입니다. 이 kit안에는 아두이노 우노보드를 포함하여 breadboard, 케이블, led, 습도 센서, 터치 센서 등 다양한 IoT 센서 및 소자가 포함되어 있으므로 학생들에게 교육용으로 적합했습니다.<br><br>
- <a href="http://snap4arduino.rocks/">Snap4Arduino</a><br>
<img src="http://snap4arduino.rocks/img/logo.png"><br>
온라인 블록코딩을 활용해 학생들에게 코딩의 기초 개념을 알려주었습니다. 코딩이라는 게 처음 접했을 때 생소함 때문에 선뜻 와닿지 않는 경우가 있는데, 흔히 갖고 놀던 블럭놀이처럼 if문, for문, 변수, 대소비교 등 다양한 기초 코드를 블럭을 조립하듯 완성할 수 있었습니다.<br>
<img src="https://i.imgur.com/sguXikQ.png" width= 300><br><br>
- C

## Project Details
1. Potentiometer / 가변저항
  - 가변 저항을 이용해 led의 밝기를 변화
2. RGB1
  - 1초마다 R / G / B 색 변화
3. RGB2
  - 원하는 색으로 NeoPixel led 사용
4. Touchsensor
  - 터치 센서를 활용해 스위치로써 제어
5. DHT11 / 온습도계
  - 일정 온도 및 습도 환경에서 켜지는 무드등
6. Cds / 조도 센서
  - 일정 빛 세기 이하에서 켜지는 무드등
7. Ultra / 초음파 센서
  - 일정 거리 안의 물체를 감지하면 켜지는 무드등
8. Chapter1_RGBLED
  - LED를 무지개 색깔로 표현
9. Chapter2_Sensor
  - 다양한 센서를 활용한 무드등
10. Chapter3_Bluetooth
  - 블루투스를 활용하여 무드등 색 변경
11. MoodLight
  - 최종 무드등 완성 코드

## Demo
- 블루투스를 활용한 무드등 색 제어<br>
<img src="https://i.imgur.com/Ap9dDi0.png" width=500><br>
- 무드등 완성 작품 및 경연대회<br>
<img src="https://i.imgur.com/JBeIsJD.jpg" width=250><img src="https://i.imgur.com/EgPQHyC.jpg" width=250><br>
- 현장분위기<br>
<img src="https://i.imgur.com/aoKyQXV.jpg" width=500><br>

## Review
제가 처음 프로그래밍을 접한 때는 스마트팩토리 시스템을 구축하는 <a href="https://github.com/0712023/S_Hero">S-Hero</a> 프로젝트였습니다. 이 프로젝트를 통해 프로그래밍에 흥미와 재능이 있다는 것을 알 수 있었고, 지금까지도 이 프로젝트에 참여하기를 권유했던 <a href="https://github.com/alsrjs2441">친구</a>에게 감사하게 생각하고 있습니다. 이처럼 이 멘토링 프로젝트를 통해 한 명의 멘티라도 프로그래밍에 대해 흥미를 느낄 수 있었다면 이 프로그램은 성공했다고 생각합니다. 앞으로 많은 학생들이 프로그래밍의 재미에 푹 빠질 수 있다면 좋겠습니다.
