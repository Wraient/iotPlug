#include <ESP8266WiFi.h>
#include <WiFiClientSecure.h>  // Include WiFiClientSecure library
#include <ArduinoJson.h>
#include <ESP8266HTTPClient.h>

#define D1 5
#define D2 4
#define D3 0
#define D4 2

const char* ssid = "Rushi";
const char* password = "mini1111";
const char* apiEndpoint = "https://192.168.1.7:8000/manageport/show_data/";
bool secure = false;

if secure{
  WiFiClientSecure wifiClient;  // Use WiFiClientSecure instead of WiFiClient
} else {
  WiFiClient wifiClient;
}

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
    if secure{
      wifiClient.setInsecure();
    }
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

    if (jsonBuffer.is<JsonObject>()) {
      // The data key is an object, so access it directly
      JsonObject jsonData = jsonBuffer["data"];

      if (jsonData.isNull()) {
          Serial.println("No data key found in JSON.");
          return;
      }

      // Now, access the array of products
      JsonArray productsArray = jsonData["data"];

      for (JsonObject product : productsArray) {
          const int id = product["id"];
          bool state = product["state"];

          if (id == 1) {
              if (state == true) {
                  turnOnPort(D1);
              } else {
                  turnOffPort(D1);
              }
          }
          if (id == 2) {
              if (state == true) {
                  turnOnPort(D2);
              } else {
                  turnOffPort(D2);
              }
          }
          if (id == 3) {
              if (state == true) {
                  turnOnPort(D3);
              } else {
                  turnOffPort(D3);
              }
          }
          if (id == 4) {
              if (state == true) {
                  turnOnPort(D4);
              } else {
                  turnOffPort(D4);
              }
          }

          Serial.println("ID: " + String(id));
          Serial.println("State: " + String(state));
          Serial.println("-------------------");
      }
    } else {
      Serial.println("JSON data is not an object.");
    }

    } else {
      Serial.printf("HTTP GET request failed, error code: %d\n", httpCode);
    }

    http.end();

    delay(500);  // Wait for 5 seconds before making the next request
  }
}

void turnOnPort(int id) {
  digitalWrite(id, HIGH);
}

void turnOffPort(int id) {
  digitalWrite(id, LOW);
}
