// ============================================================
// 🖱️ FeatherV2 BLE Joystick Mouse with OLED + Battery Display
// ------------------------------------------------------------
// This code turns your Adafruit ESP32 Feather V2 into a 
// Bluetooth mouse controlled by a joystick.
//
// Features:
//  ✅ Joystick controls mouse movement
//  ✅ Joystick button = Left click
//  ✅ OLED shows battery voltage, % and BLE status
//  ✅ Runs off LiPo or USB
//  ✅ Reads and converts battery voltage to percentage
//
// Fully commented version for learning and reference.
// ============================================================

// ----- Include required libraries -----
#include <Wire.h>                // I²C communication (for OLED)
#include <Adafruit_GFX.h>        // Core graphics functions
#include <Adafruit_SSD1306.h>    // OLED display control
#include <BleMouse.h>            // Turns ESP32 into a BLE mouse

// ----- Define OLED display parameters -----
#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define I2C_SDA 22     // Feather SDA pin
#define I2C_SCL 20     // Feather SCL pin
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);

// ----- BLE Mouse setup -----
BleMouse bleMouse("FeatherV2 Joystick Mouse", "Adafruit", 100);
// Device name, manufacturer, and starting BLE battery percentage

// ----- Pin definitions -----
#define VRX_PIN A0     // Joystick X-axis
#define VRY_PIN A1     // Joystick Y-axis
#define SW_PIN 27      // Joystick push button
#define VBAT_PIN A13   // Battery voltage reading

// ----- Joystick movement configuration -----
const int CENTER = 2048;   // Midpoint of analog input (12-bit ADC = 0–4095)
const int DEADZONE = 300;  // Ignore small movements to prevent jitter
const int MOVE_RANGE = 20; // Mouse movement sensitivity

// ----- Variables for battery monitoring -----
float batteryVoltage = 0;
int batteryPercent = 0;
unsigned long lastBatteryCheck = 0; // Timer for periodic voltage updates

// ============================================================
// Function: Read Battery Voltage
// Reads LiPo voltage from A13 and converts it to actual voltage.
// The Feather divides voltage by 2 before it reaches the ADC.
// ============================================================
float readBatteryVoltage() {
  return analogRead(VBAT_PIN) * 2.0 * 3.3 / 4095.0; 
  // Multiply by 2 (divider), scale by 3.3V ref, divide by ADC range
}

// ============================================================
// Function: Convert Voltage to Battery Percentage
// Approximates LiPo charge level from 3.2V (empty) to 4.2V (full).
// ============================================================
int voltageToPercent(float v) {
  if (v >= 4.2) return 100;  // Fully charged
  if (v <= 3.2) return 0;    // Empty
  return (int)((v - 3.2) * 100.0); // Linear mapping
}

// ============================================================
// Setup
// Initializes BLE mouse, OLED, joystick, and serial debug.
// ============================================================
void setup() {
  Serial.begin(115200);         // Debugging output
  pinMode(SW_PIN, INPUT_PULLUP);// Joystick button uses internal pull-up

  bleMouse.begin();             // Initialize BLE mouse functionality
  Wire.begin(I2C_SDA, I2C_SCL); // Start I²C communication

  // ----- Initialize the OLED -----
  if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) { // Common address 0x3C
    Serial.println(F("SSD1306 allocation failed"));
    for (;;); // Halt if display not found
  }

  // Display splash screen
  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(0, 0);
  display.println("BLE Joystick Mouse");
  display.display();
  delay(1500);
}

// ============================================================
// Main Loop
// Handles:
//   - BLE connection state
//   - Joystick mouse movement
//   - Button clicks
//   - Battery + OLED updates every 5 seconds
// ============================================================
void loop() {
  // ----- Check battery every 5 seconds -----
  if (millis() - lastBatteryCheck > 5000) {
    batteryVoltage = readBatteryVoltage();     // Get voltage
    batteryPercent = voltageToPercent(batteryVoltage); // Convert to %

    // Update OLED with latest battery + BLE info
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
    lastBatteryCheck = millis(); // Reset timer
  }

  // ----- Only control mouse if BLE is connected -----
  if (bleMouse.isConnected()) {
    int x = analogRead(VRX_PIN);      // Read X-axis (0–4095)
    int y = analogRead(VRY_PIN);      // Read Y-axis (0–4095)
    bool pressed = !digitalRead(SW_PIN); // Joystick press (LOW = pressed)

    int dx = 0, dy = 0;

    // --- Map joystick X movement to cursor ---
    if (abs(x - CENTER) > DEADZONE)
      dx = map(x - CENTER, -2048, 2048, -MOVE_RANGE, MOVE_RANGE);

    // --- Map joystick Y movement to cursor (normal, not inverted) ---
    if (abs(y - CENTER) > DEADZONE)
      dy = map(y - CENTER, -2048, 2048, MOVE_RANGE, -MOVE_RANGE); 
      // Inverted mapping so up = up, down = down

    // --- Move the mouse if joystick is outside deadzone ---
    if (dx != 0 || dy != 0)
      bleMouse.move(dx, dy);

    // --- Handle left click when button pressed ---
    if (pressed)
      bleMouse.press(MOUSE_LEFT);
    else
      bleMouse.release(MOUSE_LEFT);
  }

  delay(10); // Small delay for smoother motion + lower CPU usage
}
