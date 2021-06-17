#include <Servo.h>
#include <LiquidCrystal.h>
#include <Servo.h>
#include <Wire.h>

LiquidCrystal lcd(8, 9, 4, 5, 6, 7);

Servo myservo;

//Custom degree character
byte degree[8] = {
  B00110,
  B01001,
  B01001,
  B00110,
  B00000,
  B00000,
  B00000,
  B00000,
};

//Custom "Fan On" indicator
byte fan_on[8] = {
  B00100,
  B10101,
  B01110,
  B11111,
  B01110,
  B10101,
  B00100,
  B00000,
};

//Custom "Fan Off" indicator
byte fan_off[8] = {
  B00100,
  B00100,
  B00100,
  B11111,
  B00100,
  B00100,
  B00100,
  B00000,
};

//Pin Connections
const int FAN = 22;
const int LIGHT = 23;
const int DOWN_BUTTON = 24;
const int UP_BUTTON = 26;
const int TEMP = A7;
const int SERVO = 12;
const int temp_address = 72;

//Variables for debouncing
bool lastDownTempButton = LOW;
bool currentDownTempButton = LOW;
bool lastUpTempButton = LOW;
bool currentUpTempButton = LOW;
bool tempBuffer = false;
bool low_latch = false;
bool high_latch = false;

long int Time = millis();

int set_temp = 28; //The Default desired temperature
int c = set_temp;

void setup() {
  Serial.begin(9600);
  Serial.println("\n");
  Wire.begin();
  pinMode(FAN, OUTPUT);
  pinMode(LIGHT, OUTPUT);

  myservo.attach(SERVO);
  myservo.write(145);

  //Set up the LCD's number of columns and rows
  lcd.begin(16, 2);

  //Make custom characters
  lcd.createChar(0, degree);
  lcd.createChar(1, fan_off);
  lcd.createChar(2, fan_on);

  //Print a static message to the LCD
  lcd.setCursor(0, 0);
  lcd.print("Current:");
  lcd.setCursor(10, 0);
  lcd.write((byte)0);
  lcd.setCursor(11, 0);
  lcd.print("C");
  lcd.setCursor(0, 1);
  lcd.print("Set:");
  lcd.setCursor(10, 1);
  lcd.write((byte)0);
  lcd.setCursor(11, 1);
  lcd.print("C");
  lcd.setCursor(15, 1);
  lcd.write(1);
}

//A debouncing function that can be used by multiple buttons
bool debounce(bool last, int pin) {
  bool current = digitalRead(pin);
  if (last != current) {
    delay(5);
    current = digitalRead(pin);
  }
  return current;
}

int tempC() {
  Wire.beginTransmission(temp_address);
  Wire.write(0);
  Wire.endTransmission();

  Wire.requestFrom(temp_address, 1);
  while (Wire.available() == 0);
  return Wire.read();
}

void loop () {
  delay(100);
  if ( tempC() - 5 > c || tempC() + 5 < c ) { // fixes the temp changing when servo activates
    // do nothing
  } else {
    c = tempC();
  }

  lcd.setCursor(8, 0); //Move the cursor
  lcd.print(c); //Print this new value

  currentDownTempButton = debounce(lastDownTempButton, DOWN_BUTTON);
  currentUpTempButton = debounce(lastUpTempButton, UP_BUTTON);

  //Turn down the set temp
  if (lastDownTempButton == LOW && currentDownTempButton == HIGH) {
    set_temp--;
  } else if (lastUpTempButton == LOW && currentUpTempButton == HIGH) {
    set_temp++;
  }
  lastDownTempButton = currentDownTempButton;
  lastUpTempButton = currentUpTempButton;

  //Print the set temp
  lcd.setCursor(8, 1);
  lcd.print(set_temp);

  if ( c <= set_temp - 2 || low_latch ) {           // -2 start heating and go until set_temp is met
    if ( c >= set_temp ) {
      low_latch = false;
      Serial.println("low latch false");
    } else {
      low_latch = true;
      Serial.println("low latch true");
      digitalWrite(LIGHT, HIGH);
      digitalWrite(FAN, LOW);
      myservo.write(145);
    }
  } else if ( c >= set_temp + 2 || high_latch ) {   // +2 start cooling and go until set_temp is met
    if ( c <= set_temp ) {
      high_latch = false;
      Serial.println("high latch false");
    } else {
      high_latch = true;
      Serial.println("high latch true");
      digitalWrite(LIGHT, LOW);
      myservo.write(0);
      if ( millis() - Time >= 3000 ) {
        Serial.println("fan on");
        digitalWrite(FAN, HIGH);
      }
    }
  }

  if ( !low_latch && !high_latch ) {              // -1,0,+1 turn off all heating and cooling because its all good
    Serial.println("temp is good");
    digitalWrite(LIGHT, LOW);
    digitalWrite(FAN, LOW);
    myservo.write(145);
    Time = millis();
  }
}
