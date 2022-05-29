
#include <Adafruit_Fingerprint.h>   //https://github.com/adafruit/Adafruit-Fingerprint-Sensor-Library
#include <HardwareSerial.h>
#include <Adafruit_GFX.h>           //https://github.com/adafruit/Adafruit-GFX-Library
#include <Adafruit_SSD1306.h>       //https://github.com/adafruit/Adafruit_SSD1306
#include <SPI.h>
#include <Wire.h>
 
#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels
 
// Declaration for an SSD1306 display connected to I2C (SDA, SCL pins)
#define OLED_RESET     -1 // Reset pin # (or -1 if sharing Arduino reset pin)
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);
 
// Icon of Fingerprint
#define LOGO_HEIGHT   64
#define LOGO_WIDTH    128
static const unsigned char PROGMEM logo_bmp[] =
{
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x03, 0xff, 0xc0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x3f, 0xff, 0xfc, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xff, 0xff, 0xff, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x03, 0xff, 0x83, 0xff, 0xc0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x0f, 0xf0, 0x00, 0x0f, 0xf0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x1f, 0x80, 0x00, 0x03, 0xf8, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x7e, 0x03, 0xff, 0xc0, 0xfe, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0xfc, 0x3f, 0xff, 0xf8, 0x3f, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x01, 0xf0, 0xff, 0xff, 0xfe, 0x0f, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x01, 0xe1, 0xff, 0x00, 0xff, 0x87, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x01, 0xc7, 0xf0, 0x00, 0x1f, 0xe0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x01, 0x8f, 0xc0, 0x00, 0x03, 0xf0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x1f, 0x03, 0xff, 0xc1, 0xf8, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x3e, 0x0f, 0xff, 0xf0, 0x7c, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x7c, 0x3f, 0xff, 0xfc, 0x3e, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0xf8, 0xff, 0x00, 0xff, 0x1f, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0xf1, 0xf8, 0x00, 0x1f, 0x8f, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x01, 0xe3, 0xf0, 0x18, 0x0f, 0xc7, 0xc0, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x03, 0xc7, 0xc1, 0xff, 0x83, 0xe3, 0xc0, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x03, 0xc7, 0x87, 0xff, 0xe1, 0xf1, 0xc0, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x07, 0x8f, 0x1f, 0xff, 0xf0, 0xf0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x07, 0x1e, 0x3f, 0x01, 0xf8, 0x78, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x07, 0x1e, 0x7e, 0x00, 0x7c, 0x79, 0xc0, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x3c, 0x78, 0x00, 0x3e, 0x3d, 0xc0, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x78, 0xf0, 0xff, 0x1f, 0x3d, 0xe0, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x79, 0xe1, 0xff, 0x8f, 0x1c, 0xe0, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0xf1, 0xe3, 0xff, 0xc7, 0x1e, 0xe0, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x01, 0xe3, 0xc7, 0xc3, 0xc7, 0x9e, 0xf0, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x07, 0xe3, 0x8f, 0x01, 0xe7, 0x9e, 0xf0, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x0f, 0xc7, 0x8f, 0x00, 0xe3, 0x9e, 0xf0, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x0f, 0x8f, 0x9e, 0x18, 0xf3, 0x9e, 0x70, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x0e, 0x0f, 0x1e, 0x38, 0xf3, 0x9e, 0x70, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x1e, 0x3c, 0x38, 0xf3, 0x9e, 0x70, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x3c, 0x3c, 0x78, 0xf7, 0x9c, 0x70, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x7c, 0x78, 0x78, 0xe7, 0x9c, 0x70, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x01, 0xf0, 0xf0, 0xf1, 0xe7, 0x9c, 0x70, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x03, 0xe1, 0xf1, 0xe1, 0xe7, 0x3c, 0xf0, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x0f, 0xc3, 0xe3, 0xe3, 0xc7, 0x3c, 0xf0, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x0f, 0x87, 0xc3, 0xc3, 0xcf, 0x3c, 0xf0, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x0f, 0x0f, 0x87, 0x87, 0x8f, 0x3c, 0xe0, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x1f, 0x0f, 0x0f, 0x8f, 0x38, 0xe0, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x7e, 0x1f, 0x1f, 0x0f, 0x3c, 0xe0, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0xfc, 0x3e, 0x1e, 0x0f, 0x3d, 0xe0, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x01, 0xf0, 0x7c, 0x3c, 0xcf, 0x3c, 0xe0, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x07, 0xe0, 0xf8, 0x79, 0xcf, 0x1e, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x0f, 0xc1, 0xf0, 0xf9, 0xcf, 0x1e, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x0f, 0x07, 0xe1, 0xf1, 0xc7, 0x0f, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x0e, 0x0f, 0xc3, 0xe3, 0xc7, 0x87, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x1f, 0x07, 0xc3, 0xc7, 0x87, 0xc0, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x3e, 0x1f, 0x83, 0xc3, 0xc3, 0xc0, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0xfc, 0x3e, 0x01, 0xc3, 0xe0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x01, 0xf8, 0x7c, 0x01, 0xc1, 0xf8, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x01, 0xf0, 0xf8, 0x01, 0xe0, 0xfc, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x01, 0xc3, 0xf3, 0xf8, 0xf0, 0x7e, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x07, 0xe7, 0xfc, 0xf8, 0x1c, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x0f, 0xcf, 0xfe, 0x7c, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x0f, 0x1f, 0x1e, 0x3e, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x0e, 0x3e, 0x0f, 0x1e, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x3c, 0x0f, 0x0e, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x18, 0x07, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x07, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
};
 
Adafruit_Fingerprint finger = Adafruit_Fingerprint(&Serial2);
 
int relayPin = 23;
int buzzerPin = 15;
 
void setup()
{
 pinMode(relayPin, OUTPUT);
 pinMode(buzzerPin, OUTPUT);
 
 digitalWrite(relayPin, LOW);
 digitalWrite(buzzerPin, LOW);
 
 Serial.begin(57600);
 Serial2.begin(115200);
 
if(!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) 
{ 
    Serial.println(F("SSD1306 allocation failed"));
    for(;;); // Don't proceed, loop forever
  }
 
 while (!Serial); 
 delay(100);
 
 display.clearDisplay();
 display.drawBitmap(0, 0, logo_bmp, LOGO_WIDTH, LOGO_HEIGHT, 1);
 display.display();
 
 Serial.println("Fingerprint Door Lock");
 delay(3000);
 display.clearDisplay();
 
 // set the data rate for the sensor serial port
 finger.begin(57600);
 
 if (finger.verifyPassword()) 
 {
   Serial.println("Fingerprint Sensor Connected");
   display.clearDisplay();
   display.setTextSize(2);             // Normal 1:1 pixel scale
   display.setTextColor(SSD1306_WHITE);        // Draw white text
   display.setCursor(25, 0);            // Start at top-left corner
   display.println(("Sensor"));
   display.setCursor(5, 35);
   display.println("Connected");
   display.display();
   delay(3000); 
  // display.clearDisplay();
 }
 
 else  
 {
   display.clearDisplay();
   display.setTextSize(2);             // Normal 1:1 pixel scale
   display.setTextColor(SSD1306_WHITE);        // Draw white text
   display.setCursor(25, 0);            // Start at top-left corner
   display.println(("Sensor"));
   display.setCursor(5, 35);
   display.println("Not Found");
   display.display();
   
   Serial.println("Unable to find Sensor");
   delay(3000);
   Serial.println("Check Connections");
 
   while (1) {
     delay(1);
   }
 }
display.clearDisplay();
}
 
void loop()                     // run over and over again
{
 getFingerprintIDez();
 delay(50);            //don't need to run this at full speed.
}
 
// returns -1 if failed, otherwise returns ID #
int getFingerprintIDez() 
{
 uint8_t p = finger.getImage();
 if (p != FINGERPRINT_OK)  
 {
 
   display.clearDisplay();
   display.drawBitmap(0, 0, logo_bmp, LOGO_WIDTH, LOGO_HEIGHT, 1);
   display.display();
   Serial.println("Waiting For Valid Finger");
   return -1;
 }
 
 p = finger.image2Tz();
 if (p != FINGERPRINT_OK)  
 {
   display.clearDisplay();
   display.setTextSize(2);             // Normal 1:1 pixel scale
   display.setTextColor(SSD1306_WHITE);        // Draw white text
   display.setCursor(0, 0);            // Start at top-left corner
   display.println(("Messy  Image"));
   display.setCursor(0, 35);
   display.println("Try Again");
   display.display();
   
   Serial.println("Messy Image Try Again");
   delay(3000);
   display.clearDisplay();
   return -1;
 }
 
 p = finger.fingerFastSearch();
 if (p != FINGERPRINT_OK)  {
   
   display.clearDisplay();
   display.setTextSize(2);             // Normal 1:1 pixel scale
   display.setTextColor(SSD1306_WHITE);        // Draw white text
   display.setCursor(20, 0);            // Start at top-left corner
   display.println(("Invalid"));
   display.setCursor(25, 20);
   display.println("Finger");
   display.setCursor(10, 40);
   display.println("Try Again");
   display.display();
   Serial.println("Not Valid Finger");
   delay(3000);
   display.clearDisplay();
   return -1;
 }
 
 // found a match!
   display.clearDisplay();
   display.setTextSize(2);             // Normal 1:1 pixel scale
   display.setTextColor(SSD1306_WHITE);        // Draw white text
   display.setCursor(40, 0);            // Start at top-left corner
   display.println(("Door"));
   display.setCursor(15, 20);            // Start at top-left corner
   display.println(("Unlocked"));
   display.setCursor(20, 40);
   display.println("Welcome");
   display.display();
   
   digitalWrite(relayPin, HIGH);
   digitalWrite(buzzerPin, HIGH);
   delay(3000);
   
   display.clearDisplay();
   display.setTextSize(2);             // Normal 1:1 pixel scale
   display.setTextColor(SSD1306_WHITE);        // Draw white text
   display.setCursor(20, 10);            // Start at top-left corner
   display.println(("Closing"));
   display.setCursor(20, 30);            // Start at top-left corner
   display.println(("the Door"));
   display.display();
   
   digitalWrite(relayPin, LOW);
   digitalWrite(buzzerPin, LOW);
   delay(3000);
   
   display.clearDisplay();
   
   Serial.println("Door Unlocked Welcome");
   
   return finger.fingerID;
}
