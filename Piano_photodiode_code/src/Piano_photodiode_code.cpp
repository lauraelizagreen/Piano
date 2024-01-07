/* 
 * Project Piano_photodiode
 * Author: Laura Green
 * Date: 1/4/24
 * For comprehensive documentation and examples, please visit:
 * https://docs.particle.io/firmware/best-practices/firmware-template/
 */

// Include Particle Device OS APIs
#include "Particle.h"
#include "IoTClassroom_CNM.h"
#include <neopixel.h>





SYSTEM_MODE(SEMI_AUTOMATIC);
//SYSTEM_MODE(AUTOMATIC);//for room control


SYSTEM_THREAD(ENABLED);
const int BULB=2;
const int PHOTODIODE=A1;
const int SERVPIN=A2;//has to be PWM
const int BUZZPIN= A5;//PWM?
const int NOTELEVEL=20;//how much light photodiode has to have to trigger hue light
const int NOTEDELAY=2000;//will need to be varied, so maybe later not constant? how long light stays on
const int DURATION=1000;//also may need to be varied-how long note plays, same as delay, so could be same variable
const int PIXELCOUNT=1;//use one neopixel to check hue light when not at FUSE
const int CNOTE=131;//freq for C notes could be h file later? or use pitch.h
const int DNOTE=147;//freq for D
const int ENOTE=165;//freq for E
const int FNOTE=175;//freq for F
const int GNOTE=196;//freq for G
const int ANOTE=220;//freq for A
const int BNOTE=247;//freq for B
const int HICNOTE=262;//freq for high C

const int CBUTTON=D4;

int lightLevelC;//for color of each note?
int color;
unsigned int timerStart, currentTime;

int cBState;
bool onOff;

Servo cServo;//create object ...servo class built into photon library
IoTTimer btwNoteTimer;
Adafruit_NeoPixel pixel(PIXELCOUNT, SPI1, WS2812B);
Button cButton(CBUTTON);
IoTTimer noteTimer;


void setup() {
  Serial.begin(9600); 
  waitFor(Serial.isConnected,15000);

  /*
  WiFi.on();  //comment out this section when not at FUSE
  WiFi.clearCredentials();
  WiFi.setCredentials("IoTNetwork");

  WiFi.connect();
  while(WiFi.connecting()) {
    Serial.printf(".");
  }  
  Serial.printf("\n\n");
  */

  pinMode(PHOTODIODE,INPUT);//photodiode
  pinMode(BUZZPIN,OUTPUT);//buzzer
  cServo.attach(SERVPIN);//motor for C key (or all keys?)
  onOff=false;

pixel.begin();//to initialize neopixel for home tests
pixel.setBrightness (20); 
pixel.show();
btwNoteTimer.startTimer(100);


  
}


void loop() {
  //setHue(BULB,false,50,255); //light off
  //lightLevelC=analogRead(PHOTODIODE); //read light through hole of scroll
 // Serial.printf("Light level is %i\n",lightLevelC); //what light level is usual?
  //if(lightLevelC>NOTELEVEL){
    //setHue(BULB,true,HueViolet,50,255);
    //cServo.write(90);//0-200 degrees  maybe will need supplemental power and how long will it take?
    //noteTimer.isTimerReady();
    //tone(BUZZPIN,CNOTE,DURATION);
    //delay(DURATION+1000);
  
if(cButton.isPressed()) {
tone(BUZZPIN,CNOTE);//stays on after press
//noteTimer.startTimer(5000);
}

//noteTimer.isTimerReady() 
  noTone(BUZZPIN);


 
}

  //btwNoteTimer.startTimer(NOTEDELAY); //how long light stays on/in between notes if looped
    
  //delay(1000);
   //setHue(BULB,false,50,255); //how to turn off btw and timing (set timer with variable as target?  )
    //delay(5000);
 

  

