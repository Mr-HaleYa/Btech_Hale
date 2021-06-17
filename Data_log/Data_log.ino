//Write to SD card
#include <SPI.h>
#include <SD.h>

//We always need to set the CS Pin to 4
const int CS_PIN = 4;
String baseString = "Hello There! ";
File dataFile;

void setup() {
  digitalWrite (10, HIGH);
  digitalWrite (CS_PIN, LOW);
  Serial.begin(9600);
  while (!Serial) {}
  Serial.print("Initializing Card - ");
  //CS pin is an output
  pinMode(CS_PIN, OUTPUT);

  if (!SD.begin(CS_PIN)) {
    Serial.println("Card Failure!\n");
    return;
  }
  Serial.println("Card Ready\n");
  delay(1000);
}

void loop() {
  if (SD.exists("log.csv")) {
    Serial.println("log.csv exists, deleting and recreating\n");
    SD.remove("log.csv");
    delay(500);
  } else {
    Serial.println("log.csv doesn't exist, creating now\n");
  }
  
  Serial.println("Writing data to log.csv");
  for ( int x = 1; x <= 10; x++ ) {
     String dataString = baseString + x ;
    //Open a file and write to it.
    dataFile = SD.open("log.csv", FILE_WRITE);
    if (dataFile) {
      long timeStamp = millis();
      dataFile.print(timeStamp);
      dataFile.print("\t");
      dataFile.println(dataString);
      dataFile.close(); //Data isn't actually written until we close the connection!

      //Print same thing to the screen for debugging
      Serial.print(timeStamp);
      Serial.print("\t");
      Serial.println(dataString);
    } else {
      Serial.println("Couldn't open log file");
      break;
    }
    delay(1000);
  }
  Serial.println("\nDone writing\n");

  if (SD.exists("log.csv")) {
    Serial.println("Reading log.csv contents\n\n************\n");
    dataFile = SD.open("log.csv");
    if (dataFile) {
      while (dataFile.available()) {
        Serial.write(dataFile.read());
      }
      dataFile.close();
      Serial.println("\n************\n");
    }  else {
      Serial.println("error opening log.csv");
    }
  } else {
    Serial.println("log.csv doesn't exist.");
  }
  while (1) {}
}
