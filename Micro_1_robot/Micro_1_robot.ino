const int EN1 = 6;
const int MC1A = 10;
const int MC2A = 11;

const int EN2 = 7;
const int MC3A = 9;
const int MC4A = 8;

int val = 0;
int velocity = 0;

unsigned long myTime = millis();

void setup() {
  Serial.begin(9600);
  pinMode (EN1,   OUTPUT);
  pinMode (EN2,   OUTPUT);
  pinMode (MC1A,  OUTPUT);
  pinMode (MC2A,  OUTPUT);
  pinMode (MC3A,  OUTPUT);
  pinMode (MC4A,  OUTPUT);
  brake(3 * 1000);
}

void loop() {
  forward(2 * 1000);
  brake(2 * 1000);
  left(500);
  brake(2 * 1000);
  right(500);
  brake(2 * 1000);
  while (1) {
    delay(10000);
  }
}


void track() {
  forward   (3 * 1000);
  left      (2 * 100);
  forward   (1 * 1000);
  left      (2 * 100);
  forward   (3 * 1000);
  right     (2 * 100);
  forward   (3 * 100);
  right     (2 * 100);
  forward   (2 * 1000);
  right     (2 * 100);
  forward   (6 * 1000);
  right     (2 * 100);
  forward   (1 * 1000);
  right     (2 * 1000);
  forward   (2 * 1000);
  brake     (3 * 1000);
  while (1) {
    delay(10000);
  }
}

void forward (int x) {
  Serial.println("\nForward");
  myTime = millis();
  Serial.print("Start - "); Serial.println(myTime);
  while (myTime + x > millis()) {
    analogWrite (EN1, 128);
    digitalWrite(MC1A, LOW);
    digitalWrite (MC2A, HIGH);
    analogWrite (EN2, 128);
    digitalWrite(MC3A, LOW);
    digitalWrite (MC4A, HIGH);
  }
  Serial.print("End - "); Serial.println(millis());
}

void right (int x) {
  Serial.println("\nRight");
  myTime = millis();
  Serial.print("Start - "); Serial.println(myTime);
  while (myTime + x > millis()) {
    analogWrite(EN1, 255);
    digitalWrite(MC1A, HIGH);
    digitalWrite(MC2A, LOW);
    analogWrite(EN2, 255);
    digitalWrite(MC3A, LOW);
    digitalWrite(MC4A, LOW);
  }
  Serial.print("End - "); Serial.println(millis());
}

void left (int x) {
  Serial.println("\nLeft");
  myTime = millis();
  Serial.print("Start - "); Serial.println(myTime);
  while (myTime + x > millis()) {
    analogWrite(EN1, 255);
    digitalWrite(MC1A, LOW);
    digitalWrite(MC2A, LOW);
    analogWrite(EN2, 255);
    digitalWrite(MC3A, HIGH);
    digitalWrite(MC4A, LOW);
  }
  Serial.print("End - "); Serial.println(millis());
}

void brake (int x) {
  Serial.println("\nStop");
  myTime = millis();
  Serial.print("Start - "); Serial.println(myTime);
  analogWrite (EN1, 255);
  digitalWrite(MC1A, HIGH);
  digitalWrite (MC2A, LOW);
  analogWrite (EN2, 255);
  digitalWrite(MC3A, HIGH);
  digitalWrite (MC4A, LOW);
  delay(50);
  while (myTime + x > millis()) {
    digitalWrite(EN1, LOW);
    digitalWrite(EN2, LOW);
  }
  Serial.print("End - "); Serial.println(millis());
}
