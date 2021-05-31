/* Sweep
  by BARRAGAN <http://barraganstudio.com>
  This example code is in the public domain.

  modified 8 Nov 2013
  by Scott Fitzgerald
  http://www.arduino.cc/en/Tutorial/Sweep
*/

#include <Servo.h>
#include <SoftwareSerial.h>
/*


                  /\       ------       /\
                 /  \    /        \    /  \
                /    \  /          \  /    \
                       /     ^ ^    \
            /----------      | |     -----------\
           /           \            /            \
          /         /   \          /   \          \
                   /     \        /     \
                  /        ------        \
                  \                      /
                   \                    /

*/
SoftwareSerial bleSerial(A4, A5); // RX, TX

Servo front_1;//몸체 중심 가까운 다리
Servo front_2;
Servo front_3;
Servo front_4;
Servo front_5;
Servo front_6;

Servo back_1;//몸체 중심 바깥쪽 뒷 관절
Servo back_2;
Servo back_3;
Servo back_4;
Servo back_5;
Servo back_6;

int pin_1 = 2; //calibration for pin.
int pin_2 = 3; //calibration for pin.
int pin_3 = 4; //calibration for pin.
int pin_4 = 5; //calibration for pin.
int pin_5 = 6; //calibration for pin.
int pin_6 = 7; //calibration for pin.

int back_pin_1 = 8; //calibration for pin.
int back_pin_2 = 9; //calibration for pin.
int back_pin_3 = 10; //calibration for pin.
int back_pin_4 = 11; //calibration for pin.
int back_pin_5 = 12; //calibration for pin.
int back_pin_6 = 13; //calibration for pin.


int pos = 0;    // variable to store the servo position
int mid_point = 90;//all

int delay_time = 500;//i want mid point servo

int delay_org = 10;//i want mid point servo

int min_angle = 80;//in leg EX)front
int max_angle = 100;//in leg EX)front


int min_angle_for_out = 45;//out leg
int max_angle_for_our = 135;//out leg

int servo_num[12] = {2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13};

int count = 1;

char Trans_Test = 0;

void setup() {

  bleSerial.begin(9600);
  //2-13.
  //2,3,4, 5, 6, 7
  //8,9,10,11,12,13
  front_1.attach(pin_1);  // attaches the servo on pin 2 to the servo object
  front_2.attach(pin_2);  // attaches the servo on pin 3 to the servo object
  front_3.attach(pin_3);  // attaches the servo on pin 4 to the servo object
  front_4.attach(pin_4);  // attaches the servo on pin 5 to the servo object
  front_5.attach(pin_5);  // attaches the servo on pin 6 to the servo object
  front_6.attach(pin_6);  // attaches the servo on pin 7 to the servo object

  back_1.attach(back_pin_1);  // attaches the servo on pin 8 to the servo object
  back_2.attach(back_pin_2);  // attaches the servo on pin 9 to the servo object
  back_3.attach(back_pin_3);  // attaches the servo on pin 10 to the servo object
  back_4.attach(back_pin_4);  // attaches the servo on pin 11 to the servo object
  back_5.attach(back_pin_5);  // attaches the servo on pin 12 to the servo object
  back_6.attach(back_pin_6);  // attaches the servo on pin 13 to the servo object

  front_1.write(mid_point);
  front_2.write(mid_point);
  front_3.write(mid_point);
  front_4.write(mid_point);
  front_5.write(mid_point);
  front_6.write(mid_point);

  back_1.write(mid_point);
  back_2.write(mid_point);
  back_3.write(mid_point);
  back_4.write(mid_point);
  back_5.write(mid_point);
  back_6.write(mid_point);
}

void loop() {
        go();
}

// for embedded delay without stop
void delay_sec(uint16_t sec) {
  long prev = millis();
  while (millis() - prev <= sec);
}

void cali_angle() {
  front_1.write(min_angle);
  front_2.write(min_angle);
  front_3.write(mid_point);
  front_4.write(min_angle);
  front_5.write(min_angle);
  front_6.write(mid_point);
  delay_sec(1000);

  front_1.write(mid_point);
  front_2.write(mid_point);
  front_3.write(mid_point);
  front_4.write(mid_point);
  front_5.write(mid_point);
  front_6.write(mid_point);
  delay_sec(1000);

  front_1.write(max_angle);
  front_2.write(max_angle);
  front_3.write(mid_point);
  front_4.write(max_angle);
  front_5.write(max_angle);
  front_6.write(mid_point);
  delay_sec(1000);
}

void back()
{
  //후진은 전진과 반대로 오른쪽 부터
  for (int b = mid_point; b >= min_angle_for_out; b -= 2) {// 둘어올라기
    back_2.write(b);
    back_4.write(b);
    back_6.write(b);
    delay(delay_org);
  }
  for (int a = min_angle, b = max_angle; a <= max_angle, b >= min_angle; a += 2, b -= 2) { //포트중심(CCW,CW) -앞으로 들어올린 다리 앞으로 끌기
    front_6.write(a);
    front_2.write(b);
    front_4.write(b);
    delay(delay_org);
  }

  for (int b = min_angle_for_out; b <= max_angle_for_our; b += 2) {  //내리기
    back_2.write(b);
    back_4.write(b);
    back_6.write(b);
    delay(delay_org);
  }

  for (int a = max_angle, b = min_angle; a >= min_angle, b <= max_angle; a -= 2, b += 2) { //포트중심(CW) -앞으로 들어올린 다리 뒤로 끌기
    front_6.write(a);
    front_2.write(b);
    front_4.write(b);
    delay(delay_org);
  }


  for (int b = max_angle_for_our; b >= mid_point; b -= 2) {// 둘어올라기
    back_2.write(b);
    back_4.write(b);
    back_6.write(b);
    delay(delay_org);
  }

  for (int b = mid_point; b >= min_angle_for_out; b -= 2) {// 들어올리기
    back_1.write(b);
    back_3.write(b);
    back_5.write(b);
    delay(delay_org);
  }
  for (int a = max_angle, b = min_angle; a >= min_angle, b <= max_angle; a -= 2, b += 2) { //포트중심(CW) -앞으로 들어올린 다리 앞으로 끌기
    front_1.write(b);
    front_5.write(b);
    front_3.write(a);

    delay(delay_org);
  }
  /* for (int a = min_angle; a <= max_angle; a += 2) {  //포트중심(CCW) -앞으로 들어올린 다리 앞으로 끌기
     front_3.write(a);
     delay(15);
    }
  */
  for (int b = min_angle_for_out; b <= max_angle_for_our; b += 2) {  //내리기
    back_1.write(b);
    back_3.write(b);
    back_5.write(b);
    delay(delay_org);
  }
  for (int a = min_angle, b = max_angle; a <= max_angle, b >= min_angle; a += 2, b -= 2) { //포트중심(CCW) -앞으로 들어올린 다리 뒤로 끌기
    front_1.write(b);
    front_5.write(b);
    front_3.write(a);
    delay(delay_org);
  }
  /* for (int a = max_angle; a >= min_angle; a -= 2) {  //포트중심(CW) -앞으로 들어올린 다리 뒤로 끌기
     front_3.write(b);
     delay(15);
    }*/

  for (int b = max_angle_for_our; b >= mid_point; b -= 2) {// 들어올리기
    back_1.write(b);
    back_3.write(b);
    back_5.write(b);
    delay(delay_org);
  }
}

void go()
{

  /*
     기본자세
     업 모드
     앞 모드
     다운 모드
     뒤 모드
  */
  //  초기값은 미들

  for (int b = mid_point; b >= min_angle_for_out; b -= 2) {// 들어올리기
    back_1.write(b);
    back_3.write(b);
    back_5.write(b);
    delay(delay_org);
  }
  for (int a = max_angle, b = min_angle; a >= min_angle, b <= max_angle; a -= 2, b += 2) { //포트중심(CW) -앞으로 들어올린 다리 앞으로 끌기
    front_1.write(a);
    front_5.write(a);
    front_3.write(b);

    delay(delay_org);
  }
  for (int b = min_angle_for_out; b <= max_angle_for_our; b += 2) { //내리기
    back_1.write(b);
    back_3.write(b);
    back_5.write(b);

    delay(delay_org);
  }
  for (int a = min_angle, b = max_angle;  a <= max_angle, b >= min_angle;
       a += 2, b -= 2 ) { //포트중심(CCW) -앞으로 내린 다리 뒤로 끌기
    front_1.write(a);
    front_5.write(a);
    front_3.write(b);


    delay(delay_org);
  }
  for (int b = max_angle_for_our, a = min_angle_for_out; a <= max_angle_for_our , b >= mid_point; b -= 2, a += 2) { // 초기값 들어올리기
    back_1.write(b);
    back_3.write(b);
    back_5.write(b);

    delay(delay_org);
  }

  //left 2, right 1

  for (int b = mid_point; b >= min_angle_for_out; b -= 2) {// 둘어올라기
    back_2.write(b);
    back_4.write(b);
    back_6.write(b);
    delay(delay_org);
  }
  for (int a = min_angle, b = max_angle; a <= max_angle, b >= min_angle; a += 2, b -= 2) { //포트중심(CCW) -앞으로 들어올린 다리 앞으로 끌기
    front_6.write(b);
    front_2.write(a);
    front_4.write(a);
    delay(delay_org);
  }
  for (int b = min_angle_for_out; b <= max_angle_for_our; b += 2) {  //내리기
    back_2.write(b);
    back_4.write(b);
    back_6.write(b);
    delay(delay_org);
  }
  for (int a = max_angle, b = min_angle; a >= min_angle, b <= max_angle; a -= 2, b += 2) { //포트중심(CW) -앞으로 들어올린 다리 뒤로 끌기
    front_6.write(b);
    front_2.write(a);
    front_4.write(a);
    delay(delay_org);
  }


  for (int b = max_angle_for_our; b >= mid_point; b -= 2) {// 둘어올라기
    back_2.write(b);
    back_4.write(b);
    back_6.write(b);
    delay(delay_org);
  }
  //right 2, left 1
}

void turn_rudder_CW() { //for rudder right
  /*
     기본자세
     업 모드
     앞 모드
     다운 모드
     뒤 모드
  */
  //  초기값은 미들
  for (int b = mid_point; b >= min_angle_for_out; b -= 2) {// 들어올리기
    back_1.write(b);
    back_3.write(b);
    back_5.write(b);
    delay(delay_org);
  }
  for (int a = max_angle, b = min_angle; a >= min_angle, b <= max_angle; a -= 2, b += 2) { //포트중심 CCW - rudder
    front_1.write(a);
    front_5.write(a);
    front_3.write(a);

    delay(delay_org);
  }
  for (int b = min_angle_for_out; b <= max_angle_for_our; b += 2) {  //내리기
    back_1.write(b);
    back_3.write(b);
    back_5.write(b);
    delay(delay_org);
  }
  for (int a = min_angle, b = max_angle; a <= max_angle, b >= min_angle; a += 2, b -= 2) { //포트중심(CCW) -rudder 원상태
    front_1.write(a);
    front_5.write(a);
    front_3.write(a);
    delay(delay_org);
  }

  for (int b = max_angle_for_our; b >= mid_point; b -= 2) {// 들어올리기 - 레벨 복귀
    back_1.write(b);
    back_3.write(b);
    back_5.write(b);
    delay(delay_org);
  }
  //left 2, right 1

  for (int b = mid_point; b >= min_angle_for_out; b -= 2) {// 둘어올라기
    back_2.write(b);
    back_4.write(b);
    back_6.write(b);
    delay(delay_org);
  }
  for (int a = min_angle, b = max_angle; a <= max_angle, b >= min_angle; a += 2, b -= 2) { //포트중심(CCW) -앞으로 들어올린 다리 앞으로 끌기
    front_6.write(b);
    front_2.write(b);
    front_4.write(b);
    delay(delay_org);
  }
  for (int b = min_angle_for_out; b <= max_angle_for_our; b += 2) {  //내리기
    back_2.write(b);
    back_4.write(b);
    back_6.write(b);
    delay(delay_org);
  }

  for (int a = max_angle, b = min_angle; a >= min_angle, b <= max_angle; a -= 2, b += 2) { //포트중심(CW) -앞으로 들어올린 다리 뒤로 끌기
    front_6.write(b);
    front_2.write(b);
    front_4.write(b);
    delay(delay_org);
  }


  for (int b = max_angle_for_our; b >= mid_point; b -= 2) {// 둘어올라기
    back_2.write(b);
    back_4.write(b);
    back_6.write(b);
    delay(delay_org);
  }
  //right 2, left 1
}

void turn_rudder_CCW() { //for rudder left

  /*
     기본자세
     업 모드
     앞 모드
     다운 모드
     뒤 모드
  */
  //  초기값은 미들
  for (int b = mid_point; b >= min_angle_for_out; b -= 2) {// 들어올리기
    back_1.write(b);
    back_3.write(b);
    back_5.write(b);
    delay(delay_org);
  }
  for (int a = max_angle, b = min_angle; a >= min_angle, b <= max_angle; a -= 2, b += 2) { //포트중심 CCW - rudder
    front_1.write(b);
    front_5.write(b);
    front_3.write(b);

    delay(delay_org);
  }
  for (int b = min_angle_for_out; b <= max_angle_for_our; b += 2) {  //내리기
    back_1.write(b);
    back_3.write(b);
    back_5.write(b);
    delay(delay_org);
  }
  for (int a = min_angle, b = max_angle; a <= max_angle, b >= min_angle; a += 2, b -= 2) { //포트중심(CCW) -rudder 원상태
    front_1.write(b);
    front_5.write(b);
    front_3.write(b);
    delay(delay_org);
  }

  for (int b = max_angle_for_our; b >= mid_point; b -= 2) {// 들어올리기 - 레벨 복귀
    back_1.write(b);
    back_3.write(b);
    back_5.write(b);
    delay(delay_org);
  }
  //left 2, right 1

  for (int b = mid_point; b >= min_angle_for_out; b -= 2) {// 둘어올라기
    back_2.write(b);
    back_4.write(b);
    back_6.write(b);
    delay(delay_org);
  }
  for (int a = min_angle, b = max_angle; a <= max_angle, b >= min_angle; a += 2, b -= 2) { //포트중심(CCW) -앞으로 들어올린 다리 앞으로 끌기
    front_6.write(a);
    front_2.write(a);
    front_4.write(a);
    delay(delay_org);
  }
  for (int b = min_angle_for_out; b <= max_angle_for_our; b += 2) {  //내리기
    back_2.write(b);
    back_4.write(b);
    back_6.write(b);
    delay(delay_org);
  }

  for (int a = max_angle, b = min_angle; a >= min_angle, b <= max_angle; a -= 2, b += 2) { //포트중심(CW) -앞으로 들어올린 다리 뒤로 끌기
    front_6.write(a);
    front_2.write(a);
    front_4.write(a);
    delay(delay_org);
  }


  for (int b = max_angle_for_our; b >= mid_point; b -= 2) {// 둘어올라기
    back_2.write(b);
    back_4.write(b);
    back_6.write(b);
    delay(delay_org);
  }
  //right 2, left 1
}

//we need check for all servo angle. max/min.
void calibration(int num, int place) {
  switch (place) {//바깥쪽,안쪽
    case 1:
      switch (num) {//시계방향
        case 1:
          for (pos = min_angle; pos <= max_angle; pos += 1) { // goes from 0 degrees to max_angle degrees
            // in steps of 1 degree
            front_1.write(pos);              // tell servo to go to position in variable 'pos'
            delay(15);                       // waits 15ms for the servo to reach the position
          }
          for (pos = max_angle; pos >= min_angle; pos -= 1) { // goes from max_angle degrees to 0 degrees
            front_1.write(pos);              // tell servo to go to position in variable 'pos'
            delay(15);                       // waits 15ms for the servo to reach the position
          }

          front_1.write(mid_point);              // tell servo to go to position in variable 'pos'
          delay(delay_time);                       // waits 15ms for the servo to reach the position
          break;
        case 2://error
          for (pos = min_angle ; pos <= max_angle ; pos += 1) { // goes from 0 degrees to max_angle degrees
            // in steps of 1 degree
            front_2.write(pos);              // tell servo to go to position in variable 'pos'
            delay(15);                       // waits 15ms for the servo to reach the position
          }
          for (pos = max_angle; pos >= min_angle; pos -= 1) { // goes from max_angle degrees to 0 degrees
            front_2.write(pos);              // tell servo to go to position in variable 'pos'
            delay(15);                       // waits 15ms for the servo to reach the position
          }

          front_2.write(mid_point );            // tell servo to go to position in variable 'pos'
          delay(delay_time);                       // waits 15ms for the servo to reach the position
          break;
        case 3:
          for (pos = min_angle; pos <= max_angle; pos += 1) { // goes from 0 degrees to max_angle degrees
            // in steps of 1 degree
            front_3.write(pos);              // tell servo to go to position in variable 'pos'
            delay(15);                       // waits 15ms for the servo to reach the position
          }
          for (pos = max_angle; pos >= min_angle; pos -= 1) { // goes from max_angle degrees to 0 degrees
            front_3.write(pos);              // tell servo to go to position in variable 'pos'
            delay(15);                       // waits 15ms for the servo to reach the position
          }

          front_3.write(mid_point);              // tell servo to go to position in variable 'pos'
          delay(delay_time);                       // waits 15ms for the servo to reach the position
          break;
        case 4:
          for (pos = min_angle; pos <= max_angle; pos += 1) { // goes from 0 degrees to max_angle degrees
            // in steps of 1 degree
            front_4.write(pos);              // tell servo to go to position in variable 'pos'
            delay(15);                       // waits 15ms for the servo to reach the position
          }
          for (pos = max_angle; pos >= min_angle; pos -= 1) { // goes from max_angle degrees to 0 degrees
            front_4.write(pos);              // tell servo to go to position in variable 'pos'
            delay(15);                       // waits 15ms for the servo to reach the position
          }

          front_4.write(mid_point);              // tell servo to go to position in variable 'pos'
          delay(delay_time);                       // waits 15ms for the servo to reach the position
          break;
        case 5:
          for (pos = min_angle; pos <= max_angle; pos += 1) { // goes from 0 degrees to max_angle degrees
            // in steps of 1 degree
            front_5.write(pos);              // tell servo to go to position in variable 'pos'
            delay(15);                       // waits 15ms for the servo to reach the position
          }
          for (pos = max_angle; pos >= min_angle; pos -= 1) { // goes from max_angle degrees to 0 degrees
            front_5.write(pos);              // tell servo to go to position in variable 'pos'
            delay(15);                       // waits 15ms for the servo to reach the position
          }

          front_5.write(mid_point);              // tell servo to go to position in variable 'pos'
          delay(delay_time);                       // waits 15ms for the servo to reach the position
          break;
        case 6:
          for (pos = min_angle; pos <= max_angle; pos += 1) { // goes from 0 degrees to max_angle degrees
            // in steps of 1 degree
            front_6.write(pos);              // tell servo to go to position in variable 'pos'
            delay(15);                       // waits 15ms for the servo to reach the position
          }
          for (pos = max_angle; pos >= min_angle; pos -= 1) { // goes from max_angle degrees to 0 degrees
            front_6.write(pos);              // tell servo to go to position in variable 'pos'
            delay(15);                       // waits 15ms for the servo to reach the position
          }

          front_6.write(mid_point);              // tell servo to go to position in variable 'pos'
          delay(delay_time);                       // waits 15ms for the servo to reach the position
          break;
      } break;
    case 2:
      switch (num) {
        case 1:
          for (pos = min_angle; pos <= max_angle; pos += 1) { // goes from 0 degrees to max_angle degrees
            // in steps of 1 degree
            back_1.write(pos);              // tell servo to go to position in variable 'pos'
            delay(15);                       // waits 15ms for the servo to reach the position
          }
          for (pos = max_angle; pos >= min_angle; pos -= 1) { // goes from max_angle degrees to 0 degrees
            back_1.write(pos);              // tell servo to go to position in variable 'pos'
            delay(15);                       // waits 15ms for the servo to reach the position
          }

          back_1.write(mid_point);              // tell servo to go to position in variable 'pos'
          delay(delay_time);                       // waits 15ms for the servo to reach the position
          break;
        case 2:
          for (pos = min_angle; pos <= max_angle; pos += 1) { // goes from 0 degrees to max_angle degrees
            // in steps of 1 degree
            back_2.write(pos);              // tell servo to go to position in variable 'pos'
            delay(15);                       // waits 15ms for the servo to reach the position
          }
          for (pos = max_angle; pos >= min_angle; pos -= 1) { // goes from max_angle degrees to 0 degrees
            back_2.write(pos);              // tell servo to go to position in variable 'pos'
            delay(15);                       // waits 15ms for the servo to reach the position
          }

          back_2.write(mid_point);              // tell servo to go to position in variable 'pos'
          delay(delay_time);                       // waits 15ms for the servo to reach the position
          break;
        case 3:
          for (pos = min_angle; pos <= max_angle; pos += 1) { // goes from 0 degrees to max_angle degrees
            // in steps of 1 degree
            back_3.write(pos);              // tell servo to go to position in variable 'pos'
            delay(15);                       // waits 15ms for the servo to reach the position
          }
          for (pos = max_angle; pos >= min_angle; pos -= 1) { // goes from max_angle degrees to 0 degrees
            back_3.write(pos);              // tell servo to go to position in variable 'pos'
            delay(15);                       // waits 15ms for the servo to reach the position
          }

          back_3.write(mid_point);              // tell servo to go to position in variable 'pos'
          delay(delay_time);                       // waits 15ms for the servo to reach the position
          break;
        case 4:
          for (pos = min_angle; pos <= max_angle; pos += 1) { // goes from 0 degrees to max_angle degrees
            // in steps of 1 degree
            back_4.write(pos);              // tell servo to go to position in variable 'pos'
            delay(15);                       // waits 15ms for the servo to reach the position
          }
          for (pos = max_angle; pos >= min_angle; pos -= 1) { // goes from max_angle degrees to 0 degrees
            back_4.write(pos);              // tell servo to go to position in variable 'pos'
            delay(15);                       // waits 15ms for the servo to reach the position
          }

          back_4.write(mid_point);              // tell servo to go to position in variable 'pos'
          delay(delay_time);                       // waits 15ms for the servo to reach the position
          break;
        case 5:
          for (pos = min_angle; pos <= max_angle; pos += 1) { // goes from 0 degrees to max_angle degrees
            // in steps of 1 degree
            back_5.write(pos);              // tell servo to go to position in variable 'pos'
            delay(15);                       // waits 15ms for the servo to reach the position
          }
          for (pos = max_angle; pos >= min_angle; pos -= 1) { // goes from max_angle degrees to 0 degrees
            back_5.write(pos);              // tell servo to go to position in variable 'pos'
            delay(15);                       // waits 15ms for the servo to reach the position
          }

          back_5.write(mid_point);              // tell servo to go to position in variable 'pos'
          delay(delay_time);                       // waits 15ms for the servo to reach the position
          break;
        case 6:
          for (pos = min_angle; pos <= max_angle; pos += 1) { // goes from 0 degrees to max_angle degrees
            // in steps of 1 degree
            back_6.write(pos);              // tell servo to go to position in variable 'pos'
            delay(15);                       // waits 15ms for the servo to reach the position
          }
          for (pos = max_angle; pos >= min_angle; pos -= 1) { // goes from max_angle degrees to 0 degrees
            back_6.write(pos);              // tell servo to go to position in variable 'pos'
            delay(15);                       // waits 15ms for the servo to reach the position
          }

          back_6.write(mid_point);              // tell servo to go to position in variable 'pos'
          delay(delay_time);                       // waits 15ms for the servo to reach the position
          break;
      }
      break;
  }
}
