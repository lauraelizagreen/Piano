/* 
 * Project Piano_Lyrics_OLED
 * Author: Laura Green
 * Date: 1/4/24
 * For comprehensive documentation and examples, please visit:
 * https://docs.particle.io/firmware/best-practices/firmware-template/
 */

// Include Particle Device OS APIs
#include "Particle.h"
#include "IoTClassroom_CNM.h"
#include "Adafruit_GFX.h"
#include "Adafruit_SSD1306.h"//specific OLED device


const int OLED_RESET=-1;
Adafruit_SSD1306 display(OLED_RESET);

const int NUMFLAKES=10;//like const (datatype=int?) NUMFLAKES=10; what is this constant?
const int XPOS=0; 
const int  YPOS=1;
const int DELTAY=2;
//char threeBlindMice[]={'THREE','BLIND','MICE'};//declare lyrics as array
//int i;//looping through lyrics how many times tones
SYSTEM_MODE(SEMI_AUTOMATIC);
SYSTEM_THREAD(ENABLED);


void setup() {
  Serial.begin(9600); 
  waitFor(Serial.isConnected,10000);

display.begin(SSD1306_SWITCHCAPVCC, 0x3C); //initialize with 12C address----not sure I understand this....??
void setRotation(uint8_t rotation);//how to use this to flip?
display.clearDisplay();   // clears the screen and buffer
}

// loop() runs over and over again, as quickly as it can execute.
void loop() {
  display.clearDisplay();
  display.setTextSize(3);//
  display.setTextColor(WHITE);
  display.setCursor(0,5);
  //display.printf("%c\n",threeBlindMice[0]); //song lyrics here "three blind mice"? make into array and loop through with each note
  display.printf("MANUAL MODE");
  //display.startscrollright(0x00, 0x0F);
  display.display();
  //delay(5000); 
  //display.clearDisplay();
  //display.setCursor(3,0);
  //display.printf("AUTOMATIC");
  //display.display();
  //delay(1000);

  // Example: Publish event to cloud every 10 seconds. Uncomment the next 3 lines to try it!
  // Log.info("Sending Hello World to the cloud!");
  // Particle.publish("Hello world!");
  // delay( 10 * 1000 ); // milliseconds and blocking - see docs for more info!
}
