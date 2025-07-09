#include <Arduino.h>
#include <WiFi.h>
#include <AsyncTCP.h>
#include <ESPAsyncWebServer.h>
#include <WebSerial.h>
#include <U8g2lib.h>
#include <WiFiClientSecure.h>
#include <ArduinoJson.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#define BLYNK_TEMPLATE_ID "TMPL3hCE9d6v6"
#define BLYNK_TEMPLATE_NAME "PERSONALIZED NDS"
#include <Preferences.h>
#include <BlynkSimpleEsp32.h>

Preferences preferences;

#define BLYNK_PRINT Serial

// WiFi Credentials
const char* ssid = "Jyothika";
const char* password = "12345678";

// Blynk Credentials
char auth[] = "l1K-lWdRpgNAk33nqJ0BssUE94Bp7MY4";

// OLED Configurations
#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define OLED_RESET -1
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

// Blynk Virtual Pins
#define MESSAGE_VIRTUAL_PIN V1
#define HISTORY_VIRTUAL_PIN V2

// Store last 5 messages
#define MAX_MESSAGES 5
String messages[MAX_MESSAGES] = {"", "", "", "", ""};

// Load Messages from EEPROM
void loadMessagesFromEEPROM() {
  preferences.begin("messages", false);
  for (int i = 0; i < MAX_MESSAGES; i++) {
    messages[i] = preferences.getString(("msg" + String(i)).c_str(), "");
  }
  preferences.end();
}

// Save Messages to EEPROM
void saveMessagesToEEPROM() {
  preferences.begin("messages", false);
  for (int i = 0; i < MAX_MESSAGES; i++) {
    preferences.putString(("msg" + String(i)).c_str(), messages[i]);
  }
  preferences.end();
}

// Update Blynk History Terminal
void updateHistoryInBlynk() {
  Blynk.virtualWrite(HISTORY_VIRTUAL_PIN, "\n");
  for (int i = 0; i < MAX_MESSAGES; i++) {
    if (messages[i] != "") {
      Blynk.virtualWrite(HISTORY_VIRTUAL_PIN, String(i + 1) + ". " + messages[i] + "\n");
    }
  }
}

// Update OLED Display Immediately
void updateOLED(const String &message) {
  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(0, 0);
  display.println(message);
  display.display();
}

// Blynk Callback for Incoming Message
BLYNK_WRITE(MESSAGE_VIRTUAL_PIN) {
  String message = param.asStr();

  // Shift old messages
  for (int i = MAX_MESSAGES - 1; i > 0; i--) {
    messages[i] = messages[i - 1];
  }
  messages[0] = message;

  saveMessagesToEEPROM();
  updateHistoryInBlynk();
  updateOLED(message); // Instantly update OLED
}

void setup() {
  Serial.begin(115200);
  Wire.begin();

  // OLED Init
  if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
    Serial.println("❌ OLED Initialization Failed!");
    while (1);
  }

  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(0, 0);
  display.println("Initializing...");
  display.display();

  // WiFi Init
  WiFi.begin(ssid, password);
  Serial.print("Connecting to WiFi");

  unsigned long startAttemptTime = millis();
  while (WiFi.status() != WL_CONNECTED && millis() - startAttemptTime < 5000) {
    delay(50);
    Serial.print(".");
  }

  if (WiFi.status() == WL_CONNECTED) {
    Serial.println("\n✅ WiFi Connected!");
  } else {
    Serial.println("\n❌ WiFi Connection Failed!");
  }

  Blynk.config(auth);
  Blynk.connect(3000); // Non-blocking connection with timeout

  display.clearDisplay();
  display.setCursor(0, 0);
  if (Blynk.connected()) {
    display.println("Blynk Connected!");
  } else {
    display.println("Blynk Failed!");
  }
  display.display();

  loadMessagesFromEEPROM();
  updateHistoryInBlynk();
}

void loop() {
  Blynk.run();
}