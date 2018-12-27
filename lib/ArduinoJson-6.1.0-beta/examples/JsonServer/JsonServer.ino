// ArduinoJson - arduinojson.org
// Copyright Benoit Blanchon 2014-2018
// MIT License
//
// This example shows how to implement an HTTP server that sends JSON document
// in the responses.
// It uses the Ethernet library but can be easily adapted for Wifi.
//
// It sends the value of the analog and digital pins.
// The JSON document looks like the following:
// {
//   "analog": [ 0, 1, 2, 3, 4, 5 ],
//   "digital": [ 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13 ]
// }

#include <ArduinoJson.h>
#include <Ethernet.h>
#include <SPI.h>

byte mac[] = {0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED};
EthernetServer server(80);

void setup() {
  // Initialize serial port
  Serial.begin(9600);
  while (!Serial) continue;

  // Initialize Ethernet libary
  if (!Ethernet.begin(mac)) {
    Serial.println(F("Failed to initialize Ethernet library"));
    return;
  }

  // Start to listen
  server.begin();

  Serial.println(F("Server is ready."));
  Serial.print(F("Please connect to http://"));
  Serial.println(Ethernet.localIP());
}

void loop() {
  // Wait for an incomming connection
  EthernetClient client = server.available();

  // Do we have a client?
  if (!client) return;

  Serial.println(F("New client"));

  // Read the request (we ignore the content in this example)
  while (client.available()) client.read();

  // Allocate the JSON document
  // Use arduinojson.org/assistant to compute the capacity.
  StaticJsonDocument<500> doc;

  // Make our document represent an object
  JsonObject root = doc.to<JsonObject>();

  // Create the "analog" array
  JsonArray analogValues = root.createNestedArray("analog");
  for (int pin = 0; pin < 6; pin++) {
    // Read the analog input
    int value = analogRead(pin);

    // Add the value at the end of the array
    analogValues.add(value);
  }

  // Create the "digital" array
  JsonArray digitalValues = root.createNestedArray("digital");
  for (int pin = 0; pin < 14; pin++) {
    // Read the digital input
    int value = digitalRead(pin);

    // Add the value at the end of the array
    digitalValues.add(value);
  }

  Serial.print(F("Sending: "));
  serializeJson(root, Serial);
  Serial.println();

  // Write response headers
  client.println("HTTP/1.0 200 OK");
  client.println("Content-Type: application/json");
  client.println("Connection: close");
  client.println();

  // Write JSON document
  serializeJsonPretty(root, client);

  // Disconnect
  client.stop();
}

// Visit https://arduinojson.org/v6/example/http-server/ for more.
