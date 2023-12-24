#define BLYNK_TEMPLATE_ID "TMPL6TlwBwVk5"
#define BLYNK_TEMPLATE_NAME "fire detection"
#define BLYNK_AUTH_TOKEN "BctO5rGEM6gwGNoQchvXOX2yPjQSB3rA"

#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>
#include <DHT.h>

// Add the library for your smog sensor here

char ssid[] = "Sagarmatha";
char password[] = "sagarmatha";

char auth[] = BLYNK_AUTH_TOKEN;

#define DHTPIN D1
#define DHTTYPE DHT11

DHT dht(DHTPIN, DHTTYPE);

// Define the analog pin for the smog sensor
int smogSensorPin = A0; // Change this to your sensor's pin

void setup() {
  Serial.begin(115200);
  WiFi.begin(ssid, password);
  
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.println("Connecting to WiFi...");
  }

  Blynk.begin(auth, ssid, password);
  dht.begin();
}

void loop() {
  float temperature = dht.readTemperature();
  float humidity = dht.readHumidity();

  Serial.print("Temperature: ");
  Serial.print(temperature);
  Serial.print(" C, Humidity: ");
  Serial.print(humidity);
  Serial.println(" %");

  Blynk.virtualWrite(V0, humidity);
  Blynk.virtualWrite(V1, temperature);

  // Read the smog sensor value
  int smogValue = analogRead(smogSensorPin);
  Serial.print("Smog Value: ");
  Serial.println(smogValue);

  // Send smog value to Blynk
  Blynk.virtualWrite(V2, smogValue); // Change V2 to the desired virtual pin
   if(temperature > 25 )
  {
    Serial.println("Fire in the forest ");
    // Blynk.email("ravi.prince.7374@gmail.com","fire_detected");
    Blynk.logEvent("fire_alert","Fire Detected ");
  }
  delay(1000);
}