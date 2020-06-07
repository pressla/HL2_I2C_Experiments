// I2C slave sample code
// analog value for external Amp by arduino
// See Schematic: 
#include <Wire.h>

int outpin = 6;  //possible: 3,5,6,9
//SDA pin A4
//SCL pin A5

void setup() {
  Wire.begin(0x20);                // join i2c bus with address #8
  Wire.onReceive(receiveEvent); // register event
  Serial.begin(19200);           // start serial for output
}

void loop() {
  delay(100);
}

// function that executes whenever data is received from master
// this function is registered as an event, see setup()

void receiveEvent(int howMany) {
  while (1 < Wire.available()) { // loop through all but the last
    char c = Wire.read(); // receive byte as a character
    Serial.print(c);         // print the character
  }
  int x = Wire.read();    // receive byte as an integer
  
  Serial.println(x);         // write to usb monitor

  int Band = 0; //80m Band

  switch (x) {
    case 1:     //4MHz
      Band = 0;
      break;
    case 2:     //7Mhz
      Band = 65;
      break;
    case 3:     //14MHz
      Band = 127;
      break;
    case 4:     //21MHz
      Band = 188;
      break;
    case 5:     //30MHz
      Band = 255;
      break;
      
    default:
      Band=255; 
  }
  analogWrite(outpin, Band);
}
