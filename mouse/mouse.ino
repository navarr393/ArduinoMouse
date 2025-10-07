#include <Mouse.h>

const int VRX_PIN = A0;
const int VRY_PIN = A1;
const int SW_PIN  = 2;

const int DEADZONE = 100; // ignore small movements around the center
const int CENTER = 512; // center
const int SPEED_DIV = 80; // higher = slower cursor

void setup() {
  Mouse.begin();
  pinMode(SW_PIN, INPUT_PULLUP);  // button reads low on pressed
}

void loop() {
  int x = analogRead(VRX_PIN);   // ~0..1023
  int y = analogRead(VRY_PIN);   // ~0..1023
  int sw = digitalRead(SW_PIN);  // HIGH = not pressed, LOW = pressed

  // translate joystick movement to mouse movement 
  int dx = 0;
  int dy = 0;

  if (abs(x - CENTER) > DEADZONE) {
    dx = map(x - CENTER, -512, 512, -15, 15);
  }
  if (abs(y - CENTER) > DEADZONE) {
    dy = map(y - CENTER, -512, 512, -15, 15); // invert y for natural feel
  }

  // move the cursor
  if (dx != 0 || dy != 0) {
    Mouse.move(dx, dy);
  }

  // click when the button is pressed
  static bool wasPressed = false;
  bool pressed = (sw == LOW);
  if (pressed && !wasPressed) {
    Mouse.press(MOUSE_LEFT);
  } else if (!pressed && wasPressed) {
    Mouse.release(MOUSE_LEFT);
  }
  wasPressed = pressed;
  delay(10);
}