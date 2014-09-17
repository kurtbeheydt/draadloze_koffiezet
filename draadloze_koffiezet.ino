// draadloze koffiezet
#include <YunClient.h>
#include <YunServer.h>

int ledGroen = 3;
int pinAanRelay = 4;
int pinKoffieRelay = 5;

YunServer server;

void setup() {
  // mode juist zetten voor de statusled en relays
  pinMode(ledGroen, OUTPUT);
  pinMode(pinAanRelay, OUTPUT);
  pinMode(pinKoffieRelay, OUTPUT);
  
  // Laden van Yun bridge library.
  Bridge.begin();
  
  // Zorgen dat er geluisterd wordt naar wat er via wifi/ethernet binnenkomt
  // De arduino chip communiceert met het Linio OS via een seriale verbinding
  server.listenOnLocalhost();
  server.begin();
  
  // status: communicatie = ok
  digitalWrite(ledGroen, HIGH);
} 
 
void loop() {
  // luisteren of er iets binnenkomt via wifi/ethernet
  YunClient client = server.accept();
  
  // iemand verbonden?
  if (client) {
    // beetje tijd geven anders kan de smartphone niet volgen...
    client.setTimeout(5);
    
    // uitlezen van nakijken wat commando juist inhoudt
    String command = client.readStringUntil('/');
    command.trim();
    
    // als het commando 'koffie' binnenkomt, de bezochte webpagina is dus http://koffiezet.local/arduino/koffie
    if (command == "zetaan") { // om machine aan te zetten, de bezochte webpagina is dus http://koffiezet.local/arduino/zetaan
      digitalWrite(pinAanRelay, HIGH);
      delay(500); // aan-knop van senseo heeft wat indruktijd nodig
    } else if (command == "koffie") {
      digitalWrite(pinKoffieRelay, HIGH);
    }  

    // antwoord met de standaardpagina met de knop om koffie te maken, voor eender welke bezochte pagina onder http://koffiezet.local/arduino/
    client.println("Status: 200");
    client.println("Content-type: text/html;");
    client.println();
    client.print("<!DOCTYPE HTML><html lang=\"nl\" dir=\"ltr\"><head><title>zet koffie!</title></head>");
    client.print("<body style=\"text-align: center; padding-top: 200px; font-family: Helvetica; font-size: 120px; background-color: #dddddd;\">");
    client.print("<a href=\"/arduino/zetaan\" style=\"display: block; padding: 50px 20px; background-color: #111111; color: #ffffff; width: 80%; margin: 20px auto;");
    client.print(" text-decoration: none; -webkit-border-radius: 4px; -moz-border-radius: 4px; border-radius: 4px;\">zet aan!</a>");
    client.print("<a href=\"/arduino/koffie\" style=\"display: block; padding: 50px 20px; background-color: #333333; color: #ffffff; width: 80%; margin: 20px auto;");
    client.print(" text-decoration: none; -webkit-border-radius: 4px; -moz-border-radius: 4px; border-radius: 4px;\">zet koffie!</a>");
    client.println("</body></html>");
    client.stop();
  } else {
     digitalWrite(pinKoffieRelay, LOW);
     digitalWrite(pinAanRelay, LOW);
  }
}
