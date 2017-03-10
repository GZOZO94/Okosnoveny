#include <ESP8266WiFi.h>
#include <Wire.h>
#include <Adafruit_BMP085.h>

const char* ssid     = "TP1-kp";
const char* password = "szentantal";
Adafruit_BMP085 bmp;
const char* host = "helloka.herokuapp.com";

void setup() {
  Wire.pins(4,5); 
  Wire.setClock(400000);
  Serial.begin(115200);
  while (!bmp.begin()) {
    Serial.println("Could not find a valid BMP085 sensor, check wiring!");
  }
  delay(10);

  // We start by connecting to a WiFi network

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
}

void loop() {
  delay(5000);
  Serial.print("connecting to ");
  Serial.println(host);

  // Use WiFiClient class to create TCP connections
  WiFiClient client;
  const int httpPort = 80;
  if(!client.connect(host, httpPort)) {
    Serial.println("connection failed");
    return;
  }
  String temp=(String)bmp.readTemperature();
  String hum="0";
  // We now create a URI for the request
  String url = "/Sender.php?temp=" + temp + "&hum=" + hum;

  Serial.print("Requesting URL: ");
  Serial.println(url);

  // This will send the request to the server
  client.print(String("GET ") + url + " HTTP/1.1\r\n" +
               "Host: " + host + "\r\n" + 
               "Connection: close\r\n\r\n");
  delay(10);

  // Read all the lines of the reply from server and print them to Serial
  Serial.println("Respond:");
  while(client.available()){
    String line = client.readStringUntil('\r');
    Serial.print(line);
  }

  Serial.println();
  Serial.println("closing connection");
}
