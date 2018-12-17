#ifdef ESP8266
#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
ESP8266WebServer server(80);
#else
#include <WiFi.h>
#include <WebServer.h>
WebServer server(80);
#endif

#include <WiFiClient.h>

int count; // global counter for diagnostics
//Enter your Wi-Fi SSID and PASSWORD
const char* ssid     = "your_SSID";
const char* password = "your_PASSWORD";

void Webpage() {
  String webpage = "<!DOCTYPE html>";
  webpage += "<html>";
  webpage += "<style>";
  webpage += ".displayobject{";
  webpage += "font-family: sans-serif;";
  webpage += "margin: auto;";
  webpage += "text-align: center;";
  webpage += "width: 50%;";
  webpage += "border: 3px solid #000000;";
  webpage += "padding: 10px;";
  webpage += "background: #558ED5;";
  webpage += "}";
  webpage += "h1 {";
  webpage += "font-size: 36px;";
  webpage += "color: white;";
  webpage += "}";
  webpage += "h4 {";
  webpage += "font-size: 30px;";
  webpage += "color: yellow;";
  webpage += "}";
  webpage += "</style>";
  webpage += "<body>";
  webpage += "<div class = \"displayobject\">";
  webpage += "<h1>Update webpage to get current readings - refresh needed!</h1><br>";
  webpage += "<h4>Temperature reading: <span id=\"TEMPvalue\">" + String((float)random(195, 209) / 10, 2) + "</span>&deg</h4>";
  webpage += "<h4>Humidity reading: <span id=\"HUMIvalue\">"    + String((float)random(501, 523) / 10, 2) + "</span>%</h4>";
  webpage += "<h4>Pressure reading: <span id=\"PRESvalue\">"    + String((float)random(10161, 10169) / 10, 2) + "</span>hPa</h4><br>";
  webpage += "</div>";
  webpage += "</body>";
  webpage += "</html>";
  server.send(200, "text/html", webpage); //Send web page
}

//===================================================================
void handleRoot() {
  Webpage();
}

void setup(void) {
  Serial.begin(115200);
  WiFi.mode(WIFI_STA);        // Connect to your wifi
  WiFi.begin(ssid, password); // Start the Wi-Fi services
  Serial.println("Connecting to : " + String(ssid));
  while (WiFi.waitForConnectResult() != WL_CONNECTED) {
    Serial.print("."); // Wait for WiFi to connect
  }
  Serial.println(" Connected to : " + String(ssid));
  Serial.print("Use IP address: ");
  Serial.println(WiFi.localIP());  //IP address assigned to your ESP
  //----------------------------------------------------------------
  server.on("/", handleRoot);         // This displays the main webpage, it is called when you open a client connection on the IP address using a browser
  //----------------------------------------------------------------
  server.begin();                     // Start the webserver
}

void loop(void) {
  server.handleClient();  // Keep checking for a client connection
  if (millis() % 5000 == 0) {
    count++;  // Display a serial diagnostic print to check its running
    Serial.println(count);
  }
  delay(1);
}
