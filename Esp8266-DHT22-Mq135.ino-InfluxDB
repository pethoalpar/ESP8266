#if defined(ESP32)
#include <WiFiMulti.h>
WiFiMulti wifiMulti;
#define DEVICE "ESP32"
#elif defined(ESP8266)
#include <ESP8266WiFiMulti.h>
ESP8266WiFiMulti wifiMulti;
#define DEVICE "ESP8266BEDROOM"
#endif

#include <InfluxDbClient.h>

#define WIFI_SSID "proton"
#define WIFI_PASSWORD "0736335649"
#define INFLUXDB_URL "http://192.168.100.91:8086"
#define INFLUXDB_DB_NAME "bedroom"

InfluxDBClient client(INFLUXDB_URL, INFLUXDB_DB_NAME);

Point sensor("bedroom");

#include <DHT.h>

#define DHTPIN 14     // D5
#define DHTTYPE DHT22   // there are multiple kinds of DHT sensors

DHT dht(DHTPIN, DHTTYPE);

double air_quality;

void setup() {

  Serial.begin(9600);
  Serial.setTimeout(2000);

  // Wait for serial to initialize.
  while (!Serial) { }
  dht.begin();

  // Connect WiFi
  Serial.println("Connecting to WiFi");
  WiFi.mode(WIFI_STA);
  wifiMulti.addAP(WIFI_SSID, WIFI_PASSWORD);
  while (wifiMulti.run() != WL_CONNECTED) {
    Serial.print(".");
    delay(500);
  }

  // Add constant tags - only once
  sensor.addTag("device", DEVICE);

  // Check server connection
  if (client.validateConnection()) {
    Serial.print("Connected to InfluxDB: ");
  } else {
    Serial.println(client.getLastErrorMessage());
  }
}

void loop() {

  float h = dht.readHumidity();
  float t = dht.readTemperature();

  if (isnan(h) || isnan(t)) {
    delay(2000);
    return;
  } else {

    air_quality = ((analogRead(A0) / 1024.0) * 100.0);

    // Store measured value into point
    sensor.clearFields();
    // Report RSSI of currently connected network
    sensor.addField("temp", t);
    sensor.addField("humidity", h);
    sensor.addField("air_quality", air_quality);
    // Write point
    if (!client.writePoint(sensor)) {
      Serial.print("InfluxDB write failed: ");
    }

    delay(300000);
  }

}
