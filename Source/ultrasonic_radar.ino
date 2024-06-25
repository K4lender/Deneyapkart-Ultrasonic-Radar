#include <deneyap.h>
#include <Deneyap_Servo.h>
//#include <Deneyap_MesafeOlcerIsikAlgilayici.h>
#include <Deneyap_OLED.h>
#include <HCSR04.h>


#define trig D0
#define echo D1


//ProximityAL yakinlik;
UltraSonicDistanceSensor distanceSensor(trig, echo);
Servo servo;
OLED oled;

int mesafe;
uint16_t pos;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  //yakinlik.begin(0x23);
  
  servo.attach(D4);

  oled.begin(0x7A);
  oled.clearDisplay();
  oled.setTextXY(0,0);
  oled.putString("*Deneyap Radar*");
  oled.setTextXY(7,0);
  oled.putString("****************");
}

void loop() {
  // put your main code here, to run repeatedly:
  for(pos = 0; pos < 180; ++pos){
    servo.write(pos);
    //mesafe = yakinlik.getPSvalue();
    //mesafe = map(mesafe, 0, 2047, 2047, 0);
    mesafe = distanceSensor.measureDistanceCm();
    Serial.print("Mesafe = ");
    Serial.println(mesafe);
    if(pos % 2 == 0){
      oled.setTextXY(3,0);
      oled.putString("Mesafe = ");
      oled.setTextXY(3,9);
      oled.putFloat(mesafe);
    }
    //oled.setHorizontalScrollProperties(Scroll_Right, 0, 0, Scroll_5Frames);
    //oled.activateScroll();
    delay(50);
  }

  for(pos = 180; pos > 0; --pos){
    servo.write(pos);

    //mesafe = yakinlik.getPSvalue();
    //map(mesafe, 0, 2047, 2047, 0);
    mesafe = distanceSensor.measureDistanceCm();
    Serial.print("Mesafe = ");
    Serial.println(mesafe);
    if(pos % 2 == 0){
      oled.setTextXY(3,0);
      oled.putString("Mesafe = ");
      oled.setTextXY(3,9);
      oled.putFloat(mesafe);
    }
    //oled.setHorizontalScrollProperties(Scroll_Right, 0, 0, Scroll_5Frames);
    //oled.activateScroll();
    delay(50);
  }
}
