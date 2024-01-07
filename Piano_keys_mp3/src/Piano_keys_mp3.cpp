/* 
 * Project Piano_keys_mp3
 * Author: Laura Green
 * Date: 1/4/24
 * For comprehensive documentation and examples, please visit:
 * https://docs.particle.io/firmware/best-practices/firmware-template/
 */


#include "Particle.h"
#include "IoTClassroom_CNM.h"
#include "DFRobotDFPlayerMini.h"


SYSTEM_MODE(SEMI_AUTOMATIC);

// Run the application and system concurrently in separate threads
//SYSTEM_THREAD(ENABLED);
const int CBUTTON=D4;//add pins here (are there enough?)
//const int DBUTTON;
//const int EBUTTON;
//const int FBUTTON;
//const int GBUTTON;
//const int ABUTTON;
//const int BBUTTON;
//const int HIGHCBUTTON;

int cBState, dBState, eBState, fBState, gBState, aBState, bBState, highCBState;
bool onOff;
DFRobotDFPlayerMini myDFPlayer;
void printDetail(uint8_t type, int value);//not sure if needed


// Show system, cloud connectivity, and application logs over USB
// View logs with CLI using 'particle serial monitor --follow'
//SerialLogHandler logHandler(LOG_LEVEL_INFO);

// setup() runs once, when the device is first turned on
void setup() {
  Serial.begin(9600); 
  Serial1.begin(9600);
  waitFor(Serial.isConnected,15000);
  if (!myDFPlayer.begin(Serial1)) {  //Serial1 is name for TX RX
    Serial.println(F("Unable to begin:"));
    Serial.println(F("1.Please recheck the connection!"));
    Serial.println(F("2.Please insert the SD card!"));
    delay(10000);
    while(true);
  }
  Serial.println(F("DFPlayer Mini online."));

  myDFPlayer.volume(20);  //Set volume value. From 0 to 30
  myDFPlayer.play(1);  //Play the first mp3
  //delay(2000);

}

// loop() runs over and over again, as quickly as it can execute.
void loop() {
//static unsigned long timer = millis();

  //if (millis() - timer > 3000) {
    //timer = millis();
    //myDFPlayer.next();  //Play next mp3 every 3 second.
  
  
  //piano1 1st folder, note tracks in alpha order
  //myDFPlayer.EQ(DFPLAYER_EQ_NORMAL);
  //myDFPlayer.outputDevice(DFPLAYER_DEVICE_SD);
  //myDFPlayer.pause();
  //pausePlay=0;
  //myDFPlayer.volume(10);


  //delay(1000); 
//myDFPlayer.randomAll();

if (myDFPlayer.available()) {
    printDetail(myDFPlayer.readType(), myDFPlayer.read()); //Print the detail message from DFPlayer to handle different errors and states.
    myDFPlayer.play(1);  //Play the first mp3
    //myDFPlayer.playFolder(1,1);  //play specific mp3 in SD:/15/004.mp3; Folder Name(1~99); File Name(1~255)


}
}
 //to play mp3 tracks when button pressed 
 /*   
if(cButton.isPressed()) {
  myDFPlayer.playFolder(1,1);
}
*/
/*
if(dButton.isPressed()) {
  myDFPlayer.playFolder(1,2);
}
*/


  // Example: Publish event to cloud every 10 seconds. Uncomment the next 3 lines to try it!
  // Log.info("Sending Hello World to the cloud!");
  // Particle.publish("Hello world!");
  // delay( 10 * 1000 ); // milliseconds and blocking - see docs for more info!


void printDetail(uint8_t type, int value){
  switch (type) {
    case TimeOut:
      Serial.println(F("Time Out!"));
      break;
    case WrongStack:
      Serial.println(F("Stack Wrong!"));
      break;
    case DFPlayerCardInserted:
      Serial.println(F("Card Inserted!"));
      break;
    case DFPlayerCardRemoved:
      Serial.println(F("Card Removed!"));
      break;
    case DFPlayerCardOnline:
      Serial.println(F("Card Online!"));
      break;
      /*
    case DFPlayerCardInserted:
      Serial.println("USB Inserted!");
      break;
    case DFPlayerCardRemoved:
      Serial.println("USB Removed!");
      break;
      */
    case DFPlayerPlayFinished:
      Serial.print(F("Number:"));
      Serial.print(value);
      Serial.println(F(" Play Finished!"));
      break;
    case DFPlayerError:
      Serial.print(F("DFPlayerError:"));
      switch (value) {
        case Busy:
          Serial.println(F("Card not found"));
          break;
        case Sleeping:
          Serial.println(F("Sleeping"));
          break;
        case SerialWrongStack:
          Serial.println(F("Get Wrong Stack"));
          break;
        case CheckSumNotMatch:
          Serial.println(F("Check Sum Not Match"));
          break;
        case FileIndexOut:
          Serial.println(F("File Index Out of Bound"));
          break;
        case FileMismatch:
          Serial.println(F("Cannot Find File"));
          break;
        case Advertise:
          Serial.println(F("In Advertise"));
          break;
        default:
          break;
      }
      break;
    default:
      break;
  }

}
