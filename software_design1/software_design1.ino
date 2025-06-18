

}
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <DHT.h>

// OLED display configuration
#define SCREEN_WIDTH 128 // OLED display width in pixels
#define SCREEN_HEIGHT 64 // OLED display height in pixels
#define OLED_RESET    -1 // Reset pin (use -1 if sharing Arduino reset pin)
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

// DHT sensor configuration
#define DHTPIN 2       // Digital pin connected to the DHT sensor data line
#define DHTTYPE DHT11  // DHT 11 sensor
DHT dht(DHTPIN, DHTTYPE);

// MQ‑135 sensor configuration
#define MQ135_PIN A0   // Analog pin for the MQ‑135 sensor

// Function to evaluate air quality based on the raw sensor value
String getAirQualityCondition(int sensorValue) {
  // These thresholds are examples; calibrate as needed for your environment:
  if (sensorValue < 150)
    return "Fresh Air";
  else if (sensorValue < 300)
    return "Normal";
  else if (sensorValue < 500)
    return "Moderate";
  else if (sensorValue < 700)
    return "Poor";
  else
    return "Hazardous";
}

void setup() {
  // Initialize serial communication for debugging
  Serial.begin(9600);
  
  // Initialize the DHT sensor
  dht.begin();
  
  // Initialize the OLED display
  if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) { // 0x3C is the I2C address for many 128x64 OLED displays
    Serial.println(F("SSD1306 allocation failed"));
    for (;;);  // Infinite loop if display fails to initialize
  }
  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(SSD1306_WHITE);
  
  // Display an intro message
  display.setCursor(0, 0);
  display.println(F("Air Quality Monitor"));
  display.println(F("-------------------"));
  display.display();
  delay(2000);
  display.clearDisplay();
}

void loop() {
  // Read temperature and humidity
  float temperature = dht.readTemperature();
  float humidity = dht.readHumidity();

  // Read the raw value from the MQ‑135 sensor
  int mq135Value = analogRead(MQ135_PIN);

  // Check if DHT sensor readings failed
  if (isnan(temperature) || isnan(humidity)) {
    Serial.println(F("Failed to read from DHT sensor!"));
    return;
  }

  // Output readings to Serial Monitor
  Serial.print("Temperature: ");
  Serial.print(temperature);
  Serial.print(" °C, Humidity: ");
  Serial.print(humidity);
  Serial.print(" %, Air Quality (raw): ");
  Serial.println(mq135Value);

  // Convert the raw air quality value into a descriptive status
  String qualityCondition = getAirQualityCondition(mq135Value);

  // Display the data on the OLED screen
  display.clearDisplay();
  display.setCursor(0, 0);
  display.println(F("Air Quality Monitor"));
  display.println(F("-------------------"));
  
  display.print(F("Temp: "));
  display.print(temperature);
  display.println(F(" °C"));
  
  display.print(F("Humidity: "));
  display.print(humidity);
  display.println(F(" %"));
  
  display.print(F("Air Quality: "));
  display.println(qualityCondition);
  
  display.print(F("Raw: "));
  display.println(mq135Value);
  
  display.display();

  delay(2000);  // Update every 2 seconds
}

