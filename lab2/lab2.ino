
#include "a5.h"
#include <Arduino.h>
#include <SoftwareSerial.h> // Optional, for software-based UART

byte stream_cipher_key[15]; // Replace with your encryption stream_cipher_key
byte encryptedData[15];

void setup() {
  Serial.begin(9600); // Set the baud rate to match your configuration
  const byte initial_key[8] = { 0x78, 0x33, 0x87, 0x12, 0x73, 0x90, 0x85, 0x34}; 
  key_setup(initial_key, 0x12);
  run_key_gen(stream_cipher_key, nullptr);

}

void loop() {
  // Read 15 bytes from the serial UART
  if (Serial.available() >= 15) {
    Serial.readBytes(stream_cipher_key, 15);
    
    // Prompt the user to enter a message for encryption
    Serial.println("Enter a message for encryption:");
    
    // Wait until a message is received
    while (!Serial.available()) {
      // Wait for user input
    }
    
    // Read the message from the serial UART
    String message = Serial.readStringUntil('\n');
    
    // Check if the message length matches the stream_cipher_key length
    if (message.length() == 15) {
      // Perform XOR encryption
      for (int i = 0; i < 15; i++) {
        encryptedData[i] = stream_cipher_key[i] ^ message[i];
      }
      
      // Send the encrypted data back over UART
      Serial.println("Encrypted Data:");
      for (int i = 0; i < 15; i++) {
        Serial.print(stream_cipher_key[i], HEX);
      }
      Serial.println();
    } else {
      Serial.println("Message length must match the stream_cipher_key length (15 bytes).");
    }
  }
}

// TODO: fix it or sth, idk
