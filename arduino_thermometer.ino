#include <Adafruit_MAX31865.h>
Adafruit_MAX31865 thermo = Adafruit_MAX31865(10, 11, 12, 13);
#define RREF      430.0
#define RNOMINAL  100.0
void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  thermo.begin(MAX31865_2WIRE);
}

void loop() {
  // put your main code here, to run repeatedly:
  while (!Serial.available());
  String message =  Serial.readStringUntil('\n');
  if(message == "KDEG?"){
    Serial.println(thermo.temperature(RNOMINAL, RREF) + 273.15);
  }
  else if(message == "CDEG?"){
    Serial.println(thermo.temperature(RNOMINAL, RREF));
  }
  else if(message == "FDEG?"){
    Serial.println(thermo.temperature(RNOMINAL, RREF)* 1.8 + 32);
  }
  else if(message == "RES?"){
    uint16_t rtd = thermo.readRTD();
    float ratio = rtd;
    ratio /= 32768;
    Serial.println(RREF*ratio,8);
  }
  else if(message == "*IDN?"){
    Serial.println("Arduino thermometer");
  }
}