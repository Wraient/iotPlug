#include <ESP8266WiFi.h>
#include <WiFiClientSecure.h>
#include <ArduinoJson.h>
#include <ESP8266HTTPClient.h>

#define D1 5
#define D2 4
#define D3 0
#define D4 2

const char* ssid = "Rushi";
const char* password = "mini1111";
const char* apiEndpoint = "https://selfish-mole-81.telebit.io/manageport/show_data/";

// Flag to indicate a secure connection
bool secure = true;

// Declare WiFiClientSecure
WiFiClientSecure wifiClient;

// Function prototypes
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
    HTTPClient http;
    http.setTimeout(10000);

    // Set up WiFiClientSecure for a secure connection
    wifiClient.setInsecure();

    http.begin(wifiClient, apiEndpoint);

    int httpCode = http.GET();

    if (httpCode > 0) {
      String payload = http.getString();
      String jsonString = payload;

      const size_t bufferSize = JSON_ARRAY_SIZE(1) + 4 * JSON_OBJECT_SIZE(2) + JSON_OBJECT_SIZE(4) + 50;
      DynamicJsonDocument jsonBuffer(bufferSize);

      DeserializationError error = deserializeJson(jsonBuffer, jsonString);

      if (error) {
        Serial.print("JSON parsing failed! Error code: ");
        Serial.println(error.c_str());
        return;
      }

      // Ensure that JSON data contains "data" key and it's an array
      if (jsonBuffer.containsKey("data") && jsonBuffer["data"].is<JsonArray>()) {
        JsonArray productsArray = jsonBuffer["data"].as<JsonArray>();

        for (JsonObject product : productsArray) {
          const int id = product["id"];
          bool state = product["state"];

          // Perform actions based on received data
          // (e.g., turn on/off ports)
          if (id == 1) {
            if (state == true) {
              turnOnPort(D1);
            } else {
              turnOffPort(D1);
            }
          } else if (id == 2) {
            if (state == true) {
              turnOnPort(D2);
            } else {
              turnOffPort(D2);
            }
          } else if (id == 3) {
            if (state == true) {
              turnOnPort(D3);
            } else {
              turnOffPort(D3);
            }
          } else if (id == 4) {
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
        Serial.println("Invalid JSON structure. No 'data' array found.");
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
