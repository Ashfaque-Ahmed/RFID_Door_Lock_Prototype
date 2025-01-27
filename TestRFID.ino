#include <SPI.h>
#include <MFRC522.h>
constexpr uint8_t RST_PIN =5 ;     // Configurable, see typical pin layout above
constexpr uint8_t SS_PIN =10 ;     // Configurable, see typical pin layout above
MFRC522 rfid(SS_PIN, RST_PIN); // Instance of the class
MFRC522::MIFARE_Key key;
String tag;
void setup() {
  Serial.begin(9600);
  SPI.begin(); // Init SPI bus
  rfid.PCD_Init(); // Init MFRC522
 
}
void loop() {
  if ( ! rfid.PICC_IsNewCardPresent())
    return;
  if (rfid.PICC_ReadCardSerial()) {
    for (byte i = 0; i < 4; i++) {
      tag += rfid.uid.uidByte[i];
    }
    Serial.println(tag);
    if (tag == "1310145151") {
      Serial.println("Access Granted!");
      delay(100);
    } else {
      Serial.println("Access Denied!");
      delay(100);
    }
    tag = "";
    rfid.PICC_HaltA();
    rfid.PCD_StopCrypto1();
  }
}
