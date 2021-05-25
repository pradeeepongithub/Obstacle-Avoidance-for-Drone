#include <EnableInterrupt.h>
#include<Servo.h>
Servo pitch;
Servo roll;

//#define SERIAL_PORT_SPEED 57600
#define RC_NUM_CHANNELS  2

#define RC_CH1  0
#define RC_CH2  1
//#define RC_CH3  2
//#define RC_CH4  3

#define RC_CH1_INPUT  A0
#define RC_CH2_INPUT  A1
//#define RC_CH3_INPUT  A4
//#define RC_CH4_INPUT  A5

int ultrafront, ultraback, ultraleft, ultraright;

uint16_t rc_values[RC_NUM_CHANNELS];
uint32_t rc_start[RC_NUM_CHANNELS];
volatile uint16_t rc_shared[RC_NUM_CHANNELS];

void rc_read_values() {
  noInterrupts();
  memcpy(rc_values, (const void *)rc_shared, sizeof(rc_shared));
  interrupts();
}

void calc_input(uint8_t channel, uint8_t input_pin) {
  if (digitalRead(input_pin) == HIGH) {
    rc_start[channel] = micros();
  } else {
    uint16_t rc_compare = (uint16_t)(micros() - rc_start[channel]);
    rc_shared[channel] = rc_compare;
  }
}

void calc_ch1() { calc_input(RC_CH1, RC_CH1_INPUT); }
void calc_ch2() { calc_input(RC_CH2, RC_CH2_INPUT); }
//void calc_ch3() { calc_input(RC_CH3, RC_CH3_INPUT); }
//void calc_ch4() { calc_input(RC_CH4, RC_CH4_INPUT); }

void setup() {
 
//pinMode(A0, INPUT);//roll in
 // pinMode(A1, INPUT);//pitch
  pinMode(2, INPUT);//front ultrasonic
  pinMode(3, INPUT);//back ultra
  pinMode(4, INPUT);//left ultra
  pinMode(5, INPUT);//right ultra
  pinMode(A2, OUTPUT);//roll out
  pinMode(A3, OUTPUT);//pitch out
  roll.attach(A2);
  pitch.attach(A3); 
  
  //Serial.begin(SERIAL_PORT_SPEED);

  pinMode(RC_CH1_INPUT, INPUT);
  pinMode(RC_CH2_INPUT, INPUT);
  //pinMode(RC_CH3_INPUT, INPUT);
  //pinMode(RC_CH4_INPUT, INPUT);

  enableInterrupt(RC_CH1_INPUT, calc_ch1, CHANGE);
  enableInterrupt(RC_CH2_INPUT, calc_ch2, CHANGE);
  //enableInterrupt(RC_CH3_INPUT, calc_ch3, CHANGE);
  //enableInterrupt(RC_CH4_INPUT, calc_ch4, CHANGE);
}

void loop() {
   rc_read_values();
   ultrasonic();
   //Serial.println(rc_values[RC_CH1]);
   /*Serial.print(ultrafront);Serial.print("  ");
   Serial.print(ultraback);Serial.print("  ");
   Serial.print(ultraleft);Serial.print("  ");
   Serial.print(ultraright);Serial.println("  ");*/
   //single obstacle
  while(ultrafront==1&&ultraback==0&&ultraleft==0&&ultraright==0)//front ultra
  {
   roll.writeMicroseconds(rc_values[RC_CH1]);
   pitch.writeMicroseconds(1674);//moves back
   ultrasonic();
  }  
  
   while(ultrafront==0&&ultraback==1&&ultraleft==0&&ultraright==0)//back ultra
  {
    roll.writeMicroseconds(rc_values[RC_CH1]);
    pitch.writeMicroseconds(1430);//forward
    ultrasonic();
    
  }
   while(ultrafront==0&&ultraback==0&&ultraleft==1&&ultraright==0)//left ultra
  {
    roll.writeMicroseconds(1674);
    pitch.writeMicroseconds(rc_values[RC_CH2]);//moves right
   ultrasonic();
    
  }
  while(ultrafront==0&&ultraback==0&&ultraleft==0&&ultraright==1)//right ultra
  {
    roll.writeMicroseconds(1430);
    pitch.writeMicroseconds(rc_values[RC_CH2]);//moves left
    ultrasonic();
  }
  //double obstacle
  while(ultrafront==1&&ultraback==0&&ultraleft==0&&ultraright==1)
  {
    roll.writeMicroseconds(1430);
    pitch.writeMicroseconds(rc_values[RC_CH2]);//moves left
    ultrasonic();
  }
  while(ultrafront==0&&ultraback==0&&ultraleft==1&&ultraright==1)
  {
    roll.writeMicroseconds(rc_values[RC_CH1]);
    pitch.writeMicroseconds(1674);//moves forward
    ultrasonic();
  }
  while(ultrafront==0&&ultraback==1&&ultraleft==1&&ultraright==0)
  {
    roll.writeMicroseconds(1674);
    pitch.writeMicroseconds(rc_values[RC_CH2]);//moves right
    ultrasonic();
  }
  while(ultrafront==1&&ultraback==0&&ultraleft==1&&ultraright==0)
  {
    roll.writeMicroseconds(1674);
    pitch.writeMicroseconds(rc_values[RC_CH2]);//moves right
    ultrasonic();
  }
  while(ultrafront==1&&ultraback==1&&ultraleft==0&&ultraright==0)
  {
    roll.writeMicroseconds(1430);
    pitch.writeMicroseconds(rc_values[RC_CH2]);//moves left
    ultrasonic();
  }
 while(ultrafront==0&&ultraback==0&&ultraleft==1&&ultraright==1)
  {
    roll.writeMicroseconds(rc_values[RC_CH1]);
    pitch.writeMicroseconds(1674);//moves back
    ultrasonic();
  }
  //three obstacle
  while(ultrafront==1&&ultraback==1&&ultraleft==0&&ultraright==1)
  {
    roll.writeMicroseconds(1430);
    pitch.writeMicroseconds(rc_values[RC_CH2]);//moves left
    ultrasonic();
  }
  while(ultrafront==0&&ultraback==1&&ultraleft==1&&ultraright==1)
  {
    roll.writeMicroseconds(rc_values[RC_CH1]);
    pitch.writeMicroseconds(1430);//moves forward
    ultrasonic();
  }
  while(ultrafront==1&&ultraback==1&&ultraleft==1&&ultraright==0)
  {
    roll.writeMicroseconds(1674);
    pitch.writeMicroseconds(rc_values[RC_CH2]);//moves right
    ultrasonic();
  }
  while(ultrafront==1&&ultraback==0&&ultraleft==1&&ultraright==1)
  {
    roll.writeMicroseconds(rc_values[RC_CH1]);
    pitch.writeMicroseconds(1674);//moves back
    ultrasonic();
  }
  /*while(ultrafront==1&&ultraback==1&&ultraleft==1&&ultraright==1)
  {
    roll.writeMicroseconds(rc_values[RC_CH1]);
    pitch.writeMicroseconds(rc_values[RC_CH2]);//moves back
    ultrasonic();
  }*/
    roll.writeMicroseconds(rc_values[RC_CH1]);
    pitch.writeMicroseconds(rc_values[RC_CH2]);
  
  }
  void ultrasonic()
  {
   ultrafront=digitalRead(2);delay(10);
   ultraback=digitalRead(3);delay(10);
   ultraleft=digitalRead(4);delay(10);
  ultraright=digitalRead(5);delay(10);
  }
  
  
