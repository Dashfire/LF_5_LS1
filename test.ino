#include "DHT.h"                         // Bibliothek importieren
#define DHTPIN  12                       // Pin wählen
#define DHTTYPE DHT22                    // DHT auswählen (WokWi = DHT22 / Hardware = DHT11)
DHT dht(DHTPIN, DHTTYPE);                // Objekt mit Parameter anlegen

#include <LiquidCrystal_I2C.h>           //LCD Library einbinden
LiquidCrystal_I2C lcd(0x27,16,2);        //LCD Display einstellen

float humidity, temperature;            // Variablen vereinbaren

void setup() 
{
  Serial.begin(9600);                    // serieller Monitor starten                 
  dht.begin();                           // DHT22-Sensor starten
  lcd.begin(16, 2);                       //LCD Display starten
  pinMode(4,OUTPUT);
  pinMode(5,OUTPUT);
  pinMode(6,OUTPUT);
  pinMode(A0, INPUT);
}

void loop() 
{
  
  humidity = dht.readHumidity();         // Wert Luftfeuchtigkeit 
  temperature = dht.readTemperature();   // Wert Temperatur

  setLED(temperature,checkPotentium());
  setDisplay();                          //Refreshing the Display
  
  // Ausgabe im seriellen Monitor
  Serial.println("Humidity:    " + String(humidity) + "%");
  Serial.println("Temperature: " + String(temperature) + "°C");

  delay(2000);                           // 2 Sekunden bis zur nächsten Messung warten
}

void setLED (float tempTemperature, int tempMaxTemp) {
  resetLED();
  // Temperature reading that is used to turn on different LEDs
    if(tempTemperature <= 20.00) {
    digitalWrite(6, HIGH);
  }else if(tempTemperature >= tempMaxTemp) {
    dangerBlinken(tempTemperature, tempMaxTemp);
  } else {
    digitalWrite(5, HIGH);
  }
}


/**
Written by: HTab 16.01.2024
Release: 1.1.0
Version: 1.0.0

Refreshs the LCD DIsplay
Printing out the measured Data into the Display

Input:

Output:
  void
**/
void setDisplay() {

  lcd.clear();              //LCD Display clearen

  lcd.setCursor(0,0);
  lcd.print("Humidity:");    

  //Kontrollmechanismus für das richtige Platzieren des Cursors
  if(humidity >= 100) {
    lcd.setCursor(9,0);
  } else {
    lcd.setCursor(10,0);
  }

  lcd.print(String(humidity) + "%");

  lcd.setCursor(0,1);
  lcd.print("Temp:");

  //Kontrollmechanismus für das richtige Platzieren des Cursors
  if(temperature <= -10) {
    lcd.setCursor(9,1);
  } else if(temperature >= 0 && temperature < 10) {
    lcd.setCursor(11,1);
  } else {
    lcd.setCursor(10,1);
  }

  lcd.print(String(temperature) + "C");
  
}

//TODO Change function to use the map function to remap Values to the Potentiometer
int checkPotentium() {
  int maxTemp = analogRead(A0);
  maxTemp /= 10;
  Serial.println("Max Temp:" + String(maxTemp));
  return maxTemp;

}

void blink (int pin, int rate) {
    digitalWrite(pin, HIGH);
    delay(rate);
    digitalWrite(pin, LOW);
    delay(rate);

}

void resetLED() {
  digitalWrite(4, LOW);
  digitalWrite(5, LOW);
  digitalWrite(6, LOW);
}

void dangerBlinken(float tempTemperature,int tempMaxTemp) {
  float difference = getDifference(tempTemperature, tempMaxTemp);
  blinken(4,100*difference);
}

float getDifference(float tempTemperature,int tempMaxTemp) {
  return tempMaxTemp/tempTemperature*100;
}

