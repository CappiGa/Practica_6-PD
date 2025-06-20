#include <Arduino.h>
#include <SD.h>
#include <MFRC522.h>

#define SS_PIN 5 // Chip Select del RC522
#define RST_PIN 2 // Reset del RC522


MFRC522 rfid(SS_PIN, RST_PIN);

void setup() {
Serial.begin(115200);

// Inicializar comunicación SPI
SPI.begin();

// Inicializar RFID
rfid.PCD_Init();
Serial.println("Escaneando tarjetas...");
}

void loop() {
// Revisar si hay una tarjeta presente
if (!rfid.PICC_IsNewCardPresent() || !rfid.PICC_ReadCardSerial()) {
return;
}

// Leer el ID de la tarjeta
String uid = "";
for (byte i = 0; i < rfid.uid.size; i++) {
uid += String(rfid.uid.uidByte[i], HEX);
}
Serial.print("ID de tarjeta detectada: ");
Serial.println(uid);


// Parar la lectura de la tarjeta
rfid.PICC_HaltA();
rfid.PCD_StopCrypto1();
}