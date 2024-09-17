#include <SPI.h>
#include <MFRC522.h>

#define SS_PIN 10
#define RST_PIN 9
MFRC522 mfrc522(SS_PIN, RST_PIN);  // Instance of the class

// Define pin untuk LED dan Buzzer
#define LED_PIN 7
#define BUZZER_PIN 6

// Daftar UID yang valid (contoh)
String validUIDs[] = {
  "0315B718",  // Ganti dengan UID RFID Anda
  "C36AC30B",  // Tambahkan UID RFID lainnya
  "20DE441B",
  "B729C77B"
};

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
  content.toUpperCase();  // Ubah content menjadi huruf besar

  // Pengecekan apakah UID RFID valid
  boolean isValid = false;
  for (int i = 0; i < sizeof(validUIDs) / sizeof(validUIDs[0]); i++) {
    if (content == validUIDs[i]) {
      isValid = true;
      break;
    }
  }

  if (isValid) {
    // Jika UID valid, aktifkan LED dan Buzzer
    digitalWrite(LED_PIN, HIGH);
    digitalWrite(BUZZER_PIN, HIGH);
    delay(500);  // LED dan Buzzer aktif selama 500ms
    digitalWrite(LED_PIN, LOW);
    digitalWrite(BUZZER_PIN, LOW);
    Serial.println("Access Granted");
  } else {
    // Jika UID tidak valid
    Serial.println("Access Denied");
  }

  // Halt PICC
  mfrc522.PICC_HaltA();
}
