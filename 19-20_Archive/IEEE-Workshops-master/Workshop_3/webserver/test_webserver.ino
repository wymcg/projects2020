// Load Wi-Fi library
#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>

// Replace with your network credentials
const char* ssid     = "Test_Webserver";
const char* password = "thereisnospoon";

// Set web server port number to 80
ESP8266WebServer server(80);

// Auxiliar variables to store the current output state
String output5State = "off";
String output4State = "off";

// Assign output variables to GPIO pins
const int output5 = 5;
const int output4 = 4;

void setup() {
  Serial.begin(115200);
  
  // Initialize the output variables as outputs
  pinMode(output5, OUTPUT);
  pinMode(output4, OUTPUT);
  
  // Set outputs to LOW
  digitalWrite(output5, LOW);
  digitalWrite(output4, LOW);
  
  // Start the server
  Serial.println("Starting HTTP server");
  WiFi.softAP(ssid, password);

  // Log server IP address
  IPAddress myIP = WiFi.softAPIP();
  Serial.print("AP IP address: ");
  Serial.println(myIP);

  // Set server root
  server.on ("/", handleRoot);
  server.on ("/root", handleRoot);
  server.begin();
  Serial.println("HTTP server started");
}

void handleRoot() {
  Serial.println("Client connected to host root"); 
  int sec = millis() / 1000;
  int min = sec / 60;
  int hr = min / 60;
  
  // parse the arguments to turn the GPIOs on and off
  if (server.arg("pin") == "5" && server.arg("state") == "on") {
    Serial.println("GPIO 5 on");
    output5State = "on";
    digitalWrite(output5, HIGH);
  } else if (server.arg("pin") == "5" && server.arg("state") == "off") {
    Serial.println("GPIO 5 off");
    output5State = "off";
    digitalWrite(output5, LOW);
  } else if (server.arg("pin") == "4" && server.arg("state") == "on") {
    Serial.println("GPIO 4 on");
    output4State = "on";
    digitalWrite(output4, HIGH);
  } else if (server.arg("pin") == "4" && server.arg("state") == "off") {
    Serial.println("GPIO 4 off");
    output4State = "off";
    digitalWrite(output4, LOW);
  }
  
  String output5Button;
  String output4Button;
  
  // Determine the html button content
  if (output5State=="off") {
    output5Button = "<p><a href=\"/root?pin=5&state=on\"><button class=\"button\">ON</button></a></p>";
  } else {
    output5Button = "<p><a href=\"/root?pin=5&state=off\"><button class=\"button button2\">OFF</button></a></p>";
  } 
  if (output4State=="off") {
    output4Button = "<p><a href=\"/root?pin=4&state=on\"><button class=\"button\">ON</button></a></p>";
  } else {
    output4Button = "<p><a href=\"/root?pin=4&state=off\"><button class=\"button button2\">OFF</button></a></p>";
  }

  // Build the site
  String temp = 
  "<html>\
    <head>\
      <meta name=\"vieport\" content=\"width=device-width, initial-scale=1\">\
      <link rel=\"icon\" href=\"data:,\">\
      <style>\
        html { font-family: Helvetica; display: inline-block; margin: 0px auto; text-align: center;}\
        .button { background-color: #195B6A; border: none; color: white; padding: 16px 40px;\
        text-decoration: none; font-size: 30px; margin: 2px; cursor: pointer;}\
        .button2 {background-color: #77878A;}\
      </style>\
     </head>\
     <body>\
      <h1>ESP8266 Web Server</h1>\
      <p>GPIO 5 - State "+output5State+"</p>\
      "+output5Button+"\
      <p>GPIO 4 - State "+output4State+"</p>\
      "+output4Button+"\
      <p>Uptime: "+hr+":"+min+":"+(sec%60)+"</p>\
    </body>\
  </html>";
  
  server.send(200, "text/html", temp);
}

void loop(){
  server.handleClient();
}
