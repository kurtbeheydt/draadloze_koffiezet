// draadloze koffiezet

#include <Servo.h>
#include <YunClient.h>
#include <YunServer.h>

int ledGroen = 3;
int servoPin = 9;
Servo servoKnop;
YunServer server;

void setup() {
  // mode juist zetten voor de statusleds
  pinMode(ledGroen, OUTPUT);
  
  // Laden van Yun bridge library.
  Bridge.begin();
  
  // Zorgen dat er geluisterd wordt naar wat er via wifi/ethernet binnenkomt
  // De arduino chip communiceert met het Linio OS via een seriale verbinding
  server.listenOnLocalhost();
  server.begin();
  
  // status: communicatie = ok
  digitalWrite(ledGroen, HIGH);
  
  // servo koppelen en naar beginstand zetten
  servoKnop.attach(servoPin);
  servoKnop.write(0); 
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
    if (command == "koffie") {
      servoKnop.write(180); 
    } else if (command == "reset") { // reset mogelijkheid om servo terug naar begin positie te zetten, de bezochte webpagina is dus http://koffiezet.local/arduino/reset
      servoKnop.write(0); 
    }

    // antwoord met de standaardpagina met de knop om koffie te maken, voor eender welke bezochte pagina onder http://koffiezet.local/arduino/
    client.println("Status: 200");
    client.println("Content-type: text/html;");
    client.println();
    client.print("<!DOCTYPE HTML><html lang=\"nl\" dir=\"ltr\"><head><title>zet koffie!</title></head>");
    client.print("<body style=\"text-align: center; padding-top: 200px; font-family: Helvetica; font-size: 120px; background-color: #dddddd;\">");
    client.print("<a href=\"/arduino/koffie\" style=\"display: block; padding: 50px 20px; background-color: #333333; color: #ffffff; width: 80%; margin: auto;");
    client.print(" text-decoration: none; -webkit-border-radius: 4px; -moz-border-radius: 4px; border-radius: 4px;\">zet koffie!</a>");
    client.println("</body></html>");
    client.stop();
  }
}
