#include <BleMouse.h>

BleMouse bleMouse("ESP32 BLE Mouse", "Espressif", 100);

const int VRX_PIN = A0;
const int VRY_PIN = A1;
const int SW_PIN  = 5;

const int CENTER   = 2048;   // 12-bit ADC on ESP32 (0-4095)
const int DEADZONE = 200;    // adjust if it drifts
const int MAX_MOVE = 15;     // pixels per loop

void setup() {
  Serial.begin(115200);
  pinMode(SW_PIN, INPUT_PULLUP);
  bleMouse.begin();
}

void loop() {
  if (bleMouse.isConnected()) {
    int x = analogRead(VRX_PIN);
    int y = analogRead(VRY_PIN);
    int sw = digitalRead(SW_PIN);

    int dx = 0, dy = 0;

    if (abs(x - CENTER) > DEADZONE)
      dx = map(x - CENTER, -2048, 2048, -MAX_MOVE, MAX_MOVE);
    if (abs(y - CENTER) > DEADZONE)
      dy = map(y - CENTER, -2048, 2048, -MAX_MOVE, MAX_MOVE);// up=up

    if (dx || dy) bleMouse.move(dx, dy);

    static bool wasPressed = false;
    bool pressed = (sw == LOW);
    if (pressed && !wasPressed) bleMouse.press(MOUSE_LEFT);
    else if (!pressed && wasPressed) bleMouse.release(MOUSE_LEFT);
    wasPressed = pressed;
  }

  delay(10);
}