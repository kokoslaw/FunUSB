#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>

int operationPin = 0;
int modePin = 2;
bool modeSelector = true; //true = URL_Mode, false = Macro_Mode
ESP8266WebServer server(80);

void handleRoot();
void handleOperationStart();
void handlePageNotFound();
void handleChangeURL();
void handleChangeMode();

void setup() 
{
  pinMode(operationPin, OUTPUT);
  pinMode(modePin, OUTPUT);
  digitalWrite(modePin, HIGH);
  digitalWrite(operationPin, LOW);
  
  Serial.begin(9600);
  WiFi.softAP("AP", "ESPpassword");
  
  server.on("/" , handleRoot);
  server.on("/operationStart" , handleOperationStart);
  server.on("/changeURL" , handleChangeURL);
  server.on("/changeMode" , handleChangeMode);
  server.onNotFound(handlePageNotFound);

  server.begin(); 
}

void loop() 
{
  server.handleClient(); 
}

void handleRoot()
{
  String serverResponse = "";
  if(modeSelector)
    serverResponse = "<!DOCTYPE html> <html> <head> <title>Fun USB</title> <meta charset=\"UTF-8\" /> <style> a { border: 2px dashed gray; margin: 10px; text-decoration: none; color: gray; font-size:70px; position: relative; } .container { border: 2px dashed gray; width:min-content; padding: 1%; margin: 0.5%; position: relative; left: 40%; } textarea { background-color: black; font-size: 30px; color: gray; width: 400px; margin: 10px; } .btn { font-size: 60px; color: gray; margin-left: 10px; border: 2px dashed gray; background-color: black; } </style> </head> <body style=\"background-color: black;\"> <div id=\"kkk\" class=\"container\"> <script> \"use strict\"; function redirectWithParams(key, value) {var searchParams = new URLSearchParams(window.location.search); searchParams.set(key, value); var newRelativePathQuery = window.location.pathname + \"changeURL?\" + searchParams.toString(); window.location.href = newRelativePathQuery; } \"use strict\"; function getTextAreaValue() { var textarea = document.getElementById('textarea'); var value = textarea.value; return value; } function handlerMouseDown() { redirectWithParams(\"URL\", getTextAreaValue()); return false; } </script> <h4> <a href=\"/operationStart\"> Start </a> </h4> <a href=\"/changeMode\"> Mode_URL </a>  <textarea id=\"textarea\"></textarea> <a onclick=\"return handlerMouseDown()\" href=\"ee\"> Edit </a> </div> </body> </html>";
  else
    serverResponse = "<!DOCTYPE html> <html> <head> <title>Fun USB</title> <meta charset=\"UTF-8\" /> <style> a { border: 2px dashed gray; margin: 10px; text-decoration: none; color: gray; font-size:70px; position: relative; } .container { border: 2px dashed gray; width:min-content; padding: 1%; margin: 0.5%; position: relative; left: 40%; } textarea { background-color: black; font-size: 30px; color: gray; width: 400px; margin: 10px; } .btn { font-size: 60px; color: gray; margin-left: 10px; border: 2px dashed gray; background-color: black; } </style> </head> <body style=\"background-color: black;\"> <div id=\"kkk\" class=\"container\"> <script> \"use strict\"; function redirectWithParams(key, value) {var searchParams = new URLSearchParams(window.location.search); searchParams.set(key, value); var newRelativePathQuery = window.location.pathname + \"changeURL?\" + searchParams.toString(); window.location.href = newRelativePathQuery; } \"use strict\"; function getTextAreaValue() { var textarea = document.getElementById('textarea'); var value = textarea.value; return value; } function handlerMouseDown() { redirectWithParams(\"URL\", getTextAreaValue()); return false; } </script> <h4> <a href=\"/operationStart\"> Start </a> </h4> <a href=\"/changeMode\"> Mode_MACRO </a> <textarea id=\"textarea\"></textarea> <a onclick=\"return handlerMouseDown()\" href=\"ee\"> Edit </a> </div> </body> </html>";

  
  server.send(200, "text/html", serverResponse);
}

void handleOperationStart()
{
  String serverResponse = "<!DOCTYPE html> <html> <head> <title>Old Page</title> <meta charset=\"UTF-8\" /> <meta http-equiv=\"refresh\" content=\"1; URL=/\" /> </head> <body> </body> </html>";
  digitalWrite(operationPin, HIGH);
  delay(20);
  digitalWrite(operationPin, LOW);
  server.send(200, "text/html", serverResponse);
}

void handleChangeURL()
{
  String serverResponse = "<!DOCTYPE html> <html> <head> <title>Redirecting</title> <meta charset=\"UTF-8\" /> <meta http-equiv=\"refresh\" content=\"1; URL=/\" /> </head> <body> </body> </html>";

  if(server.arg("URL") != "")
  {
    String newURL = server.arg("URL");
    Serial.print(newURL);
  }
  
  server.send(200, "text/html", serverResponse);
}

void handleChangeMode()
{
  String serverResponse = "<!DOCTYPE html> <html> <head> <title>Redirecting</title> <meta charset=\"UTF-8\" /> <meta http-equiv=\"refresh\" content=\"1; URL=/\" /> </head> <body> </body> </html>";
  modeSelector = !modeSelector;
  
  if(modeSelector) digitalWrite(modePin, HIGH);
  else digitalWrite(modePin, LOW);
  server.send(200, "text/html", serverResponse);
}

void handlePageNotFound(){
  String serverResponse = "<!DOCTYPE html> <html> <head> <title>Redirecting</title> <meta charset=\"UTF-8\" /> <meta http-equiv=\"refresh\" content=\"1; URL=/\" /> </head> <body> </body> </html>";
  server.send(200, "text/html", serverResponse);
}
