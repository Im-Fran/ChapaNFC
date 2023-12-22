#define RST_PIN 9
#define SDA_PIN 10
#define MOSI_PIN 11
#define MISO_PIN 12
#define SCK_PIN 13

MFRC522 mfrc522(SDA_PIN, RST_PIN);  // Crear instancia de MFRC522

String read_rfid_tag() {
  /* Verifica si hay tags para leer. */
  if (!mfrc522.PICC_IsNewCardPresent() || !mfrc522.PICC_ReadCardSerial()) {
    return ""; // Retorna un string vacio si no hay tags.
  }

  /* Seleccionar el tipo de tag. */
  MFRC522::PICC_Type piccType = mfrc522.PICC_GetType(mfrc522.uid.sak);

  /* Valida si es un tag soportado. */
  if (piccType != MFRC522::PICC_TYPE_MIFARE_MINI && piccType != MFRC522::PICC_TYPE_MIFARE_1K && piccType != MFRC522::PICC_TYPE_MIFARE_4K && piccType != MFRC522::PICC_TYPE_MIFARE_UL) {
    return ""; // Retorna un string vacio si no es soportado.
  }

  String uid = "";
  /* Muestra el UID del tag. */
  for (byte i = 0; i < mfrc522.uid.size; i++) {
    if (mfrc522.uid.uidByte[i] < 0x10) {
      uid += "0"; // Agrega un cero inicial si el byte es menor a 0x10
    }
    uid += String(mfrc522.uid.uidByte[i], HEX); // Agrega el byte del UID al string.
  }
  
  mfrc522.PICC_HaltA();       // Detener PICC
  mfrc522.PCD_StopCrypto1();  // Detener encriptacion en PCD
  return uid;
}

void init_rfid_reader()  {
  SPI.begin();          // Inicia bus SPI
  mfrc522.PCD_Init();   // Inicia MFRC522
}
