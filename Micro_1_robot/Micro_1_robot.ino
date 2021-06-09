#define EN1 6
#define MC1A 10
#define MC2A 11

#define EN2 7
#define MC3A 9
#define MC4A 8

unsigned long myTime = millis();

void setup() {
  Serial.begin(9600);
  pinMode (EN1,   OUTPUT);
  pinMode (EN2,   OUTPUT);
  pinMode (MC1A,  OUTPUT);
  pinMode (MC2A,  OUTPUT);
  pinMode (MC3A,  OUTPUT);
  pinMode (MC4A,  OUTPUT);
  Serial.println("\nSTART OF SKETCH\n");
}

void loop() {
//  track();
test();
}

void test() {
  forward   (3 * 1000);
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
  forward   (4 * 1000);
  right     (2 * 100);
  forward   (1 * 1000);
  right     (2 * 1000);
  forward   (2 * 1000);
  brake     (3 * 1000);
  while (1) {
  }
}

void forward (int x) {
  Serial.println("\nForward");
  myTime = millis();
  Serial.print("Start - "); Serial.println(myTime);
  analogWrite (EN1, 255);
  digitalWrite(MC1A, LOW);
  digitalWrite (MC2A, HIGH);
  analogWrite (EN2, 60);
  digitalWrite(MC3A, LOW);
  digitalWrite (MC4A, HIGH);
  while (myTime + x > millis()) {
    delay(10);
  }
  Serial.print("End - "); Serial.println(millis());
}

void right (int x) {
  Serial.println("\nRight");
  myTime = millis();
  Serial.print("Start - "); Serial.println(myTime);
  analogWrite(EN1, 255);
  digitalWrite(MC1A, LOW);
  digitalWrite(MC2A, HIGH);
  digitalWrite(EN2, LOW);
  digitalWrite(MC3A, LOW);
  digitalWrite(MC4A, HIGH);
  while (myTime + x > millis()) {
    delay(10);
  }
  Serial.print("End - "); Serial.println(millis());
}

void left (int x) {
  Serial.println("\nLeft");
  myTime = millis();
  Serial.print("Start - "); Serial.println(myTime);
  digitalWrite(EN1, LOW);
  digitalWrite(MC1A, LOW);
  digitalWrite(MC2A, HIGH);
  analogWrite(EN2, 255);
  digitalWrite(MC3A, LOW);
  digitalWrite(MC4A, HIGH);
  while (myTime + x > millis()) {
    delay(10);
  }
  Serial.print("End - "); Serial.println(millis());
}

void brake (int x) {
  Serial.println("\nStop");
  myTime = millis();
  Serial.print("Start - "); Serial.println(myTime);
  while (myTime + x > millis()) {
    digitalWrite(EN1, LOW);
    digitalWrite(EN2, LOW);
  }
  Serial.print("End - "); Serial.println(millis());
}
