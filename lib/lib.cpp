#include "Arduino.h"
#include "lib.h

void setDisplay(float humid, float temp) {

  lcd.clear();                //LCD Display clearen         

  lcd.setCursor(0,0);
  lcd.print("Humidity:");    

  //Kontrollmechanismus für das richtige Platzieren des Cursors
  if(humid >= 100) {
    lcd.setCursor(9,0);
  } else {
    lcd.setCursor(10,0);
  }

  lcd.print(String(humid) + "%");

  lcd.setCursor(0,1);
  lcd.print("Temp:");

  //Kontrollmechanismus für das richtige Platzieren des Cursors
  if(temp <= -10) {
    lcd.setCursor(9,1);
  } else if(temp >= 0 && temp < 10) {
    lcd.setCursor(11,1);
  } else {
    lcd.setCursor(10,1);
  }

  lcd.print(String(temp) + "C");
  
}
