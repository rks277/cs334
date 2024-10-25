// Copied from the linked tutorial below

/*
*  ESP32 WiFi Scanner Example. Examples > WiFi > WiFiScan
*  Full Tutorial @ https://deepbluembedded.com/esp32-wifi-library-examples-tutorial-arduino/
*/

/*
    Output in AKW: 
    Message (Enter to send message to 'ESP32 Dev Module' on '/dev/cu.usbserial-10')
    115200 baud
    14:21:26.145 -> 14 | YaleGuest                        |  -86 | 11 | open
    14:21:26.145 -> 15 | YaleSecure                       |  -87 | 11 | WPA2-EAP
    14:21:26.178 -> 16 | eduroam                          |  -88 | 11 | WPA2-EAP
    14:21:26.178 -> 17 | yale wireless                    |  -88 | 11 | open
    14:21:26.178 -> 18 | IQR Lab                          |  -89 |  8 | WPA2
    14:21:26.178 -> 19 | EBD224C1-EE81fIqYJ11AO6o         |  -89 | 11 | WPA2
    14:21:26.210 -> 20 | yale wireless                    |  -90 | 11 | open
    14:21:26.210 -> 21 | YaleSecure                       |  -91 | 11 | WPA2-EAP
    14:21:26.210 -> 22 | eduroam                          |  -92 | 11 | WPA2-EAP
    14:21:26.242 -> 23 | DIRECT-c6-HP M452 LaserJet       |  -94 |  6 | WPA2
    14:21:26.242 -> 
    14:21:31.224 -> Scan start
*/
 
#include "WiFi.h"
 
void setup()
{
    Serial.begin(115200);
 
    // Set WiFi to station mode and disconnect from an AP if it was previously connected.
    WiFi.mode(WIFI_STA);
    WiFi.disconnect();
    delay(100);
 
    Serial.println("Setup done");
}
 
void loop()
{
    Serial.println("Scan start");
 
    // WiFi.scanNetworks will return the number of networks found.
    int n = WiFi.scanNetworks();
    Serial.println("Scan done");
    if (n == 0) {
        Serial.println("no networks found");
    } else {
        Serial.print(n);
        Serial.println(" networks found");
        Serial.println("Nr | SSID                             | RSSI | CH | Encryption");
        for (int i = 0; i < n; ++i) {
            // Print SSID and RSSI for each network found
            Serial.printf("%2d",i + 1);
            Serial.print(" | ");
            Serial.printf("%-32.32s", WiFi.SSID(i).c_str());
            Serial.print(" | ");
            Serial.printf("%4d", WiFi.RSSI(i));
            Serial.print(" | ");
            Serial.printf("%2d", WiFi.channel(i));
            Serial.print(" | ");
            switch (WiFi.encryptionType(i))
            {
            case WIFI_AUTH_OPEN:
                Serial.print("open");
                break;
            case WIFI_AUTH_WEP:
                Serial.print("WEP");
                break;
            case WIFI_AUTH_WPA_PSK:
                Serial.print("WPA");
                break;
            case WIFI_AUTH_WPA2_PSK:
                Serial.print("WPA2");
                break;
            case WIFI_AUTH_WPA_WPA2_PSK:
                Serial.print("WPA+WPA2");
                break;
            case WIFI_AUTH_WPA2_ENTERPRISE:
                Serial.print("WPA2-EAP");
                break;
            case WIFI_AUTH_WPA3_PSK:
                Serial.print("WPA3");
                break;
            case WIFI_AUTH_WPA2_WPA3_PSK:
                Serial.print("WPA2+WPA3");
                break;
            case WIFI_AUTH_WAPI_PSK:
                Serial.print("WAPI");
                break;
            default:
                Serial.print("unknown");
            }
            Serial.println();
            delay(10);
        }
    }
    Serial.println("");
 
    // Delete the scan result to free memory for code below.
    WiFi.scanDelete();
 
    // Wait a bit before scanning again.
    delay(5000);
}