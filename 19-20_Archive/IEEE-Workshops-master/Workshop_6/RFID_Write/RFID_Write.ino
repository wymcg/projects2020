// Write Data
#include <SPI.h>
#include <MFRC522.h>

// Create mfrc522 instance using SDA and RST
MFRC522 mfrc522(10, 9);
// Initialize a MIFARE key to be used globally
MFRC522::MIFARE_Key key;


void setup() {
  Serial.begin(9600);

  // Start the SPI communications
  SPI.begin();
  
  // Initialize the card
  mfrc522.PCD_Init();
  
  // Show that the card is ready
  Serial.println("Ready to write MIFARE PICC"); 
  
  // Prepare the key to access data set to FFFFFFFFFFFF at chip delivery
  // A company or user can change this key, usually kept secret on reader side
  // If a false key is provided, the card can not be read
  for (byte i = 0; i < 6; i++) key.keyByte[i] = 0xFF;

  // Set a timeout for Serial functions
  Serial.setTimeout(20000L);
}

void loop() {
  // Reset the loop if no new card present on the sensor/reader. This saves the entire process when idle.
  if ( ! mfrc522.PICC_IsNewCardPresent()) {
    return;
  }

  // Select one of the cards
  if ( ! mfrc522.PICC_ReadCardSerial()) {
    return;
  }

  byte buffer[18];
  byte block;
  MFRC522::StatusCode status;
  byte len;

  // Choose block to write to
  SetBlock:
    Serial.println("Input block you want to write to");
    while(!Serial.available()) {}
    block = Serial.parseInt();
    if (block % 4 == 3 || block == 0 || block > 63) {
      Serial.println("Choose a block which does not contain a locked sector");
      Serial.println("This is blocks that do not have a mod 4 equal to 3, block 0, or a block greater than 63");
      goto SetBlock;
    }
   
  // Print block data
  Serial.print("Selected Block: ");
  Serial.print(block);
  Serial.print(" \t| Sector: ");
  Serial.print(block / 4);
  Serial.print(" \t| Sector Block: ");
  Serial.println(block % 4);

  // Collect string to write to block
  Serial.println(F("Type data you want to write, ending with #"));
  
  // Read data from serial
  len = Serial.readBytesUntil('#', (char *) buffer, 16);
  
  // Pad with spaces
  for (byte i = len; i < 16; i++) buffer[i] = ' ';

  // Autheticate with the block
  status = mfrc522.PCD_Authenticate(MFRC522::PICC_CMD_MF_AUTH_KEY_A, block, &key, &(mfrc522.uid));
  if (status != MFRC522::STATUS_OK) {
    Serial.print(F("PCD_Authenticate() failed: "));
    Serial.println(mfrc522.GetStatusCodeName(status));
    goto newCard;
  }
  else Serial.println(F("PCD_Authenticate() success: "));

  // Write to the block
  status = mfrc522.MIFARE_Write(block, buffer, 16);
  if (status != MFRC522::STATUS_OK) {
    Serial.print(F("MIFARE_Write() failed: "));
    Serial.println(mfrc522.GetStatusCodeName(status));
    goto newCard;
  }
  else Serial.println(F("MIFARE_Write() success: "));

  Serial.println("**Write Finished**");
  newCard:
    // If you want to keep writing, comment out this code
    mfrc522.PICC_HaltA();
    mfrc522.PCD_StopCrypto1();
    Serial.println("Ready to write MIFARE PICC"); 
}
