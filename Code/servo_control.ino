#include <SPI.h>
#include <MFRC522.h>
#include <Servo.h>

#define SS_PIN 10
#define RST_PIN 9

MFRC522 mfrc522(SS_PIN, RST_PIN);   // Create MFRC522 instance
Servo myservo;                      // Create Servo instance

void setup() {
  Serial.begin(9600);              // Initialize serial communication
  SPI.begin();                     // Initialize SPI bus
  mfrc522.PCD_Init();              // Initialize MFRC522
  myservo.attach(9);               // Attach servo to pin 9
}

void loop() {
  if (mfrc522.PICC_IsNewCardPresent() && mfrc522.PICC_ReadCardSerial()) {
    // Read RFID tag UID
    Serial.print("UID tag :");
    String content = "";
    byte letter;
    for (byte i = 0; i < mfrc522.uid.size; i++) {
      Serial.print(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " ");
      Serial.print(mfrc522.uid.uidByte[i], HEX);
      content.concat(String(mfrc522.uid.uidByte[i] < 0x10 ? "0" : ""));
      content.concat(String(mfrc522.uid.uidByte[i], HEX));
    }
    Serial.println();
    Serial.print("Message : ");
    content.toUpperCase();

    // Check for authorized tags
    if (content.substring(1) == "YOUR_RFID_TAG_UID") {
      Serial.println("Authorized access");
      myservo.write(180);          // Rotate servo to 180 degrees
      delay(1000);
      myservo.write(0);            // Rotate servo to 0 degrees
    } else {
      Serial.println("Unauthorized access");
    }
  }
}
