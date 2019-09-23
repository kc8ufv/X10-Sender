// Module to turn any AC device into an X10 controller, so a remote device or lamp can be turned on/off with the device.
// Schematics made with Eagle. 

// This project by Chrissy Hart, KC8UFV


// include X10 library files available at https://github.com/tigoe/x10
#include <x10.h>
                                      // Define pins for functions
const int rxPin = A2;                 // X10 receive pin - required for X10 setup, though X10 reception not implemented in hardware or software in this project. 
const int txPin = A1;                 // X10 transmit pin - Identify the pin to send X10 codes out
const int zcPin = A0;                 // X10 Zero-Crossing pin - Detect the zero crossing of the AC line to line up the transmissions properly
const int swPin = 8;                  // Identify if the switched circuit is turned on
const int House0Pin = 0;              // Set the house code DIP switch pins
const int House1Pin = 1;
const int House2Pin = 2;
const int House3Pin = 3;
const int Dev0Pin = 4;                // Set the Device code DIP switch pins
const int Dev1Pin = 5;
const int Dev2Pin = 6;
const int Dev3Pin = 7;





void setup() {
  x10.begin(rxPin, txPin, zcPin);        // Setup the proper mode for all pins - first the X10 interface
  pinMode(House0Pin, INPUT_PULLUP);      // Next, the DIP switches, using internal pullups. The dip switches pull the signal to ground
  pinMode(House1Pin, INPUT_PULLUP);
  pinMode(House2Pin, INPUT_PULLUP);
  pinMode(House3Pin, INPUT_PULLUP);
  pinMode(Dev0Pin, INPUT_PULLUP);
  pinMode(Dev1Pin, INPUT_PULLUP);
  pinMode(Dev2Pin, INPUT_PULLUP);
  pinMode(Dev3Pin, INPUT_PULLUP);
  pinMode(swPin, INPUT);                  // Finally, a simple input pin for the switched circuit detection. Set up with a 2 resistor voltage divider


}

void loop() {
  // Watch for power to go on, and send command to remote X10 module, and switch to alternative loop:
  if ( digitalRead(swPin) == HIGH) {     // Check if the switch has been turned on. We should be able to safely assume this is true anytime this pin goes high. We assume the switch starts as off, and if not send the ON command on the first loop.
    x10.beginTransmission(HOUSE());      // Read the house code from the DIP switches, and start an X10 packet
    x10.write(DEVICE());                 // Read the device code, and send it
    x10.write(ON);                       // Send the ON command
     
    x10.write(DEVICE());                 // Resend twice to make sure the command goes thru.
    x10.write(ON);
    
    x10.write(DEVICE());
    x10.write(ON);
    delay(500);
    loop2();                             // Go to the alternative loop to watch for power off
  }

}

void loop2() {
  // Watch for switched circuit to go off for several AC cycles, send off command, and return to main loop
  unsigned long TIME;                    // Setup the variables for this routine
  unsigned long TIMER;

do {

  if( digitalRead(swPin) == HIGH ) {      // If power is on, reset the start of the timer
    TIME = millis(); }
  if( TIME > millis() ) {                 // If the clock rolled over since last set, reset it to the current time. This is a failsafe in case the counter's roughly 50 days occours in the brief wait to detect power off. 
    TIME = millis(); }                    //      This may cause a slightly longer delay if the rollover happens durring the delay, but ensures the off command does get sent.
  TIMER = millis() - TIME ;               // Calculate how many milliseconds have elapsed since it was last reset.  One AC cycle is approx 16ms. 


} while ( TIMER < 240 );                  // Make sure we have missed 15 or 16 cycles of the AC, to be sure power is off before sending the command. 

    x10.beginTransmission(HOUSE());       // Read the house code from the DIP switches, and start an X10 packet
    x10.write(DEVICE());                  // Read the device code, and send it
    x10.write(OFF);                       // Send the OFF command
    
    x10.write(DEVICE());                  // Resend twice to make sure the command goes thru.
    x10.write(OFF);
    
    x10.write(DEVICE());
    x10.write(OFF);
    delay(500);
return;                                    // Done with this loop, return to the main loop, and watch for the switch to be turned back on. 
}



byte HOUSE() {                             // Function to read house code
  int COUNTER = 0;
  byte HC = A;
  if ( digitalRead(House0Pin) == LOW ) {   // Read the dip switches, and increment counter if switch is set
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
  switch ( COUNTER ) {                     // Check the value set by the dip switches, and put the bit value in the house code field
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
  return HC;                                 // Return the house code to the calling routine
}


byte DEVICE() {                              // Function to read device code. Works identical to the House code, except the bit patters set in the select case statement
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
