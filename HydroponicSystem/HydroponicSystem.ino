#include <LiquidCrystal_I2C.h>
#include <ArduinoJson.h>
#include <OneWire.h>
#include <DallasTemperature.h>
long temp;
long acid;
const int pinDatosDQ = 9;
OneWire oneWireObject(pinDatosDQ);
DallasTemperature sensorDS18B20(&oneWireObject);
LiquidCrystal_I2C lcd(0x3f,16,2);
void setup() {
  Serial.begin(9600);
  sensorDS18B20.begin();
  lcd.init();
  lcd.backlight();
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("Temperatura");
}
void loop() {
  sensorDS18B20.requestTemperatures();
  delay(1000);
  lcd.setCursor(0,1);
  lcd.print(sensorDS18B20.getTempCByIndex(0));
  lcd.display();
  delay(500);
  temp = (sensorDS18B20.getTempCByIndex(0));
  acid = random(0,6);
  char buf [100];
  snprintf (buf, sizeof(buf),"{\"temp\":%d,\"acid\":%d}",temp,acid);
  Serial.println(buf);
  delay(3500);
}
