#include <Wire.h>
void i2c_scan(TwoWire i2c);


void setup() {
  Serial.begin(115200);
  Wire.setSDA(8);
  Wire.setSCL(9);
  Wire.begin();
  Wire1.setSDA(6);
  Wire1.setSCL(7);
  Wire1.begin();
}

void loop() {

  Serial.println("\r\nI2C0 Scanning...");
  i2c_scan(Wire);
  Serial.println("\r\nI2C1 Scanning...");
  i2c_scan(Wire1);
  delay(1000);  // wait 5 seconds for the next I2C scan
}


void i2c_scan(TwoWire i2c) {
  byte error, address;  //variable for error and I2C address
  int nDevices;

  nDevices = 0;
  for (address = 0; address < 16; address++) {
    if (address % 16 == 0) {
      Serial.print("    ");
    }
    Serial.print(address, HEX);
    Serial.print("   ");
  }
  Serial.println("");
  for (address = 16; address < 128; address++) {
    // The i2c_scanner uses the return value of
    // the Write.endTransmisstion to see if
    // a device did acknowledge to the address.
    i2c.beginTransmission(address);
    error = i2c.endTransmission();
    if (address % 16 == 0) {
      Serial.print(address / 16);
      Serial.print("   ");
    }
    if (error == 0) {
      Serial.print(address, HEX);
      Serial.print("  ");
      nDevices++;
    } else {
      Serial.print("--  ");
    }
    if (address % 16 == 15) {
      Serial.println("");
    }
  }
}