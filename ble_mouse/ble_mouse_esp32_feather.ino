#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <BleMouse.h>

BleMouse bleMouse("FeatherV2 Joystick Mouse", "Adafruit", 100);

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define I2C_SDA 22
#define I2C_SCL 20
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);

// Pin definitions
#define VRX_PIN A0
#define VRY_PIN A1
#define SW_PIN 27
#define VBAT_PIN A13

const int CENTER = 2048;
const int DEADZONE = 300;
const int MOVE_RANGE = 20;

unsigned long lastBatteryCheck = 0;
float batteryVoltage = 0;
int batteryPercent = 0;

float readBatteryVoltage() {
  return analogRead(VBAT_PIN) * 2.0 * 3.3 / 4095.0;
}

int voltageToPercent(float v) {
  if (v >= 4.2) return 100;
  if (v <= 3.2) return 0;
  return (int)((v - 3.2) * 100.0);
}

void setup() {
  Serial.begin(115200);
  pinMode(SW_PIN, INPUT_PULLUP);
  bleMouse.begin();

  // Initialize I2C explicitly on Feather pins
  Wire.begin(I2C_SDA, I2C_SCL);

  // OLED setup
  if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
    Serial.println(F("SSD1306 allocation failed"));
    for (;;);
  }
  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(0, 0);
  display.println("BLE Joystick Mouse");
  display.display();
  delay(1500);
}

void loop() {
  // Battery update every 5 s
  if (millis() - lastBatteryCheck > 5000) {
    batteryVoltage = readBatteryVoltage();
    batteryPercent = voltageToPercent(batteryVoltage);
    lastBatteryCheck = millis();

    // Update OLED
    display.clearDisplay();
    display.setCursor(0, 0);
    display.setTextSize(1);
    display.print("Battery: ");
    display.print(batteryPercent);
    display.println("%");
    display.print("Voltage: ");
    display.print(batteryVoltage, 2);
    display.println("V");
    display.print("BLE: ");
    display.println(bleMouse.isConnected() ? "Connected" : "Not connected");
    display.display();

    Serial.print("Battery: ");
    Serial.print(batteryVoltage, 2);
    Serial.print("V (");
    Serial.print(batteryPercent);
    Serial.println("%)");
  }

  // Joystick control
  if (bleMouse.isConnected()) {
    int x = analogRead(VRX_PIN);
    int y = analogRead(VRY_PIN);
    bool pressed = !digitalRead(SW_PIN);

    int dx = 0, dy = 0;
    if (abs(x - CENTER) > DEADZONE)
      dx = map(x - CENTER, -2048, 2048, -MOVE_RANGE, MOVE_RANGE);
    if (abs(y - CENTER) > DEADZONE)
      dy = map(y - CENTER, -2048, 2048, -MOVE_RANGE, MOVE_RANGE);

    if (dx != 0 || dy != 0) bleMouse.move(dx, dy);
    if (pressed) bleMouse.press(MOUSE_LEFT);
    else bleMouse.release(MOUSE_LEFT);
  }

  delay(10);
}