#include <Arduino.h>
#include <Wire.h>
#include <Adafruit_RGBLCDShield.h>
#include <utility/Adafruit_MCP23017.h>


// The shield uses the I2C SCL and SDA pins. On classic Arduinos
// this is Analog 4 and 5 so you can't use those for analogRead() anymore
// However, you can connect other I2C sensors to the I2C bus and share
// the I2C bus.
Adafruit_RGBLCDShield lcd = Adafruit_RGBLCDShield();

// These #defines make it easy to set the backlight color
#define RED 0x1
#define YELLOW 0x3
#define GREEN 0x2
#define TEAL 0x6
#define BLUE 0x4
#define VIOLET 0x5
#define WHITE 0x7

struct state{
  unsigned char throttle;
  unsigned char sense12V;
  unsigned char sense48V;
  unsigned char motThrottle;
  unsigned char pwrThrottle;
  union{
    unsigned char bitarray;
    struct bit {
      unsigned char RESERVE:1;
      unsigned char PwrEN:1;
      unsigned char PwrDIR:1;
      unsigned char KeyL:1;
      unsigned char KeyUP:1;
      unsigned char KeyDN:1;
      unsigned char KeyR:1;
      unsigned char KeySE:1;
    };
  }DIO;
};

void setup() {
  // Debugging output
  Serial.begin(9600);
  // set up the LCD's number of columns and rows: 
  lcd.begin(16, 2);

  // Print a message to the LCD. We track how long it takes since
  // this library has been optimized a bit and we're proud of it :)
  int time = millis();
  lcd.print("Hello, world!");
  time = millis() - time;
  Serial.print("Took "); Serial.print(time); Serial.println(" ms");
  lcd.setBacklight(WHITE);
}

void loop() {
  // set the cursor to column 0, line 1
  // (note: line 1 is the second row, since counting begins with 0):
  lcd.setCursor(0, 1);
  // print the number of seconds since reset:
  lcd.print(millis()/1000);

  uint8_t buttons = lcd.readButtons();

  if (buttons) {
    lcd.clear();
    lcd.setCursor(0,0);
    if (buttons & BUTTON_UP) {
      lcd.print("UP ");
      lcd.setBacklight(RED);
    }
    if (buttons & BUTTON_DOWN) {
      lcd.print("DOWN ");
      lcd.setBacklight(YELLOW);
    }
    if (buttons & BUTTON_LEFT) {
      lcd.print("LEFT ");
      lcd.setBacklight(GREEN);
    }
    if (buttons & BUTTON_RIGHT) {
      lcd.print("RIGHT ");
      lcd.setBacklight(TEAL);
    }
    if (buttons & BUTTON_SELECT) {
      lcd.print("SELECT ");
      lcd.setBacklight(VIOLET);
    }
  }
}

// switch(Throttle){
//     case DRIVE:
//         switch(PowerSource){
//             case BATTERY:

//             break;
//             case EDLC:

//             break;
//             default:
//             break;
//         }
//     break;
//     case FREE:

//     break;
//     case REGEN:

//     break;
//     default:
//     break;
// }

// Allow StateTransition
// Free->Drive
// Free->Boost
// Free->Regen
// * -> Free
// DIS-Allow StateTransition
// Drive -> Boost
// Drive -> Regen
// Boost -> Drive
// Boost -> Regen
// Regen -> Drive
// Regen -> Boost


void drive(uint16_t throttleValue){

}

void boost(uint16_t throttleValue){

}
void freeRun(uint16_t throttleValue){

}

void regen(uint16_t throttleValue){

}

void (* const stateFunc[])(uint16_t) = {
  drive, boost, freeRun, regen,
};

enum operationMode{
  Drive, Boost, FreeRun, Regen,
};