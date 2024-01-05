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

  myDFPlayer.volume(10);  //Set volume value. From 0 to 30
  myDFPlayer.play(1);  //Play the first mp3

}

// loop() runs over and over again, as quickly as it can execute.
void loop() {
  
  //piano1 1st folder, note tracks in alpha order
  myDFPlayer.EQ(DFPLAYER_EQ_NORMAL);
  myDFPlayer.outputDevice(DFPLAYER_DEVICE_SD);
  //myDFPlayer.pause();
  //pausePlay=0;
  myDFPlayer.volume(10);

//myDFPlayer.play(1);  //Play the first mp3
  //delay(1000); 
//myDFPlayer.randomAll();
myDFPlayer.playFolder(1,1);  //play specific mp3 in SD:/15/004.mp3; Folder Name(1~99); File Name(1~255)

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
}
