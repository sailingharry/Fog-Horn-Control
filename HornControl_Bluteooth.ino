// Set up Bluetooth
#include "BluetoothSerial.h"
BluetoothSerial ESP_BT;

// Global Variables
int HornPin = 13;
int LED = 2;
int Command = 0;                   // Bluetooth command.  0=Off, 1=Motor, 2=Sail, 3=Anchor
int ShortBlast = 1000;             // One Second
int ProlongedBlast = 5000;         // Five Seconds
int Space = 1000;                  // One Second
int Interval = 120000;             //120000 is 2 minutes -- set for 30 seconds (30000) for testing
int Rand = random(-15000, 15000);  //Insert +/- 15 seconds randomization on repeat period

void setup() {
  //Setup code here, to run once:

  // define pins
  pinMode(HornPin, OUTPUT);
  pinMode(LED, OUTPUT);

  // Serial and Bluetooth setup
  //Serial.begin(19200);               // Initialize serial port for communication with PC (over USB Cable)
  ESP_BT.begin("Fog_Horn_Control");  // Name of Bluetooth interface
  //Serial.println("Bluetooth ready to pair");
}

void loop() {
  // put your main code here, to run repeatedly:
  if (ESP_BT.available()) {   //Incomming info on BT
    Command = ESP_BT.read();  //Read the info
  }

  switch (Command) {
    case 0:  // Horn off
      Serial.println("OFF");
      break;

      // Motoring horns;
    case 1:
      Serial.println("Motor");
      Horn(ProlongedBlast);
      Rand = random(-15000, 15000);  // add 15 seconds of randomness to spacing of sets
      delay(Interval - ProlongedBlast - Space + Rand);
      break;

    // Sailing horns;
    case 2:
      Serial.println("Sail");
      Horn(ProlongedBlast);
      Horn(ShortBlast);
      Horn(ShortBlast);
      Rand = random(-15000, 15000);  // add 15 seconds of randomness to spacing of sets
      delay(Interval - 3 * Space - 2 * ShortBlast - ProlongedBlast + Rand);
      break;
      // Anchored horns;
    case 3:
      Serial.println("Anchor");
      Horn(ShortBlast);
      Horn(ProlongedBlast);
      Horn(ShortBlast);
      Rand = random(-15000, 15000);  // add 15 seconds of randomness to spacing of sets
      delay(Interval - 3 * Space - 2 * ShortBlast - ProlongedBlast + Rand);
      break;
  }
}
// Subroutines
void Horn(int Length) {         //Sound horn for requested length
  digitalWrite(HornPin, HIGH);  // Turn on horn
  digitalWrite(LED, HIGH);      // Turn on LED
  delay(Length);                // Horn length
  digitalWrite(HornPin, LOW);   //Turn off horn
  digitalWrite(LED, LOW);       // Turn off LED
  delay(Space);                 // Pause for space before next horn
}
