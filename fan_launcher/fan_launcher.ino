// include the TinkerKit library
#include <TinkerKit.h>
#include <Time.h>
#include <LiquidCrystal.h>
#include <Wire.h>
#include <matrix_lcd_commands.h>
#include <TKLCD.h>
 
// creating the object 'relay' that belongs to the 'TKRlay' class 
TKMosFet relay(A1);                      
TKLCD_Local lcd = TKLCD_Local();
TKButton button(A0);
unsigned long lastPress = 0;
const unsigned long timeOut = 6000;
int printed = 0;
int currentCount = 1;

void setup() {
  lcd.begin();
  relay.off();
}
 
void loop() 
{
  unsigned long millisLastPress = millis() - lastPress;
  
  if (lastPress > 0 && (millisLastPress < timeOut)) {
    // turn on display
    if (millisLastPress > (currentCount * 1000) && millisLastPress < ((currentCount+1)*1000)) {
      if (printed == 0) {
        printed++;
        lcd.clear();
        lcd.setCursor(0,0);
        if (currentCount == 5) {
          lcd.print("Launch!");
          relay.off();
        }
        else
          lcd.print(5 - currentCount);
      }
    }
    else {
      if (millisLastPress > (currentCount * 1000)) {
        currentCount++;
        printed = 0;
      }
    }
  }
  else {
    lastPress = 0;
    lcd.clear();
  }

  if (button.pressed() == HIGH) {
    if (lastPress == 0) {
      // send the passcode to server
      lastPress = millis();
      lcd.clear();
      lcd.setCursor(0,0);
      lcd.print("Begin Engine");
      printed = 0;
      currentCount = 1;
      relay.on();
    }
  }
}
