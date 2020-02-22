#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
Adafruit_SSD1306 display(4);
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
  pinMode(7,INPUT);
  digitalWrite(7, HIGH);
  #define DIP1 !digitalRead(7)
   pinMode(15,INPUT);
  digitalWrite(15, HIGH);
  #define DIP2 !digitalRead(15)
   pinMode(16,INPUT);
  digitalWrite(16, HIGH);
  #define DIP3 !digitalRead(16)
   pinMode(14,INPUT);
  digitalWrite(14, HIGH);
  #define DIP4 !digitalRead(14)
}
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
void loop() {
 Forward(0, 0); //Stop motors
  delay(100);
   if (BTN) { //Turn on program with button
    
 while(BTN){}
    while (!BTN) {
      if(!PROX2){
        Forward(35,35);
      }
      else{
        if(DIP1==1 && DIP2==0){
        Backward(50,50);
        delay(200);
        Forward(0,50);
        delay(400);
      }
      if(DIP1==0 && DIP2==1){
       Backward(70,70);
        delay(400);
        Forward(0,70);
        delay(600);
      }
      }
      }

while(BTN){}
   }
}
