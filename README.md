# Servo Motor Control with RFID
In this project, an RFID reader is used to read RFID tags and the servo motor is controlled to perform a specific action, such as opening a door or a gate. In this article, we will discuss how to make Servo control with RFID using Arduino.

## What is RFID Card?

> <img src="https://github.com/musarda/Servo-Motor-Control-with-RFID/blob/main/img/image.png" title="RFID" alt="RFID" width="256">

RFID card is a kind of smart card created using Radio Frequency Identification (RFID) technology and can be used for many different purposes. These cards can be recognized and communicated by RFID readers at close range, thanks to a microchip and antenna on them.

RFID cards are often used for purposes such as authentication, access control, tracking and inventory management. For example, employees in a workplace may need to have RFID cards to enter a particular section. These cards can open the door if people who have access to the department hold their cards to the RFID reader.

RFID cards can also be used for many different purposes, such as the production process of products, storage and transportation, customer loyalty programs and even animal tracking.

Here are the steps to follow: 

## Materials Required
* Arduino Uno
* RFID reader (MFRC522)
* Servo motor
* Jumper cable
* Breadboard
* RFID tags

## Wiring
> <img src="https://github.com/musarda/Servo-Motor-Control-with-RFID/blob/main/img/wiring_diagram.png" title="RFID" alt="RFID" width="512">
* Connect the VCC and GND pins of the RFID reader to the 3.3V and GND pins of the Arduino board, respectively.
* Connect the SDA, SCK, MOSI, MISO pins of the RFID reader to the digital pins 10, 13, 11, and 12 of the Arduino board, respectively.
* Connect the VCC and GND pins of the servo motor to the 5V and GND pins of the Arduino board, respectively.
* Connect the signal pin of the servo motor to the digital pin 9 of the Arduino board.

## Code
First, you need to install the MFRC522 library. To do that, go to Sketch > Include Library > Manage Libraries in the Arduino IDE, and search for "MFRC522". Install the library and restart the IDE. Then, copy the following code and upload it to your Arduino board.

* **[Code](https://github.com/musarda/Servo-Motor-Control-with-RFID/blob/main/Code/servo_control.ino)**

## Explanation
The code starts by including the required libraries: `SPI`, `MFRC522`, and `Servo`. Then, it defines some constants, such as the SS_PIN and RST_PIN for the RFID reader and creates instances of the MFRC522 and Servo classes.

In the `setup()` function, the serial communication is initialized, the SPI bus is initialized, the MFRC522 is initialized, and the servo motor is attached to pin 9.
``` ino
void setup() {
  Serial.begin(9600);              // Initialize serial communication
  SPI.begin();                     // Initialize SPI bus
  mfrc522.PCD_Init();              // Initialize MFRC522
  myservo.attach(9);               // Attach servo to pin 9
}
```
In the `loop()` function, the code checks if a new RFID card is present and reads its UID. If the UID matches the authorized tag UID, the code prints "Authorized access" on the serial monitor, rotates the servo to 180 degrees, waits for a second, and then rotates the servo to 0 degrees. If the UID does not match, the code prints "Unauthorized access" on the serial monitor.

``` ino
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
```

## Testing
> Once you have uploaded the code to your Arduino board, open the serial monitor (Tools > Serial Monitor) and set the baud rate to 9600. Place an authorized RFID tag near the RFID reader and check if the servo motor rotates to 180 degrees and then to 0 degrees. Then, place an unauthorized RFID tag near the RFID reader and check if the servo motor does not rotate.
