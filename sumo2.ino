// Libraries for Display
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
Adafruit_SSD1306 display(4);
int counter = 0;
void setup() {
  // Display setup
  display.begin(SSD1306_SWITCHCAPVCC,
                0x3C, false);
  display.setTextSize(1);
  display.setTextColor(WHITE);
  //LED
  pinMode(12, OUTPUT); //Left LED
#define led1ON digitalWrite(12,HIGH);
#define led1OFF digitalWrite(12,LOW);
  pinMode(6, OUTPUT); //Right LED
#define led2ON digitalWrite(6,HIGH);
#define led2OFF digitalWrite(6,LOW);
  //Button
  pinMode(A2, INPUT);
  digitalWrite(A2, HIGH);
#define BTN !digitalRead(A2)
  //Line sensors
  pinMode(A4, INPUT);
#define SENL analogRead(A4)<80
  pinMode(A3, INPUT);
#define SENR analogRead(A3)<80
  //Proximity sensors
  pinMode(A1, INPUT);
#define PROX2 !digitalRead(A1)
  pinMode(A0, INPUT);
#define PROX1 !digitalRead(A0);
  //Motor pins
  //Left motor
  pinMode(5, OUTPUT);
  pinMode(11, OUTPUT);
  //Right Motor
  pinMode(9, OUTPUT);
  pinMode(10, OUTPUT);
}
//Motor functions
void Forward (int lSpeed, int rSpeed) {
  analogWrite(5, lSpeed);
  digitalWrite(11, LOW);
  analogWrite(9, rSpeed);
  digitalWrite(10, LOW);
}
void Backward (int lSpeed, int rSpeed) {
  analogWrite(11, lSpeed);
  digitalWrite(5, LOW);
  analogWrite(10, rSpeed);
  digitalWrite(9, LOW);
}
int senState = 0; //variable for sensors
void loop() {
  Forward(0, 0); //Stop motors
  delay(100);
  if (BTN) { //Turn on program with button
    while (BTN) {   //prevents multiple triggering
     }              //add code for switch bounce
    while (!BTN) { //stop robot if button is pushed again
      senState = 0; //reset variable to 0
      // Read sensors
      if (SENL) {
        led1ON; senState = senState + 1;
      } else {
        led1OFF;
      }
      if (SENR) {
        led2ON; senState = senState + 2;
      } else {
        led2OFF;
      }
      if (senState == 0) {
        if (PROX2) {
          senState = +4;
        }
      }
      
      //robot movement according to senState
      switch (senState) {
        case 0://no white line
          Forward(35, 35);
          break;
        case 1: //white line on left
          Backward(50, 50);
          delay(200);
          Forward(50, 0);
          delay(400);
          break;
        case 2://white line on right
          Backward(60, 60);
          delay(200);
          Forward(0, 60);
          delay(400);
          break;
        case 3://white line in front
          Backward(75, 75);
          delay(200);
          break;
        case 4://Middle proximity sensor
          Forward(170, 170);
          break;
      }
    }
    while (BTN) {}
  }
}
