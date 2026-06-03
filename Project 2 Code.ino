#include <WiFi.h>
#include <DHT.h>
#include <LiquidCrystal_I2C.h>

#define DHTPIN 4
#define DHTTYPE DHT22

#define CURRENT_SENSOR 34
#define VIBRATION_SENSOR 27

DHT dht(DHTPIN, DHTTYPE);

LiquidCrystal_I2C lcd(0x27,16,2);

const char* ssid = "Your_WiFi_Name";
const char* password = "Your_WiFi_Password";

float temperature;
float humidity;
int currentValue;
int vibrationValue;

void setup()
{
Serial.begin(115200);

dht.begin();

pinMode(VIBRATION_SENSOR, INPUT);

lcd.init();
lcd.backlight();

WiFi.begin(ssid, password);

lcd.clear();
lcd.setCursor(0,0);
lcd.print("Connecting");

while(WiFi.status()!=WL_CONNECTED)
{
delay(500);
Serial.print(".");
}

lcd.clear();
lcd.print("WiFi Connected");
delay(2000);
}

void loop()
{
temperature = dht.readTemperature();
humidity = dht.readHumidity();

currentValue = analogRead(CURRENT_SENSOR);

vibrationValue = digitalRead(VIBRATION_SENSOR);

Serial.println("===========");
Serial.print("Temperature : ");
Serial.println(temperature);

Serial.print("Humidity : ");
Serial.println(humidity);

Serial.print("Current : ");
Serial.println(currentValue);

Serial.print("Vibration : ");
Serial.println(vibrationValue);

lcd.clear();

lcd.setCursor(0,0);
lcd.print("T:");
lcd.print(temperature);
lcd.print(" H:");
lcd.print(humidity);

lcd.setCursor(0,1);
lcd.print("C:");
lcd.print(currentValue);

lcd.print(" V:");
lcd.print(vibrationValue);

if(temperature > 60)
{
Serial.println("ALERT: HIGH TEMPERATURE");
}

if(vibrationValue == HIGH)
{
Serial.println("ALERT: ABNORMAL VIBRATION");
}

delay(2000);
}
