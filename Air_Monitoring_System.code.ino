#include <DHT.h>
#include <LiquidCrystal.h>

// DHT11 setup
#define DHTPIN 2        // DHT11 DATA → Arduino pin 2
#define DHTTYPE DHT11
DHT dht(DHTPIN, DHTTYPE);

// LCD pin mapping
// RS, E, D4, D5, D6, D7
LiquidCrystal lcd(7, 6, 5, 4, 3, 2);  // Matches your wiring

void setup() {
  lcd.begin(16, 2);      // LCD columns & rows
  dht.begin();           // Start DHT11
  lcd.print("Air Monitoring");
  delay(2000);
  lcd.clear();
}

void loop() {
  float temp = dht.readTemperature();      // Celsius
  float humid = dht.readHumidity();

  if (isnan(temp) || isnan(humid)) {
    lcd.setCursor(0, 0);
    lcd.print("Sensor error");
  } else {
    lcd.setCursor(0, 0);
    lcd.print("Temp: ");
    lcd.print(temp);
    lcd.print("C");

    lcd.setCursor(0, 1);
    lcd.print("Humid: ");
    lcd.print(humid);
    lcd.print("%");
  }

  delay(2000);  // Update every 2 sec
}
