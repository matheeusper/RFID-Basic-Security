#include <Arduino.h>
#include <SPI.h>
#include <MFRC522.h>

#define RST_PIN 9
#define SS_PIN 10

MFRC522 mfrc522(SS_PIN, RST_PIN);

void setup() {
  Serial.begin(9600);
  while (!Serial);
  SPI.begin();
  mfrc522.PCD_Init();
  Serial.println("Aguardando leitura do cartão RFID...");
}

void loop() {
  if (mfrc522.PICC_IsNewCardPresent() && mfrc522.PICC_ReadCardSerial()) {
    String variavel = "";
    for (byte i = 0; i < mfrc522.uid.size; i++) {
      variavel.concat(String(mfrc522.uid.uidByte[i] < 0x10 ? "0" : ""));
      variavel.concat(String(mfrc522.uid.uidByte[i], HEX));
    }
    Serial.println("Variável lida: " + variavel);
    String novaVariavel = "exemplo123"; // Gera automaticamente uma nova variável
    Serial.print("Nova variável: ");
    Serial.println(novaVariavel);
    variavel = novaVariavel;
  }
}
