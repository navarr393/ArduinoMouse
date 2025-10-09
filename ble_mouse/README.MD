# 🖱️ ESP32 Bluetooth Joystick Mouse

Turn any ESP32 board (Nano ESP32, ESP32 Dev Kit, ESP32-S3, etc.) into a **wireless Bluetooth mouse** controlled by an analog joystick!  
Move the joystick to move the cursor and press the joystick’s built-in button to left-click — all over BLE.

---

## 🎯 Features
- Fully wireless **Bluetooth HID mouse** (no dongle needed)
- Smooth analog movement with dead-zone filtering
- Joystick button acts as **left click**
- Works with **Windows**, **macOS**, **Linux**, **Android**, and **Smart TVs**
- Built with Arduino and BLE HID

---

## 🧰 Hardware Required
| Component | Quantity | Notes |
|------------|-----------|-------|
| **ESP32 board** | 1 | Works on Nano ESP32, ESP32-S3, or regular Dev Kit |
| **Analog joystick module** | 1 | Standard 2-axis joystick with push button (KY-023 or similar) |
| **Jumper wires** | 5 | Male-to-male or male-to-female as needed |

---

## ⚙️ Wiring

> ⚠️ Even if your joystick says **5V**, power it from **3.3V** when using ESP32!  
> Feeding 5V into analog pins can damage your board.

| Joystick Pin | ESP32 Pin | Description |
|---------------|-----------|--------------|
| **VCC** | 3.3V | Power |
| **GND** | GND | Ground |
| **VRX** | GPIO 34 | X-axis analog input |
| **VRY** | GPIO 35 | Y-axis analog input |
| **SW** | GPIO 14 | Button input |

---

## 🧩 Arduino IDE Setup

1. Open **Arduino IDE**
2. **Boards Manager →** search “esp32” → install **Espressif Systems – ESP32**  
   - Recommended version: **2.0.14** *(library uses `String`, newer 3.x releases cause compile errors)*  
   - If you already have 3.x installed and get conversion errors, simply downgrade to 2.0.x.
3. Select your board under **Tools → Board → ESP32 Arduino → ESP32 Dev Module** (or Nano ESP32 / ESP32-S3)
4. **Tools → Port:** choose the correct USB port.
5. **Library Manager →** search and install **ESP32 BLE Mouse** by *T-vK*  
   - If not found, download from GitHub: [https://github.com/T-vK/ESP32-BLE-Mouse](https://github.com/T-vK/ESP32-BLE-Mouse)  
     → **Sketch → Include Library → Add .ZIP Library…**

---
