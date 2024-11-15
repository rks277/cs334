
// #define BROADCAST_BUTTON_PIN 4
// #define RESET_BUTTON_PIN 5
// #define LED_RED_PIN 12
// #define LED_GREEN_PIN 14
#include "ESP32_NOW.h"
#include "WiFi.h"
#include <esp_mac.h> // For MAC2STR and MACSTR macros

/* Definitions */
#define ESPNOW_WIFI_CHANNEL 7
#define ESPNOW_WIFI_IFACE WIFI_IF_STA
#define ESPNOW_EXAMPLE_PMK "pmk1234567890123"

// Device-specific configuration
#define DEVICE_ID 1 // Set this to 1, 2, or 3 for each device

// GPIO Pins
#define BROADCAST_BUTTON_PIN 4
#define RESET_BUTTON_PIN 5
#define LED_RED_PIN 12
#define LED_GREEN_PIN 14

/* Hardcoded MAC Addresses (replace with actual MACs of the devices) */
const uint8_t DEVICE1_MAC[6] = {0x24, 0x6F, 0x28, 0xAA, 0xBB, 0x01};
const uint8_t DEVICE2_MAC[6] = {0x24, 0x6F, 0x28, 0xAA, 0xBB, 0x02};
const uint8_t DEVICE3_MAC[6] = {0x24, 0x6F, 0x28, 0xAA, 0xBB, 0x03};

/* Message Structure */
typedef struct {
    uint8_t sender_mac[6];   // Sender's MAC address
    uint8_t message_type;    // 0 = Broadcast, 1 = Return call
    uint8_t led_color;       // Sender's LED color (0 = red, 1 = green)
} __attribute__((packed)) message_t;

/* Global Variables */
volatile bool broadcast_triggered = false;
volatile bool reset_triggered = false;
bool can_receive_broadcasts = true; // Determines if the device can receive broadcasts

ESP_NOW_Network_Peer broadcast_peer(ESP_NOW.BROADCAST_ADDR, 0, NULL);

/* Function Prototypes */
void IRAM_ATTR onBroadcastButtonPress();
void IRAM_ATTR onResetButtonPress();
void broadcastMessage();
void sendReturnMessage(const uint8_t *receiver_mac, uint8_t led_color);
void resetDevice();
void lightLED(uint8_t led_color);
bool isValidMAC(const uint8_t *mac);

/* Callbacks */
void onReceive(const uint8_t *data, size_t len, bool broadcast) {
    if (len != sizeof(message_t)) {
        Serial.println("Invalid message length. Ignoring.");
        return;
    }

    message_t *msg = (message_t *)data;

    // Validate MAC address
    if (!isValidMAC(msg->sender_mac)) {
        Serial.println("Invalid sender MAC. Ignoring.");
        return;
    }

    if (msg->message_type == 0 && can_receive_broadcasts) { // Broadcast
        Serial.printf("Received broadcast from " MACSTR "\n", MAC2STR(msg->sender_mac));

        // Light up LED based on the sender's color
        lightLED(msg->led_color);

        // Send return message to the broadcasting device
        sendReturnMessage(msg->sender_mac, (DEVICE_ID == 1) ? 0 : 1); // Example: 0 = red, 1 = green
    } else if (msg->message_type == 1) { // Return call
        Serial.printf("Received return call from " MACSTR "\n", MAC2STR(msg->sender_mac));

        // Light up LED based on the sender's color
        lightLED(msg->led_color);
    }
}

/* LED Control */
void lightLED(uint8_t led_color) {
    if (led_color == 0) { // Red
        digitalWrite(LED_RED_PIN, HIGH);
        digitalWrite(LED_GREEN_PIN, LOW);
    } else if (led_color == 1) { // Green
        digitalWrite(LED_RED_PIN, LOW);
        digitalWrite(LED_GREEN_PIN, HIGH);
    }
}

/* Broadcast Logic */
void broadcastMessage() {
    message_t msg;
    WiFi.macAddress(msg.sender_mac);
    msg.message_type = 0; // Broadcast
    msg.led_color = (DEVICE_ID == 1) ? 0 : 1; // Example: 0 = red, 1 = green

    if (!broadcast_peer.send_message((uint8_t *)&msg, sizeof(msg))) {
        Serial.println("Broadcast failed");
    } else {
        Serial.println("Broadcast sent successfully");
        can_receive_broadcasts = false; // Disable receiving further broadcasts
    }
}

/* Return Message Logic */
void sendReturnMessage(const uint8_t *receiver_mac, uint8_t led_color) {
    message_t msg;
    WiFi.macAddress(msg.sender_mac);
    msg.message_type = 1; // Return call
    msg.led_color = led_color;

    ESP_NOW_Network_Peer receiver(receiver_mac);
    if (!receiver.send_message((uint8_t *)&msg, sizeof(msg))) {
        Serial.println("Return message failed");
    } else {
        Serial.println("Return message sent successfully");
    }
}

/* Reset Logic */
void resetDevice() {
    can_receive_broadcasts = true; // Enable receiving broadcasts
    digitalWrite(LED_RED_PIN, LOW);
    digitalWrite(LED_GREEN_PIN, LOW);
    Serial.println("Device reset to receiving mode");
}

/* Validate MAC Address */
bool isValidMAC(const uint8_t *mac) {
    return (memcmp(mac, DEVICE1_MAC, 6) == 0 ||
            memcmp(mac, DEVICE2_MAC, 6) == 0 ||
            memcmp(mac, DEVICE3_MAC, 6) == 0);
}

/* Interrupt Handlers */
void IRAM_ATTR onBroadcastButtonPress() {
    broadcast_triggered = true;
}

void IRAM_ATTR onResetButtonPress() {
    reset_triggered = true;
}

/* Setup */
void setup() {
    Serial.begin(115200);

    pinMode(LED_RED_PIN, OUTPUT);
    pinMode(LED_GREEN_PIN, OUTPUT);
    pinMode(BROADCAST_BUTTON_PIN, INPUT_PULLUP);
    pinMode(RESET_BUTTON_PIN, INPUT_PULLUP);

    attachInterrupt(BROADCAST_BUTTON_PIN, onBroadcastButtonPress, FALLING);
    attachInterrupt(RESET_BUTTON_PIN, onResetButtonPress, FALLING);

    // WiFi setup
    WiFi.mode(WIFI_STA);
    WiFi.setChannel(ESPNOW_WIFI_CHANNEL);

    // ESP-NOW setup
    if (!ESP_NOW.begin((const uint8_t *)ESPNOW_EXAMPLE_PMK)) {
        Serial.println("Failed to initialize ESP-NOW");
        ESP.restart();
    }

    if (!broadcast_peer.begin()) {
        Serial.println("Failed to initialize broadcast peer");
        ESP.restart();
    }

    ESP_NOW.onReceive(onReceive, NULL);

    Serial.println("Setup complete. Ready to receive broadcasts.");
}

/* Main Loop */
void loop() {
    if (broadcast_triggered) {
        broadcast_triggered = false;
        Serial.println("Broadcast button pressed. Broadcasting...");
        broadcastMessage();
    }

    if (reset_triggered) {
        reset_triggered = false;
        Serial.println("Reset button pressed. Resetting device...");
        resetDevice();
    }
}