#define EN1 6
#define MC1A 10
#define MC2A 11

#define EN2 7
#define MC3A 9
#define MC4A 8

#define IRM 0
#define IRL 1
#define IRR 2

int distM, distL, distR;
unsigned long myTime = millis();

void setup() {
  Serial.begin(9600);
  pinMode (EN1,   OUTPUT);
  pinMode (EN2,   OUTPUT);
  pinMode (MC1A,  OUTPUT);
  pinMode (MC2A,  OUTPUT);
  pinMode (MC3A,  OUTPUT);
  pinMode (MC4A,  OUTPUT);

}

bool checkMain() {
  distM = analogRead(IRM);
  if (distM > 600) {
    return true;
  } else {
    return false;
  }
}


void loop() {
  if (checkMain()) {  // if somthing is to close
    distL = analogRead(IRL);
    distR = analogRead(IRR);
    if (distL > distR) {
      goForward(10, 128, 0);  // go left
    } else {
      goForward(10, 0, 128);  // go right
    }
  } else {
    goForward(10, 255, 255);  // straight
  }
  Serial.println(analogRead(IRM));
}


void goForward (int x, int y, int z) {    //time to move, left speed, right speed
  Serial.println("\nForward");
  myTime = millis();
  Serial.print("Start - "); Serial.println(myTime);
  while (myTime + x > millis()) {
    analogWrite (EN1, y);
    digitalWrite(MC1A, LOW);
    digitalWrite (MC2A, HIGH);
    analogWrite (EN2, z);
    digitalWrite(MC3A, LOW);
    digitalWrite (MC4A, HIGH);
  }
  Serial.print("End - "); Serial.println(millis());
}
