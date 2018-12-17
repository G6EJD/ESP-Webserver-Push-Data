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

// This function returns an HTML formated page in the correct type for display 
// It uses the Raw string macro 'R' to place commands in PROGMEM
const char Web_page[] PROGMEM = R"=====( 
<!DOCTYPE html>
<html>
  <style>
    .displayobject{
       font-family: sans-serif;
       margin: auto;
       text-align: center;
       width: 50%;
       border: 3px solid #000000;
       padding: 10px;
       background: #558ED5;
    }
    h1 {
      font-size: 36px;
      color: white;
    }
    h4 {
      font-size: 30px;
      color: yellow;
    }
  </style>
  <body>
     <div class = "displayobject">
       <h1>Update only webpage Values - no refresh needed!</h1><br>
       <h4>Temperature reading: <span id="TEMPvalue">0</span>&deg</h4>
       <h4>Humidity reading: <span id="HUMIvalue">0</span>%</h4>
       <h4>Pressure reading: <span id="PRESvalue">0</span>hPa</h4><br>
     </div>
     <script>
       setInterval(function() {getSensorData();}, 1000); // Call the update function every set interval e.g. 1000mS or 1-sec
  
       function getSensorData() {
          var xhttp = new XMLHttpRequest();
          xhttp.onreadystatechange = function() {
          if (this.readyState == 4 && this.status == 200) {
            document.getElementById("TEMPvalue").innerHTML = this.responseText;
          }
        };
        xhttp.open("GET", "TEMPread", true);
        xhttp.send();
        //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
        var xhttp = new XMLHttpRequest();
        xhttp.onreadystatechange = function() {
          if (this.readyState == 4 && this.status == 200) {
            document.getElementById("HUMIvalue").innerHTML = this.responseText;
          }
        };
        xhttp.open("GET", "HUMIread", true);
        xhttp.send();
        //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
        var xhttp = new XMLHttpRequest();
        xhttp.onreadystatechange = function() {
          if (this.readyState == 4 && this.status == 200) {
            document.getElementById("PRESvalue").innerHTML = this.responseText;}
        };  
        xhttp.open("GET", "PRESread", true);
        xhttp.send(); 
      }
    </script>
  </body>
</html>
)=====";

//===================================================================
// This routine is executed when you open a browser at the IP address
//===================================================================
void handleRoot() {
  //String s = Web_page;             //Display HTML contents
  server.send(200, "text/html", Web_page); //Send web page
}

void handleTEMP() { // This function is called by the script to update the sensor value, in this example random data!
  // temp = String(bme.readTemperature(),2);
  // server.send(200, "text/plain", temp));
  server.send(200, "text/plain", String((float)random(195,209)/10,2)); //Send sensor reading when there's a client ajax request
}

void handleHUMI() { // This function is called by the script to update the sensor value, in this example random data!
  server.send(200, "text/plain", String((float)random(501,523)/10,2)); //Send sensor reading when there's a client ajax request
}

void handlePRES() { // This function is called by the script to update the sensor value, in this example random data!
  server.send(200, "text/plain", String((float)random(10161,10169)/10,2)); //Send sensor reading when there's a client ajax request
}

void setup(void) {
  Serial.begin(115200);
  WiFi.mode(WIFI_STA);        // Connect to your wifi
  WiFi.begin(ssid, password); // Start the Wi-Fi services
  Serial.println("Connecting to : "+String(ssid));
  while (WiFi.waitForConnectResult() != WL_CONNECTED) {Serial.print(".");} // Wait for WiFi to connect
  Serial.println(" Connected to : "+String(ssid));
  Serial.print("Use IP address: ");
  Serial.println(WiFi.localIP());  //IP address assigned to your ESP
  //----------------------------------------------------------------
  server.on("/", handleRoot);         // This displays the main webpage, it is called when you open a client connection on the IP address using a browser
  server.on("/TEMPread", handleTEMP); // To update Temperature called by the function getSensorData
  server.on("/HUMIread", handleHUMI); // To update Humidity called by the function getSensorData
  server.on("/PRESread", handlePRES); // To update Pressure called by the function getSensorData
  //----------------------------------------------------------------
  server.begin();                     // Start the webserver
}

void loop(void) {
  server.handleClient();  // Keep checking for a client connection
  if (millis() % 5000 == 0) { count++; Serial.println(count);} // Display a serial diagnostic print to check its running
  delay(1);
}
