/* 
 * Project Piano Test Code
 * Author: Laura Green  
 * Date: 12/15/23
 * For comprehensive documentation and examples, please visit:
 * https://docs.particle.io/firmware/best-practices/firmware-template/
 */

// Include Particle Device OS APIs
#include "Particle.h"
#include "IoTClassroom_CNM.h"
#include <neopixel.h>
#include <DFRobotDFPlayerMini.h>
#include "Adafruit_GFX.h"
#include "Adafruit_SSD1306.h"//specific OLED device

DFRobotDFPlayerMini myDFPlayer;//not sure about what this is function to print?  is it necessary?
void printDetail(uint8_t type, int value);
//#include "pitches.h" //use h file with note frequencies?

// Let Device OS manage the connection to the Particle Cloud
//SYSTEM_MODE(MANUAL);
SYSTEM_MODE(SEMI_AUTOMATIC);//when not at FUSE
const int BULB=2;
const int PHOTODIODE=A1;
const int SERVPIN=A2;//has to be PWM
const int BUZZPIN= A5;//PWM?
const int NOTELEVEL=100;//how much light photodiode has to have to trigger hue light
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
const int CBUTTON=pin #;//add pins here (are there enough?)
const int DBUTTON;
const int EBUTTON;
const int FBUTTON;
const int GBUTTON;
const int ABUTTON;
const int BBUTTON;
const int HIGHCBUTTON;

const int OLED_RESET=-1;
const int NUMFLAKES=10;//like const (datatype=int?) NUMFLAKES=10; what is this constant?
const int XPOS=0; 
const int  YPOS=1;
const int DELTAY=2;


int cBState, dBState, eBState, fBState, gBState, aBState, bBState, highCBState;
bool onOff;

char threeBlindMice[]={'THREE','BLIND','MICE'};

int lightLevelC;
int color;
unsigned int timerStart, currentTime;

Servo cServo;//create object ...servo class built into photon library
IoTTimer noteTimer;
Adafruit_NeoPixel pixel(PIXELCOUNT, SPI1, WS2812B);
Adafruit_SSD1306 display(OLED_RESET);
Button cButton(CBUTTON);//declaring all objects
Button dButton(DBUTTON);
Button eButton(EBUTTON);
Button fButton(FBUTTON);
Button gButton(GBUTTON);
Button aButton(ABUTTON);
Button bButton(BBUTTON);
Button highCButton(HIGHCBUTTON);
//SYSTEM_THREAD(ENABLED);

//SerialLogHandler logHandler(LOG_LEVEL_INFO);

// setup() runs once, when the device is first turned on
void setup() {
  Serial.begin(9600); 
  waitFor(Serial.isConnected,15000);

  display.begin(SSD1306_SWITCHCAPVCC, 0x3C); //initialize with 12C address----not sure I understand this....??
  display.clearDisplay();   // clears the screen and buffer
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
  cServo.attach(SERVPIN);//motor for C key

pixel.begin();//to initialize neopixel for home tests
pixel.setBrightness (20); 
pixel.show();
noteTimer.startTimer(100);

onOff= false;//initial value of onOff

  
 
}



// loop() runs over and over again, as quickly as it can execute.
void loop() {
  //setHue(BULB,false,50,255); //light off
  //lightLevelC=analogRead(PHOTODIODE); //read light through hole of scroll
  //Serial.printf("Light level is %i\n",lightLevelC); //what light level is usual?
  
  //if(lightLevelC>NOTELEVEL){
    //setHue(BULB,true,HueViolet,50,255);
    //cServo.write(90);//0-200 degrees  maybe will need supplemental power and how long will it take?
    noteTimer.isTimerReady();
    tone(BUZZPIN,CNOTE,DURATION);
    //delay(DURATION+1000);
    
  noteTimer.startTimer(NOTEDELAY); //how long light stays on/in between notes if looped
    
  //delay(1000);
   //setHue(BULB,false,50,255); //how to turn off btw and timing (set timer with variable as target?  )
    //delay(5000);

  display.setTextSize(1);//code to add my name and birthdate
  display.setTextColor(WHITE);
  display.setCursor(0,0);
  display.printf(threeBlindMice[i]\n); //song lyrics here "three blind mice"? make into array and loop through with each note
  display.display();
  delay(1000); 
  }
//to play mp3 tracks when button pressed
//piano1 1st folder, note tracks in alpha order
 
myDFPlayer.playFolder(1,1);  //play specific mp3 in SD:/15/004.mp3; Folder Name(1~99); File Name(1~255)
     
if(cButton.isPressed()) {
  myDFPlayer.playFolder(1,1);
}
if(dButton.isPressed()) {
  myDFPlayer.playFolder(1,2);
}

