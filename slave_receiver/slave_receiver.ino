// I2C slave sample code
// analog value for external Amp by arduino
// See Schematic: 
#include <Wire.h>

int outpin = 6;  //possible: 3,5,6,9
//SDA pin A4
//SCL pin A5

void setup() {
  Wire.begin(0x20);                 // join i2c bus with address to listen
  Wire.onReceive(receiveEvent);     // register event
  Serial.begin(115200);             // start serial for output
  Serial.println("Hello HL2 I2C");
}

void loop() {
  delay(100);
}

// function that executes whenever data is received from master
// this function is registered as an event, see setup()

void receiveEvent(int howMany) {
  //Serial.println(howMany);
  Serial.println("--");
  byte c[10];
  int i= 0;
  while (0 < Wire.available()) { // loop through all but the last
    c[i] = Wire.read(); // receive byte as a character
    i++;
  }
 
  Serial.print("BUS DATA:");
  Serial.println(c[1]);         // write to usb monitor

  int Band = 0; //80m Band

  switch (c[1]) {
    case 0x1:     //2MHz
      Band = 0;
      break;
    case 0x2:     //4Mhz
      Band = 65;
      break;
    case 0x4:     //7MHz
      Band = 127;
      break;
    case 0x8:     //14MHz
      Band = 188;
      break;
    case 0x10:     //21MHz
      Band = 222;
      break;
      
    default:
      Band=255; // equals 4.5V or so
  }
  Serial.print("BAND:");
  Serial.println(Band);         // write to usb monitor

  analogWrite(outpin, Band);    //analog value to amp
}
