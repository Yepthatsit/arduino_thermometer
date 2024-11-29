#include <Adafruit_MAX31865.h>
#include <LiquidCrystal_I2C.h>
Adafruit_MAX31865 thermo = Adafruit_MAX31865(10, 11, 12, 13);
LiquidCrystal_I2C lcd(0x27,16,2);
#define RREF      430.0
#define RNOMINAL  100.0
void setup() {
  // put your setup code here, to run once:
 
  Serial.begin(115200);
  thermo.begin(MAX31865_2WIRE);
  lcd.init();
  lcd.backlight();
  lcd.setCursor(0,0);
  lcd.print("Arduino Thermometer");
}

void loop() {
  // put your main code here, to run repeatedly:
  while (!Serial.available());
  String message =  Serial.readStringUntil('\n');
  if(message == "KDEG?"){
    lcd.clear();
    lcd.setCursor(0,0);
    float measured_value = thermo.temperature(RNOMINAL, RREF) + 273.15;
    lcd.print(measured_value);
    lcd.print(" K");
    Serial.println(measured_value);
  }
  else if(message == "CDEG?"){
    lcd.clear();
    lcd.setCursor(0,0);
    float measured_value = thermo.temperature(RNOMINAL, RREF);
    lcd.print(measured_value);
    lcd.print(" C");
    Serial.println(measured_value);
  }
  else if(message == "FDEG?"){
    lcd.clear();
    lcd.setCursor(0,0);
    float measured_value = thermo.temperature(RNOMINAL, RREF)* 1.8 + 32;
    lcd.print(measured_value);
    lcd.print(" F");
    Serial.println(measured_value);
  }
  else if(message == "RES?"){
    uint16_t rtd = thermo.readRTD();
    float ratio = rtd;
    ratio /= 32768;
    float measured_value = RREF*ratio;
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print(measured_value);
    lcd.print(" Ohm");
    Serial.println(measured_value);
  }
  else if(message == "*IDN?"){
    Serial.println("Arduino thermometer");
  }
}