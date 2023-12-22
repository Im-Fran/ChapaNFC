#include <SPI.h>
#include <MFRC522.h>
#include <string.h>

void setup() {
  Serial.begin(9600);
  init_rfid_reader();
  Serial.println("Escanea tu tag...");
}

void loop() {
  String id = read_rfid_tag();
  if(id != "") {
    Serial.print("UID del tag: ");
    Serial.println(id);
  }
}