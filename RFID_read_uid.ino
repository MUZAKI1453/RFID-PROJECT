#include <SPI.h>
#include <MFRC522.h>

#define SS_PIN 10
#define RST_PIN 9
MFRC522 mfrc522(SS_PIN, RST_PIN);  // Instance of the class

// Define pin untuk LED dan Buzzer
#define LED_PIN 7
#define BUZZER_PIN 6

void setup() {
  Serial.begin(9600);   // Initialize serial communications
  SPI.begin();          // Init SPI bus
  mfrc522.PCD_Init();   // Init MFRC522 RFID
  Serial.println("Scan RFID Tag");

  // Inisialisasi pin LED dan Buzzer sebagai output
  pinMode(LED_PIN, OUTPUT);
  pinMode(BUZZER_PIN, OUTPUT);

  // Pastikan LED dan Buzzer mati saat awal
  digitalWrite(LED_PIN, LOW);
  digitalWrite(BUZZER_PIN, LOW);
}

void loop() {
  // Look for new cards
  if ( ! mfrc522.PICC_IsNewCardPresent()) {
    return;
  }

  // Select one of the cards
  if ( ! mfrc522.PICC_ReadCardSerial()) {
    return;
  }

  // Print Card UID
  Serial.print("UID tag : ");
  String content = "";
  for (byte i = 0; i < mfrc522.uid.size; i++) {
    Serial.print(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " ");
    Serial.print(mfrc522.uid.uidByte[i], HEX);
    content.concat(String(mfrc522.uid.uidByte[i] < 0x10 ? "0" : ""));
    content.concat(String(mfrc522.uid.uidByte[i], HEX));
  }
  Serial.println();

  // Ubah content menjadi uppercase
  content.toUpperCase();

  // Aktifkan LED dan Buzzer
  digitalWrite(LED_PIN, HIGH);
  digitalWrite(BUZZER_PIN, HIGH);
  delay(500);  // LED dan Buzzer aktif selama 500ms
  digitalWrite(LED_PIN, LOW);
  digitalWrite(BUZZER_PIN, LOW);

  // Halt PICC
  mfrc522.PICC_HaltA();
}
