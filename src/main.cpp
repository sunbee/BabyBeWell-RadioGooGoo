#include <Arduino.h>
#include <SoftwareSerial.h>

#define RX_PIN 25
#define TX_PIN 26

SoftwareSerial lora(RX_PIN, TX_PIN);

void setup() {
  Serial.begin(9600);
  while(!Serial);

  lora.begin(9600);
  Serial.println("Completed setup for LoRa reception!");
  delay(1000);

  char* lora_IPR="AT+IPR=9600\r\n";
  char* lora_ADDRESS = "AT+ADDRESS=121\r\n";    // 0~65535(default 0)
  char* lora_NETWORKID = "AT+NETWORKID=6\r\n";  // 0~16(default 0)
  
}

void loop() {
  // put your main code here, to run repeatedly:
  if (lora.available()) {
    String messageRx = lora.readStringUntil('\n');
    Serial.println("Received: " + messageRx);

    if (messageRx.startsWith("+RCV")) {
      // Extract the address, message length, and message
      int addressIndex = messageRx.indexOf(":") + 1;
      int lengthIndex = messageRx.indexOf(",", addressIndex) + 1;
      int messageIndex = messageRx.indexOf(",", lengthIndex) + 1;

      int address = messageRx.substring(addressIndex, lengthIndex - 1).toInt();
      int length = messageRx.substring(lengthIndex, messageIndex - 1).toInt();
      String message = messageRx.substring(messageIndex);

      Serial.println("Address: " + String(address));
      Serial.println("Length: " + String(length));
      Serial.println("Message: " + message);
    }
  }
}
