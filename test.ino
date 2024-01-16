#include "DHT.h"                         // Bibliothek importieren
#define DHTPIN  12                       // Pin wählen
#define DHTTYPE DHT22                    // DHT auswählen (WokWi = DHT22 / Hardware = DHT11)
DHT dht(DHTPIN, DHTTYPE);                // Objekt mit Parameter anlegen

float humidity, temperature;            // Variablen vereinbaren

void setup() 
{
  Serial.begin(9600);                    // serieller Monitor starten                 
  dht.begin();                           // DHT22-Sensor starten
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
//TODO 
int checkPotentium() {
  int maxTemp = analogRead(A0);
  maxTemp /= 10;
  Serial.println("Max Temp:" + String(maxTemp));
  return maxTemp;

}

void blinken (int pin, int rate) {
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

