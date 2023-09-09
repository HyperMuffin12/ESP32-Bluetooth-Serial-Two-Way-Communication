#include <BluetoothSerial.h>

BluetoothSerial SerialBT;

const char* deviceName = "ESP32Receiver"; // Set your device name here
const int maxMessageLength = 100; // Maximum length of a message

void setup() {
  Serial.begin(115200);
  SerialBT.begin(deviceName);

  while (!SerialBT.connected()) {
    delay(1000);
    Serial.println("Waiting for a connection...");
  }
}

void loop() {
  // Read user input from Serial Monitor and send it
  if (Serial.available()) {
    char outgoingMessage[maxMessageLength];
    int messageLength = Serial.readBytesUntil('\n', outgoingMessage, maxMessageLength - 1);
    outgoingMessage[messageLength] = '\0'; // Null-terminate the message
    SerialBT.print(outgoingMessage);
    Serial.println("Message sent: ");
    Serial.println(outgoingMessage);
  }

  // Check for incoming messages
  if (SerialBT.available()) {
    char incomingMessage[maxMessageLength];
    int messageLength = SerialBT.readBytesUntil('\n', incomingMessage, maxMessageLength - 1);
    incomingMessage[messageLength] = '\0'; // Null-terminate the message
    Serial.print("Received: ");
    Serial.println(incomingMessage);

    // You can add your message processing logic here
  }
}
