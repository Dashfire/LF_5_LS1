# LF_5_LS1
Dieses Projekt ist im Rahmen des ersten Ausbildungsjahres als Fachinformatiker für Anwendungsentwicklung entstanden.

Dieses Projekt ist von:
- [Hamidreza Tabrizi]()
- [Marc Czapp]()

## Beschreibung

Das Projekt teilt sich in 2 Bereiche auf, zum einen die main.ino und der Display Bibliothek im Ordner lib.

Die Datei main.ino behinhaltet jegliche Funktionalität um auf einen Arduino Uno, die Daten die mit einem DHT 11/22 zu verarbeiten und
mit einem LCD1602 darzustellen.

## Nutzung
Für die Nutzung des Programms, einfach den Code der main.ino auf deinen Arduino Uno kopieren. Sobald der Arduino angeschlossen ist,
misst er die Temperatur und Luftfeuchtigkeit. Die Grenzen der Temperaturmessung liegen bei 20°C als feste untere Grenze.
Die Obere Grenze kann von 25°C bis 255°C mit dem Drehregler eingestellt werden. Eine Benachrichtigung über den Akutellen 
Messwert, kann im Serielen Monitor, den LEDS oder dem mit angeschlossenen LCD1602 eingesehen werden. 

Die LEDS haben folgende Bedeutung:
Blaue LED - Die Temperatur liegt unter normalen Bereich.
Grüne LED - Die Temperatur liegt im normalen Bereich.
Rote LED - Die Temperatur liegt ueber dem normalen Bereich.

## Struktogramm Haupt-Funktion

![Main Struktogramm](https://github.com/Dashfire/LF_5_LS1/assets/1838613/05b64460-7535-4b26-92fe-e631e98d67bb)

## Struktogramm Display-Funktion

![setDisplay Struktogramm](https://github.com/Dashfire/LF_5_LS1/assets/1838613/3e185313-61a1-43dd-855b-c79fb16a4fa0)
