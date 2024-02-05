/*
Version: 1.1.0
Licence:
Copyright (c) 2024 Marc Czapp, Hamidreza Tabrizi 

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
*/
#include <LiquidCrystal_I2C.h>           // LCD Library einbinden
#include "DHT.h"                         // Bibliothek importieren
#define DHTPIN  12                       // Pin wählen
#define DHTTYPE DHT22                    // DHT auswählen (WokWi = DHT22 / Hardware = DHT11)
DHT dht(DHTPIN, DHTTYPE);                // Objekt mit Parameter anlegen
LiquidCrystal_I2C lcd(0x27,16,2);        // LCD Display einstellen


unsigned long privousMilli;             // Variablen vereinbaren
const float minTemp = 20.00;            // Variablen vereinbaren
float humidity, temperature;            // Variablen vereinbaren

void setup() 
{
  Serial.begin(9600);                    // serieller Monitor starten                 
  dht.begin();                           // DHT22-Sensor starten
  lcd.begin(16, 2);                       //LCD Display starten
  pinMode(4,OUTPUT);
  pinMode(5,OUTPUT);
  pinMode(6,OUTPUT);
  pinMode(7,OUTPUT);
  pinMode(A0, INPUT);
}

/**
Written by: MCzapp 05.02.2024
Release: 2.0.0
Version: 1.0.0

loop function that implements the functions.

Output:
  void
**/

void loop() 
{
  
  if(millis() - privousMilli > 500) {
    humidity = dht.readHumidity();         // Wert Luftfeuchtigkeit 
    temperature = dht.readTemperature();   // Wert Temperatur
    setLED(temperature, checkPotentium());
  }
  
  if(millis() - privousMilli > 5000) {
    privousMilli = millis();
    resetLED();
  }
  
  setDisplay(humidity, temperature);        //Refreshing the Display
  
  // Ausgabe im seriellen Monitor
  Serial.println("Humidity:    " + String(humidity) + "%");
  Serial.println("Temperature: " + String(temperature) + "°C");

  delay(2000);                           // 2 Sekunden bis zur nächsten Messung warten
}

/**
Written by: HTab 16.01.2024
Release: 1.1.0
Version: 1.0.0

Refreshs the LCD DIsplay
Printing out the measured Data into the Display

Input:
  float humid = Current Humidity
  float temp = Current Temperature

Output:
  void
**/
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

//TODO Change function to use the map function to remap Values to the Potentiometer
int checkPotentium() {
  int maxTemp = analogRead(A0);
  maxTemp /= 10;
  Serial.println("Max Temp:" + String(maxTemp));
  return maxTemp;

}

/**
Written by MCzapp 05.12.2023
Release: 1.0.0
Version: 2.0.0

Input:
  float tempTemperature = Current Temperature
  int tempMaxTemp = Max Temperatur setted by Potentiumeter

Output:
  void

**/
void setLED (float tempTemperature, int tempMaxTemp) 
{

  if (tempTemperature <= minTemp) {
    digitalWrite(6, HIGH);
  } else if (tempTemperature >= tempMaxTemp) {
    digitalWrite(4, HIGH);
  } else {
    digitalWrite(5, HIGH);
  }
}

/**
Written by: HTab 16.01.2024
Release: 1.0.0
Version: 1.0.0

Resets all LED Pins to LOW

Input:

Output:
  void
**/
void resetLED() 
{
  digitalWrite(4, LOW);
  digitalWrite(5, LOW);
  digitalWrite(6, LOW);
}

