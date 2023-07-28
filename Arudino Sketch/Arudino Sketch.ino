#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include <ArduinoJson.h>

#define D1 5
#define D2 4
#define D3 0
#define D4 2


const char* ssid = "Loading..";
const char* password = "rutuja1721";
const char* apiEndpoint = "http://192.168.1.7:8000/api/products/?format=json";

WiFiClient wifiClient;

void setup() {
  
  pinMode(D1, OUTPUT);
  pinMode(D2, OUTPUT);
  pinMode(D3, OUTPUT);
  pinMode(D4, OUTPUT);


  Serial.begin(115200);
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println();
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
}

void loop() {
  if (WiFi.status() == WL_CONNECTED) {
    HTTPClient http;
    http.begin(wifiClient, apiEndpoint);

    int httpCode = http.GET();

    if (httpCode > 0) {
      String payload = http.getString();
      String jsonString = payload;
      // Allocate a buffer to store the JSON data
      const size_t bufferSize = 2 * JSON_OBJECT_SIZE(3) + JSON_ARRAY_SIZE(3) + 100; // Adjust the buffer size as needed
    DynamicJsonDocument jsonBuffer(bufferSize);

    // Parse the JSON data
    DeserializationError error = deserializeJson(jsonBuffer, jsonString);

    // Check for parsing errors
    if (error) {
      Serial.print("JSON parsing failed! Error code: ");
      Serial.println(error.c_str());
      return;
    }

    // Check if the parsed JSON is an array
    if (jsonBuffer.is<JsonArray>()) {
      // Get the array of product objects
      JsonArray productsArray = jsonBuffer.as<JsonArray>();

      // Loop through each product object in the array
      for (JsonObject product : productsArray) {
        // Unpack the JSON data for each product
        // Serial.println(product);
        const int id = product["id"];
        // const char* description = product["description"];
        bool state = product["state"];

        if(id==1){
          if (state==true){
          turnOnPort(D1);
          } else {
          turnOffPort(D1);
          }
        }
        if(id==2){
          if (state==true){
          turnOnPort(D2);
          } else {
          turnOffPort(D2);
          }
        }
        if(id==3){
          if (state==true){
          turnOnPort(D3);
          } else {
          turnOffPort(D3);
          }
        }
        if(id==4){
          if (state==true){
          turnOnPort(D4);
          } else {
          turnOffPort(D4);
          }
        }

        // Print the unpacked data for each product
        Serial.println("ID: " + String(id));
        // Serial.println("Description: " + String(description));
        Serial.println("State: " + String(state));
        Serial.println("-------------------");
      }
    } else {
      Serial.println("JSON data is not an array.");
    }

    } else {
      Serial.printf("HTTP GET request failed, error code: %d\n", httpCode);
    }

    http.end();

    delay(2000);  // Wait for 5 seconds before making the next request
  }
}

void turnOnPort(int id) {
  digitalWrite(id, HIGH);
}

void turnOffPort(int id) {
  digitalWrite(id, LOW);
}

