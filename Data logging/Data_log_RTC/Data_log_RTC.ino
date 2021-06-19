//SD read and write with RTC

#include <SD.h> //For talking to SD Card
#include <Wire.h> //For RTC
#include <RTClib.h> //For RTC

//Define pins
//SD card is on standard SPI pins
//RTC is on Standard I2C Pins
const int CS_PIN = 4;
const int RTC_POW_PIN = A3;
const int RTC_GND_PIN = A2;

String baseString = "Hello There! ";

//Default rate of 1 second
int refresh_rate = 1000;

//Define an RTC object
RTC_DS1307 RTC;

File dataFile;

//Initialize strings
String year, month, day, hour, minute, second, time, date;

void setup() {
  Serial.begin(9600);

  //CS pin, and pwr/gnd pins are outputs
  pinMode(CS_PIN, OUTPUT);
  pinMode(RTC_POW_PIN, OUTPUT);
  pinMode(RTC_GND_PIN, OUTPUT);

  //Setup power and ground pins for both modules
  digitalWrite(RTC_POW_PIN, HIGH);
  digitalWrite(RTC_GND_PIN, LOW);

  //Initialize SD card
  Serial.print(F("Initializing Card - "));
  if (!SD.begin(CS_PIN)) {
    Serial.println(F("Card Failure!"));
    return;
  }

  //Initiate the I2C bus and the RTC library
  Wire.begin();
  RTC.begin();

  Serial.println(F("Card Ready!"));
  //If RTC is not running, set it to the computer's compile time
  if (! RTC.isrunning()) {
    Serial.println(F("RTC is NOT running!"));
    RTC.adjust(DateTime(__DATE__, __TIME__));
  }

}

void loop() {
  if (SD.exists("log.csv")) {
    Serial.println("\nlog.csv exists, deleting and recreating");
    SD.remove("log.csv");
    delay(500);
  } else {
    Serial.println("\nlog.csv doesn't exist, creating now");
  }

  //Write column headers
  dataFile = SD.open("log.csv", FILE_WRITE);
  if (dataFile) {
    dataFile.println(F("\nNew Log Started!"));
    dataFile.println(F("\nDate\t\tTime\t \tPhrase"));
    dataFile.close(); //Data isn't actually written until we close the connection!

    //Print same thing to the screen for debugging
    Serial.println(F("\nNew Log Started!"));
    Serial.println(F("\nDate\t\tTime\t \tPhrase"));
  } else {
    Serial.println(F("Couldn't open log file"));
  }


  for ( int x = 1; x <= 10; x++ ) {

    //Get the current date and time info and store in strings
    DateTime datetime = RTC.now();
    year = String(datetime.year(), DEC);
    month = String(datetime.month(), DEC);
    day = String(datetime.day(), DEC);
    hour = String(datetime.hour(), DEC);
    minute = String(datetime.minute(), DEC);
    second = String(datetime.second(), DEC);

    //Concatenate the strings into date and time
    date = year + "/" + month + "/" + day;
    time = hour + ":" + minute + ":" + second;

    String dataString = baseString + x ;

    //Open a file and write to it.
    dataFile = SD.open("log.csv", FILE_WRITE);
    if (dataFile) {
      dataFile.print(date);
      dataFile.print(F("\t"));
      dataFile.print(time);
      dataFile.print(F(" \t"));
      dataFile.println(dataString);
      dataFile.close(); //Data isn't actually written until we close the connection!

      //Print same thing to the screen for debugging
      Serial.print(date);
      Serial.print(F("\t"));
      Serial.print(time);
      Serial.print(F(" \t"));
      Serial.println(dataString);
    } else {
      Serial.println(F("Couldn't open log file"));
      break;
    }
    delay(refresh_rate);
  }

  if (SD.exists("log.csv")) {
    Serial.println("\nReading log.csv contents\n\n************\n");
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
