#include <ESP8266WiFi.h>
#include <WiFiClientSecure.h>  // Include WiFiClientSecure library
#include <ArduinoJson.h>
#include <ESP8266HTTPClient.h>

#define D1 5
#define D2 4
#define D3 0
#define D4 2

const char* ssid = "Rushi";
const char* password = "arduinopassword";
const char* apiEndpoint = "https://www.devrushi.me/manageport/show_data/";

WiFiClientSecure wifiClient;  // Use WiFiClientSecure instead of WiFiClient

void turnOnPort(int id);
void turnOffPort(int id);

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

    wifiClient.setInsecure();
    HTTPClient http;
    http.setTimeout(10000);
    // Use wifiClient for secure connection
    http.begin(wifiClient, apiEndpoint);

    int httpCode = http.GET();

    if (httpCode > 0) {
      String payload = http.getString();
      String jsonString = payload;

      const size_t bufferSize = 2 * JSON_OBJECT_SIZE(3) + JSON_ARRAY_SIZE(3) + 100;
      DynamicJsonDocument jsonBuffer(bufferSize);

      DeserializationError error = deserializeJson(jsonBuffer, jsonString);

      if (error) {
        Serial.print("JSON parsing failed! Error code: ");
        Serial.println(error.c_str());
        return;
      }

      if (jsonBuffer.containsKey("data")) {
        JsonArray productsArray = jsonBuffer["data"].as<JsonArray>();

        for (JsonObject product : productsArray) {
          String id = product["id"].as<String>(); // Convert ID to string
          bool state = product["state"];

          if (id == "1") {
              if (state == false) {
                  turnOnPort(D1);
              } else {
                  turnOffPort(D1);
              }
          } else if (id == "2") {
              if (state == false) {
                  turnOnPort(D2);
              } else {
                  turnOffPort(D2);
              }
          } else if (id == "3") {
              if (state == false) {
                  turnOnPort(D3);
              } else {
                  turnOffPort(D3);
              }
          } else if (id == "4") {
              if (state == false) {
                  turnOnPort(D4);
              } else {
                  turnOffPort(D4);
              }
          }

          // Your existing logic for processing JSON data

          // Serial.println("ID: " + id);
          // Serial.println("State: " + String(state));
          // Serial.println("-------------------");
        }
      } else {
        Serial.println("JSON data does not contain 'data' key or is not formatted as expected.");
      }

    } else {
      Serial.printf("HTTP GET request failed, error code: %d\n", httpCode);
    }

    http.end();

    // delay();  // Wait for 5 seconds before making the next request
  }
}
void turnOnPort(int id) {
  digitalWrite(id, HIGH);
}

void turnOffPort(int id) {
  digitalWrite(id, LOW);
}
