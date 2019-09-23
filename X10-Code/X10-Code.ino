// include X10 library files
#include <x10.h>

const int rxPin = A2; 
const int txPin = A1;
const int zcPin = A0;
const int swPin = 8;
const int House0Pin = 0;
const int House1Pin = 1;
const int House2Pin = 2;
const int House3Pin = 3;
const int Dev0Pin = 4;
const int Dev1Pin = 5;
const int Dev2Pin = 6;
const int Dev3Pin = 7;





void setup() {
  // put your setup code here, to run once:
  x10.begin(rxPin, txPin, zcPin);
  pinMode(House0Pin, INPUT_PULLUP);
  pinMode(House1Pin, INPUT_PULLUP);
  pinMode(House2Pin, INPUT_PULLUP);
  pinMode(House3Pin, INPUT_PULLUP);
  pinMode(Dev0Pin, INPUT_PULLUP);
  pinMode(Dev1Pin, INPUT_PULLUP);
  pinMode(Dev2Pin, INPUT_PULLUP);
  pinMode(Dev3Pin, INPUT_PULLUP);
  pinMode(swPin, INPUT);


}

void loop() {
  // Watch for power to go on, and send command to air compressor, and switch to alternative loop:
  if ( digitalRead(swPin) == HIGH) {
    x10.beginTransmission(HOUSE());
    x10.write(DEVICE());
    x10.write(ON);
    delay(500);
    x10.write(DEVICE());
    x10.write(ON);
    delay(500);
    x10.write(DEVICE());
    x10.write(ON);
    delay(500);
    loop2();
  }

}

void loop2() {
  // Watch for power to go off for more than a second, send off command, and return to main loop
  unsigned long TIME;
  unsigned long TIMER;

do {

  if( digitalRead(swPin) == HIGH ) {
    TIME = millis(); }
  if( TIME > millis() ) {
    TIME = millis(); }
  TIMER = millis() - TIME ;


} while ( TIMER < 120 );
    x10.beginTransmission(HOUSE());
    x10.write(DEVICE());
    x10.write(OFF);
    delay(500);
    x10.write(DEVICE());
    x10.write(OFF);
    delay(500);
    x10.write(DEVICE());
    x10.write(OFF);
    delay(500);
return;
}



byte HOUSE() {
  int COUNTER = 0;
  byte HC = A;
  if ( digitalRead(House0Pin) == LOW ) {
     COUNTER = COUNTER + 1;
  }
  if ( digitalRead(House1Pin) == LOW ) {
     COUNTER = COUNTER + 2;
  }
  if ( digitalRead(House2Pin) == LOW ) {
     COUNTER = COUNTER + 4;
  }
  if ( digitalRead(House3Pin) == LOW ) {
     COUNTER = COUNTER + 8;
  }
  switch ( COUNTER ) {
    case 0:
      HC = A;
      break ;
    case 1:
      HC = B;
      break ;
    case 2:
      HC = C;
      break ;
    case 3:
      HC = D;
      break ;
    case 4:
      HC = E;
      break ;
    case 5:
      HC = F;
      break ;
    case 6:
      HC = G;
      break ;
    case 7:
      HC = H;
      break ;
    case 8:
      HC = I;
      break ;
    case 9:
      HC = J;
      break ;
    case 10:
      HC = K;
      break ;
    case 11:
      HC = L;
      break ;
    case 12:
      HC = M;
      break ;
    case 13:
      HC = N;
      break ;
    case 14:
      HC = O;
      break ;
    case 15:
      HC = P;
      break;
   }
  return HC;  
}


byte DEVICE() {
  int COUNTER = 0;
  byte HC = UNIT_3;
  if ( digitalRead(Dev0Pin) == LOW ) {
     COUNTER = COUNTER + 1;
  }
  if ( digitalRead(Dev1Pin) == LOW ) {
     COUNTER = COUNTER + 2;
  }
  if ( digitalRead(Dev2Pin) == LOW ) {
     COUNTER = COUNTER + 4;
  }
  if ( digitalRead(Dev3Pin) == LOW ) {
     COUNTER = COUNTER + 8;
  }
  switch ( COUNTER )  {
    case 0:
      HC = UNIT_1;
      break ;
    case 1:
      HC = UNIT_2;
      break ;
    case 2:
      HC = UNIT_3;
      break ;
    case 3:
      HC = UNIT_4;
      break ;
    case 4:
      HC = UNIT_5;
      break ;
    case 5:
      HC = UNIT_6;
      break ;
    case 6:
      HC = UNIT_7;
      break ;
    case 7:
      HC = UNIT_8;
      break ;
    case 8:
      HC = UNIT_9;
      break ;
    case 9:
      HC = UNIT_10;
      break ;
    case 10:
      HC = UNIT_11;
      break ;
    case 11:
      HC = UNIT_12;
      break ;
    case 12:
      HC = UNIT_13;
      break ;
    case 13:
      HC = UNIT_14;
      break ;
    case 14:
      HC = UNIT_15;
      break ;
    case 15:
      HC = UNIT_16;
      break;
   }
  return HC;  
}
