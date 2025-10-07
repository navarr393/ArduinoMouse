# ArduinoMouse
# 🖱️ Arduino UNO R4 WiFi Joystick Mouse

A simple project that turns your **Arduino UNO R4 WiFi** into a **USB HID mouse** controlled by a joystick.  
Move the joystick to move the cursor and press it to left-click — just like a game controller controlling your mouse!

---

## 🎯 Features
- Full **USB HID mouse** emulation (plug-and-play on Windows, macOS, Linux)
- Smooth analog cursor movement using joystick axes
- Built-in **deadzone** to prevent drift
- Variable speed control — the further you push, the faster it moves
- Joystick button acts as **left-click**

---

## 🧰 Hardware Required
| Component | Quantity | Notes |
|------------|-----------|-------|
| Arduino UNO R4 WiFi | 1 | Required for native USB HID |
| Analog joystick module | 1 | (X, Y, and SW pins) |
| Jumper wires | 4 | Male-to-female preferred |

---

## ⚙️ Wiring

| Joystick Pin | UNO R4 WiFi Pin | Description |
|---------------|----------------|-------------|
| **VRX** | A0 | Horizontal axis |
| **VRY** | A1 | Vertical axis |
| **SW** | D2 | Joystick push button |
| **VCC** | 5V | Power |
| **GND** | GND | Ground |

---

## 🧩 How It Works
1. The Arduino reads analog voltages from the joystick (`A0`, `A1`) and converts them to cursor movement (`Mouse.move()`).
2. A **deadzone** prevents tiny noise near the center from moving the cursor.
3. The **map()** function scales movement so small deflections move slowly and large ones move quickly.
4. The joystick’s button (`D2`) sends a **left-click** using `Mouse.press()` and `Mouse.release()`.
5. The board enumerates as a USB mouse device automatically when connected to a computer.

---

## 🧾 Example Output
When you move the joystick:
X: 720 | Y: 310 | SW: released
X: 512 | Y: 512 | SW: pressed
---

## 🚀 Uploading the Sketch
1. Open the Arduino IDE.
2. Go to **Tools → Board → Arduino UNO R4 WiFi**.
3. Copy the sketch into a new file.
4. Click **Upload**.
5. Your computer should now recognize a new mouse device.

---

## 🧠 Future Upgrades
- Add **right-click** with long-press or a second button.
- Add **scroll-wheel** emulation.
- Port to **Bluetooth HID** for wireless mouse control (Nano ESP32 or R4 WiFi BLE).
- Use **OLED display** or LEDs to show connection state or battery if made portable.

---

## ⚠️ Notes
- When connected, your board acts as a real mouse — be careful while testing (keep a physical mouse handy!).
- You may need to press the **RESET** button twice quickly if the USB device isn’t detected after uploading.

---

### 👨‍💻 Author
Created by **David Navarro Duenas**  
Simple, smooth, and fun example of USB HID on the Arduino UNO R4 WiFi.
