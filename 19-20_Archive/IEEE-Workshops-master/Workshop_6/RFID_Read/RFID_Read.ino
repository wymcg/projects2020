// Read Data
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
  Serial.println("Ready to read MIFARE PICC"); 
  
  // Prepare the key to access data set to FFFFFFFFFFFF at chip delivery
  // A company or user can change this key, usually kept secret on reader side
  // If a false key is provided, the card can not be read
  for (byte i = 0; i < 6; i++) key.keyByte[i] = 0xFF;
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

  // Some variable which will be used to read the cards
  // Create a byte array length for a buffer
  byte len = 18;
  // A byte array to store the hex read from the card for each block
  byte readBuffer[len];
  // A storage for the status code
  MFRC522::StatusCode status;
  
  Serial.println(F("**Card Detected:**"));

  for (byte block = 0; block < 64; block++) {
    // Autheticate the block
    status = mfrc522.PCD_Authenticate(MFRC522::PICC_CMD_MF_AUTH_KEY_A, block, &key, &(mfrc522.uid));
    if (status != MFRC522::STATUS_OK) {
      Serial.print(F("Authentication failed: "));
      Serial.println(mfrc522.GetStatusCodeName(status));
      goto newCard;
    }
    // Read the block
    status = mfrc522.MIFARE_Read(block, readBuffer, &len);
    if (status != MFRC522::STATUS_OK) {
      Serial.print(F("Reading failed: "));
      Serial.println(mfrc522.GetStatusCodeName(status));
      goto newCard;
    }
    printSectorData(block);
    printHex(readBuffer);
    printASCII(readBuffer);
    Serial.println();
  }

  Serial.println("**Read Finished**");
  newCard:
    mfrc522.PICC_HaltA();
    mfrc522.PCD_StopCrypto1();
    Serial.println("Ready to read MIFARE PICC"); 
}

void printSectorData(byte block) {
  // Calculate Sector
  int sector = block / 4;
  // Calculate Block in Sector
  int secBlock = block % 4;
  Serial.print("Block: ");
  Serial.print(block);
  Serial.print("\t | Sector: ");
  Serial.print(sector);
  Serial.print("\t | Sector Block: ");
  Serial.print(secBlock);
  Serial.print("\t | ");
}

void printHex(byte readBuffer[18]) {
  // Print the block in HEX Format
  Serial.print("HEX Data: ");
  for (uint8_t i = 0; i < 16; i++) {
    Serial.print(readBuffer[i] < 16 ? "0" : "");
    Serial.print(readBuffer[i], HEX);
    Serial.print(" ");
  }
  Serial.print(" \t| ");
}

void printASCII(byte readBuffer[18]) {
  // Print the block in ASCII Format
  Serial.print("ASCII Data: ");
  for (uint8_t i = 0; i < 16; i++) {
    if (readBuffer[i] != 10) {
      Serial.write(readBuffer[i]);
    }
  }
}
