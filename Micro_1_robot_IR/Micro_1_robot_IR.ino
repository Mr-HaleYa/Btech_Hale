#define EN1 6
#define MC1A 10
#define MC2A 11

#define EN2 7
#define MC3A 9
#define MC4A 8

#define IRM 0
#define IRL 1
#define IRR 2

int distM = 0, distL = 0, distR = 0;
unsigned long myTime = millis();
bool M = false;
bool L = false;
bool R = false;


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
  distM = getDistance(IRM);
  if (distM > 350) {
    return true;
  } else {
    return false;
  }
}

bool checkLeft() {
  distL = getDistance(IRL);
  if (distL > 600) {
    return true;
  } else {
    return false;
  }
}

bool checkRight() {
  distR = getDistance(IRR);
  if (distR > 600) {
    return true;
  } else {
    return false;
  }
}

int getDistance( int x ) {
  Serial.println("\n");
  Serial.println(x);
  int dist = 0;
  for (int y = 10; y > 0; y--) {
    delay(10);
    dist = dist + analogRead(x);
    Serial.println(dist);
  }
  dist = dist / 10 ;
  Serial.println(dist);
  return dist;
}

//void loop() {
//  if (checkMain()) {  // if somthing is to close
//    distL = getDistance(IRL);
//    distR = getDistance(IRR);
//    if (distL > distR) {
//      Serial.println("left 1");
//      goForward(10, 128, 0);  // go left
//    } else {
//      Serial.println("right 1");
//      goForward(10, 0, 128);  // go right
//    }
//  } else {
//    if (checkRight()) {
//      Serial.println("left 2");
//      goForward(10, 255, 128);  // go left
//    } else if (checkLeft()) {
//      Serial.println("right 2");
//      goForward(10, 128, 255);  // go right
//    } else {
//      Serial.println("straight 2");
//      goForward(10, 255, 255);  // straight
//    }
//  }
//  delay(1000);
//}

void loop() {
  M = checkMain();
  L = checkLeft();
  R = checkRight();
  if ( M ) {
    if ( L && R ) {
      Serial.println("back 1");
      goBack(10 , 128 , 128);
    } else if ( L ) {
      Serial.println("right 1");
      goForward(10, 0, 128);  // go right
    } else if ( R ) {
      Serial.println("left 1");
      goForward(10, 128, 0);  // go left
    }
  } else if ( L || R ) {
    if ( L ) {
      Serial.println("right 2");
      goForward(10, 128, 255);  // go right
    } else if ( R ) {
      Serial.println("left 2");
      goForward(10, 255, 128);  // go left
    }
  } else {
    Serial.println("straight 1");
    goForward(10, 255, 255);  // straight
  }
  delay(1000);
}

void goForward (int x, int y, int z) {    //time to move, left speed, right speed
  myTime = millis();
  while (myTime + x > millis()) {
    analogWrite (EN1, y);
    digitalWrite(MC1A, LOW);
    digitalWrite (MC2A, HIGH);
    analogWrite (EN2, z);
    digitalWrite(MC3A, LOW);
    digitalWrite (MC4A, HIGH);
  }
}


void goBack (int x, int y, int z) {    //time to move, left speed, right speed
  myTime = millis();
  while (myTime + x > millis()) {
    analogWrite (EN1, y);
    digitalWrite(MC1A, HIGH);
    digitalWrite (MC2A, LOW);
    analogWrite (EN2, z);
    digitalWrite(MC3A, HIGH);
    digitalWrite (MC4A, LOW);
  }
}

