#define EN1 6
#define MC1A 10
#define MC2A 12

#define EN2 7
#define MC3A 9
#define MC4A 8

#define IRL A0
#define IRR A1
#define IRM A2

#define BL 3
#define BR 2
#define FR 4
#define FL 5

bool BLB = false;
bool BRB = false;
bool FRB = false;
bool FLB = false;
unsigned long myTime = millis();

void setup() {
  Serial.begin(9600);
  pinMode (EN1,   OUTPUT);
  pinMode (EN2,   OUTPUT);
  pinMode (MC1A,  OUTPUT);
  pinMode (MC2A,  OUTPUT);
  pinMode (MC3A,  OUTPUT);
  pinMode (MC4A,  OUTPUT);
  pinMode (FL,    INPUT_PULLUP);
  pinMode (FR,    INPUT_PULLUP);
  pinMode (BL,    INPUT_PULLUP);
  pinMode (BR,    INPUT_PULLUP);
  Serial.println("\nSTART OF SKETCH\n");
}

void loop() {
  //track();
  autoNav();
  //test();
}

void test() {
  forward ( 5 * 1000 );
  back    ( 5 * 1000 );
  brake   ( 100 * 1000 );
}

void autoNav() {
  int distL = analogRead( IRL );
  int distR = analogRead( IRR );
  FRB = !digitalRead( FR );
  FLB = !digitalRead( FL );
  BLB = !digitalRead( BL );
  BRB = !digitalRead( BR );
  if (distL > 610 || distR > 610 || BLB || BRB || FRB || FLB ) {
    if ( FRB && FLB ) {
      back ( 1 * 100 );
    } else if ( FRB || FLB ) {
      if ( FLB ) {
        sharpRight (1 * 100);
      } else {
        sharpLeft (1 * 100);
      }
    } else {
      if (distL > 610 || BLB ) {
        right (1 * 100);
      } else if ( distR > 610 || BRB ) {
        left (1 * 100);
      }
    }
  } else {
    forward   (2 * 100);
  }
}



void track() {
  forward   (1.5 * 1000);
  left      (1.5 * 100);
  forward   (1 * 1000);
  left      (1 * 100);
  forward   (0.3 * 1000);


  left      (7 * 100);


  forward   (0.6 * 1000);


  left      (7 * 100);


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

void forward1 (int x) {
  int L = 0;
  int R = 0;
  int MSL = 0;
  int MSR = 0;
  Serial.println("\nForward");
  myTime = millis();
  Serial.print("Start - "); Serial.println(myTime);
  while (myTime + x > millis()) {
    L = analogRead( IRL );
    R = analogRead( IRR );
    MSL = map( L, 800 , 400 , 0, 255 );
    Serial.println(MSL);
    MSR = map( R, 800 , 400 , 0, 255 );
    analogWrite (EN1, MSR);   // LEFT MOTOR
    digitalWrite(MC1A, LOW);
    digitalWrite (MC2A, HIGH);
    analogWrite (EN2, MSL);   // RIGHT MOTOR
    digitalWrite(MC3A, LOW);
    digitalWrite (MC4A, HIGH);
  }
  Serial.print("End - "); Serial.println(millis());
}


/*------------------------------------------------------*/

void forward (int x) {
  Serial.println("\nForward");
  myTime = millis();
  Serial.print("Start - "); Serial.println(myTime);

  shift();

  digitalWrite  (MC1A, LOW);
  digitalWrite  (MC2A, HIGH);
  analogWrite   (EN1,   255);

  digitalWrite  (MC3A, LOW);
  digitalWrite  (MC4A, HIGH);
  analogWrite   (EN2,  255);

  while (myTime + x > millis()) {
    delay(10);
  }
  Serial.print("End - "); Serial.println(millis());
}



void back (int x) {
  Serial.println("\nBack");
  myTime = millis();
  Serial.print("Start - "); Serial.println(myTime);

  shift();

  digitalWrite  (MC1A, HIGH);
  digitalWrite  (MC2A, LOW);
  analogWrite   (EN1, 255);

  digitalWrite  (MC3A, HIGH);
  digitalWrite  (MC4A, LOW);
  analogWrite   (EN2, 255);

  while (myTime + x > millis()) {
    delay(10);
  }
  Serial.print("End - "); Serial.println(millis());
}



void right (int x) {
  Serial.println("\nRight");
  myTime = millis();
  Serial.print("Start - "); Serial.println(myTime);

  shift();

  digitalWrite(MC1A, LOW);
  digitalWrite(MC2A, HIGH);
  analogWrite(EN1, 255);

  digitalWrite(MC3A, LOW);
  digitalWrite(MC4A, HIGH);
  digitalWrite(EN2, LOW);

  while (myTime + x > millis()) {
    delay(10);
  }
  Serial.print("End - "); Serial.println(millis());
}



void left (int x) {
  Serial.println("\nLeft");
  myTime = millis();
  Serial.print("Start - "); Serial.println(myTime);

  shift();

  digitalWrite(MC1A, LOW);
  digitalWrite(MC2A, HIGH);
  digitalWrite(EN1, LOW);

  digitalWrite(MC3A, LOW);
  digitalWrite(MC4A, HIGH);
  analogWrite(EN2, 255);

  while (myTime + x > millis()) {
    delay(10);
  }
  Serial.print("End - "); Serial.println(millis());
}



void sharpRight (int x) {
  Serial.println("\nSharp Right");
  myTime = millis();
  Serial.print("Start - "); Serial.println(myTime);

  shift();

  digitalWrite(MC1A, LOW);
  digitalWrite(MC2A, HIGH);
  analogWrite(EN1, 255);

  digitalWrite(MC3A, HIGH);
  digitalWrite(MC4A, LOW);
  analogWrite(EN2, 128);

  while (myTime + x > millis()) {
    delay(10);
  }
  Serial.print("End - "); Serial.println(millis());
}



void sharpLeft (int x) {
  Serial.println("\nSharp Left");
  myTime = millis();
  Serial.print("Start - "); Serial.println(myTime);

  shift();

  digitalWrite(MC1A, HIGH);
  digitalWrite(MC2A, LOW);
  analogWrite(EN1, 255);

  digitalWrite(MC3A, LOW);
  digitalWrite(MC4A, HIGH);
  analogWrite(EN2, 255);

  while (myTime + x > millis()) {
    delay(10);
  }
  Serial.print("End - "); Serial.println(millis());
}



void shift() {
  digitalWrite (MC1A, LOW);
  digitalWrite (MC2A, LOW);
  digitalWrite (EN1,  LOW);
  delay(5);
  digitalWrite (MC3A, LOW);
  digitalWrite (MC4A, LOW);
  digitalWrite (EN2,  LOW);
  delay(5);
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
