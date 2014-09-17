Draadloze koffiezet
===================

Voor wie via zijn smartphone of computer de koffiezet wil starten.

Er komt geen uitleg over wat Arduino en dergelijke is, je hebt best al een paar eenvoudige projectjes met de Arduino Uno achter de rug.
Alles wat nieuw is voor de Yun, wordt uitgelegd.

# Onderdelen
- Arduino Yun
- arduino 1.5 nodig (met Yun libraries)
- twee 5v relays. Handig om er te gebruiken die al van een breakout-board voorzien zijn, bv deze http://www.dx.com/p/arduino-5v-relay-module-blue-black-121354
- weerstand 220Ohm
- groen ledje
- kabeltjes
- breadboard

# Hacken van koffiezet
- Google op het model van je koffiezet + 'exploded design' of 'exploded view' Meestal vind je op die manier technische documentatie met waar de vijzen, clipjes zitten om je toestel open te breken. Voor de senseo staat de documentatie op: http://www.onderdelensenseo.nl/gebruiksaanwijzingen/philips-service-manual/963/hd-pdf.html
- Zoek op het pcb naar waar de schakelaar(s) het circuit kortsluit(en) om dit via kabeltjes te verlengen (zie foto's) deze kabeltjes gaan dan in de relay die je aansluit op de Arduino.
![hacking van koffiezet](https://raw.githubusercontent.com/nerdlandbe/draadloze_koffiezet/master/footage/01-koffiezet-open.jpg)
![hacking van koffiezet](https://raw.githubusercontent.com/nerdlandbe/draadloze_koffiezet/master/footage/02-koffiezet-pcb.jpg)
![hacking van koffiezet](https://raw.githubusercontent.com/nerdlandbe/draadloze_koffiezet/master/footage/03-koffiezet-pcb-gehacked.jpg)
![hacking van koffiezet](https://raw.githubusercontent.com/nerdlandbe/draadloze_koffiezet/master/footage/04-koffiezet-draadjes.jpg)

# Connecties met arduino
- Zie onderstaand schema (de relays verbinden met de draadjes van de gehackte koffiezet)
![schema](https://raw.githubusercontent.com/nerdlandbe/draadloze_koffiezet/master/howto/schema.png)
- foto's van de schakeling:
![schakeling](https://raw.githubusercontent.com/nerdlandbe/draadloze_koffiezet/master/footage/schakeling-breadboard.jpg)
![schakeling](https://raw.githubusercontent.com/nerdlandbe/draadloze_koffiezet/master/footage/schakeling-arduino-breadboard.jpg)
![complete opstelling](https://raw.githubusercontent.com/nerdlandbe/draadloze_koffiezet/master/footage/opstelling-compleet.jpg)

# Wifi instellen op de arduino Yun
- Als de Arduino Yun nog niet geconfigureerd is, maakt hij zelf een wifi-netwerk met de naam 'Arduino Yun-XXXXXXXXXXXX'. Connecteer met dit wifi-netwerk.
- Open de webpagina http://arduino.local. Je krijgt nu een pagina in arduino stijl met een formulier om in te loggen.
![stap 1](https://raw.githubusercontent.com/nerdlandbe/draadloze_koffiezet/master/howto/stap01.png)
- Het standaard wachtwoord is 'arduino'.
- geef je Arduino een naam (bv koffiezet) en stel een admin wachtwoord in
![stap 2](https://raw.githubusercontent.com/nerdlandbe/draadloze_koffiezet/master/howto/stap02.png)
- Kies het wifi netwerk waarmee je wil verbinden, vul het wifi-wachtwoord in
![stap 3](https://raw.githubusercontent.com/nerdlandbe/draadloze_koffiezet/master/howto/stap03.png)
- Onder de knop 'configure & restart' staat nog een optie die belangrijk is voor dit project: Rest api access, zet deze op 'open'. Info over de Web services op de Arduino Yun: http://arduino.cc/en/Guide/ArduinoYun#toc5
![stap 4](https://raw.githubusercontent.com/nerdlandbe/draadloze_koffiezet/master/howto/stap04.png)
- Kies nu 'Configure & restart'. De Arduino herstart en connecteert terug met je eigen wifi.

# Code opladen
- Je hebt de Arduino IDE 1.5 nodig (momenteel misschien nog in beta, maar is geen probleem). Kies het juiste board uit de lijst via 'tools' > 'board'
- Yun moet stroom hebben via usb kabel, hoeft niet via kabel met je computer verbonden te zijn (wel op hetzelfde wifi netwerk). Kies de juiste poort via 'tools' > 'port'
- laad de code op: https://raw.githubusercontent.com/nerdlandbe/draadloze_koffiezet/master/draadloze_koffiezet.ino

# Bedienen
- Surf vanop je smartphone/computer naar: http://koffiezet.local/arduino/start
- klik op de knop 'zet aan' om de koffiezet aan te zetten.
- Klik op de knop 'koffie!' om koffie te zetten.

# Verder?
- Misschien lukt het ook met transistors ipv relays
- Het wordt nog interessanter als je een mini sd-kaartje in de arduino Yun steekt. op die manier kan je php, python, of andere scripting talen gebruiken als je stevigere code nodig hebt voor je projecten. Meer info: http://playground.arduino.cc/Hardware/Yun
- Nu nog automatisch tas koffie laten brengen, nieuwe tas klaarzetten, ...

# referenties
- http://www.homautomation.org/2013/10/01/playing-with-arduino-yun/
- http://arduino.cc/en/Main/ArduinoBoardYun
- http://arduino.cc/en/Guide/ArduinoYun
- http://makezine.com/projects/smart-remote-control/
- http://www.onderdelensenseo.nl/gebruiksaanwijzingen/philips-service-manual/963/hd-pdf.html