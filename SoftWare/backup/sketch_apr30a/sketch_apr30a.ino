#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>


// WiFi network
const char* ssid     = "VIETTEL_CHUYEN";
const char* password = "0903482723";

ESP8266WebServer server ( 80 );



char htmlResponse[3000];

void handleRoot() {

  snprintf ( htmlResponse, 3000,
"<!DOCTYPE html>\
<html lang=\"en\">\
  <head>\
    <meta charset=\"utf-8\">\
    <meta name=\"viewport\" content=\"width=device-width, initial-scale=1\">\
  </head>\
  <body>\
          <h1>Time</h1>\
          <input type='text' name='Speed' id='speed' size=2 autofocus> Speed \
          <input type='text' name='KP' id='date_mm' size=2 autofocus> mm \
          <input type='text' name='KD' id='date_ss' size=2 autofocus> ss \
          <input type='text' name='KI' id='date_ss' size=2 autofocus> ss \
          <div>\
          <br><button id=\"save_button\">Save</button>\
          </div>\
    <script src=\"https://ajax.googleapis.com/ajax/libs/jquery/1.11.3/jquery.min.js\"></script>\    
    <script>\
      var Speed;\
      var mm;\
      var ss;\
      $('#save_button').click(function(e){\
        e.preventDefault();\
        Speed = $('#speed').val();\
        mm = $('#date_mm').val();\
        ss = $('#date_ss').val();\        
        $.get('/save?hh=' + hh + '&mm=' + mm + '&ss=' + ss, function(data){\
          console.log(data);\
        });\
      });\      
    </script>\
  </body>\
</html>"); 

   server.send ( 200, "text/html", htmlResponse );  

}


void handleSave() {
  if (server.arg("Speed")!= ""){
    Serial.println("Speed: " + server.arg("Speed"));
  }

  if (server.arg("mm")!= ""){
    Serial.println("Minutes: " + server.arg("mm"));
  }

  if (server.arg("ss")!= ""){
    Serial.println("Seconds: " + server.arg("ss"));
  }

}


void setup() {

  // Start serial
  Serial.begin(115200);
  delay(10);

  // Connecting to a WiFi network
  Serial.println();
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);

  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("");
  Serial.println("WiFi connected");  
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());

  server.on ( "/", handleRoot );
  server.on ("/save", handleSave);

  server.begin();
  Serial.println ( "HTTP server started" );


}

void loop() {
  server.handleClient();
}
