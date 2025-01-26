#include <Wire.h>
#include <RTClib.h>
#include <LiquidCrystal_I2C.h>
#include <DHT.h>

// Initialize RTC, LCD, and DHT
RTC_DS3231 rtc;
LiquidCrystal_I2C lcd(0x27, 16, 2);
#define DHTPIN 2  // Pin where DHT sensor is connected
#define DHTTYPE DHT11 
DHT dht(DHTPIN, DHTTYPE);

void setup() {
  // Initialize Serial Monitor
  Serial.begin(9600);

  // Initialize LCD
  lcd.begin();
  lcd.backlight();

  // Initialize RTC
  if (!rtc.begin()) {
    lcd.print("RTC error!");
    while (1);
  }

  if (rtc.lostPower()) {
    // If RTC lost power, set it to the current time
    rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));
  }

  // Initialize DHT sensor
  dht.begin();
  
  // Display startup message
  lcd.setCursor(0, 0);
  lcd.print("Digital Clock");
  lcd.setCursor(0, 1);
  lcd.print("Initializing...");
  delay(2000);
  lcd.clear();
}

void loop() {
  // Fetch current time from RTC
  DateTime now = rtc.now();

  // Read temperature from DHT sensor
  float temp = dht.readTemperature();
  if (isnan(temp)) {
    temp = 0.0; // Default in case of error
  }

  // Display Time on LCD
  lcd.setCursor(0, 0);
  lcd.print("Time: ");
  lcd.print(now.hour() < 10 ? "0" : "");
  lcd.print(now.hour());
  lcd.print(":");
  lcd.print(now.minute() < 10 ? "0" : "");
  lcd.print(now.minute());
  lcd.print(":");
  lcd.print(now.second() < 10 ? "0" : "");
  lcd.print(now.second());

  // Display Temperature on LCD
  lcd.setCursor(0, 1);
  lcd.print("Temp: ");
  lcd.print(temp);
  lcd.print((char)223); // Degree symbol
  lcd.print("C");

  // Delay for a second
  delay(1000);
}
