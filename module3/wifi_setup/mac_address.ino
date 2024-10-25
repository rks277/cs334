// Copied from 334 course notes

/* 
It sometimes amazes me how much broken code is on the internet. I wish I hadn't written so much of it.
-sage
*/

#include "esp_mac.h"
uint8_t baseMac[6];

void setup() {
  Serial.begin(9600);
  // Get MAC address of the WiFi station interface
  esp_read_mac(baseMac, ESP_MAC_WIFI_STA);
}
void loop() {
  Serial.print("Station MAC: ");
  for (int i = 0; i < 5; i++) {
    Serial.printf("%02X:", baseMac[i]);
  }
  Serial.printf("%02X\n", baseMac[5]);
  delay(1000);
}