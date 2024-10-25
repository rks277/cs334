#include <WiFi.h>

const char* ssid = "yale wireless";  // Replace with your Wi-Fi network name
const char* password = "";  // Replace with your Wi-Fi network password

WiFiServer server(80);  // Start a server on port 80

int photoresistorPin = 34;  // Analog pin for photoresistor
int touchPin = 4;

unsigned long lastSeasonChange = 0;  // Time tracking for season changes
int season = 0;  // Current season: 0 = Spring, 1 = Summer, 2 = Fall, 3 = Winter
const int seasonDuration = 20000;  // Duration of each season in milliseconds (20 seconds)

void setup() {
  Serial.begin(115200);
  pinMode(photoresistorPin, INPUT);
  pinMode(touchPin, INPUT);

  // Connect to Wi-Fi
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to Wi-Fi...");
  }
  
  Serial.println("Connected to Wi-Fi");
  server.begin();  // Start the server
  Serial.print("Server started at: ");
  Serial.println(WiFi.localIP());  // Show the IP address
}

void loop() {
  WiFiClient client = server.available();  // Listen for incoming clients

  // Change season every 20 seconds
  unsigned long currentMillis = millis();
  if (currentMillis - lastSeasonChange >= seasonDuration) {
    season = (season + 1) % 4;  // Cycle through seasons (0 to 3)
    lastSeasonChange = currentMillis;
    Serial.println("Season changed to: " + String(season));
  }

  if (client) {
    Serial.println("Client connected");

    // Read sensor values
    String photoresistorValue = String(analogRead(photoresistorPin));  // Read photoresistor value
    String touchValue = String(touchRead(touchPin));  // Read touch value

    // Send sensor data and season value
    client.println(photoresistorValue + " | " + touchValue + " | " + String(season));  // Send sensor data and season as integer
    client.stop();  // Close the connection
    delay(100);  // Delay between readings
  }
}
