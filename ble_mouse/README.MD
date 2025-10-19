# 🖱️ FeatherV2 Joystick BLE Mouse  
### A portable Bluetooth mouse built with Adafruit ESP32 Feather V2, joystick, and OLED display  

---

## 🚀 Overview
This project turns an **Adafruit ESP32 Feather V2** and a simple **analog joystick** into a fully functional **Bluetooth LE mouse** — complete with:
- **Joystick control** for cursor movement  
- **Joystick button** for left-click  
- **Live battery monitoring and percentage display**  
- **OLED screen** showing battery, voltage, and BLE status  
- **Portable power via 3.7 V LiPo battery**  

The result: a compact, wireless, rechargeable joystick mouse that displays its battery level in real time.  

---

## 🧩 Features
✅ **Bluetooth LE Mouse (BLE HID)**  
- Moves cursor with joystick  
- Press joystick button for left-click  
- Auto reconnects to paired device  

✅ **Battery Monitoring**  
- Reads LiPo voltage via VBAT pin (A13)  
- Converts voltage → percentage  
- Displays both voltage and percentage  

✅ **OLED Display (SSD1306 128×64)**  
- Shows:  
  - Battery percentage and voltage  
  - BLE connection status (“Connected” / “Not connected”)  
- Updates automatically every 5 seconds  

✅ **Portable Power**  
- Runs from onboard LiPo (3.7 V)  
- Auto charges when plugged into USB-C  
- Automatically switches between battery and USB power  

✅ **Quality-of-Life Fixes**
- Y-axis movement corrected for natural “up = up” feel  
- BLE and joystick timing optimized (no lag)  
- Battery readings rate-limited to prevent blocking  

---

## ⚙️ Hardware Required

| Component | Description |
|------------|-------------|
| 🧠 **Adafruit ESP32 Feather V2** | Core board with BLE + LiPo charging |
| 🕹️ **Analog Joystick Module** | 5-pin type (GND, 5V, VRx, VRy, SW) |
| 🔋 **LiPo Battery (3.7 V)** | 400 mAh–1200 mAh with correct Adafruit JST polarity |
| 🖥️ **OLED Display (SSD1306 I²C)** | 0.96″ 128×64 screen |
| 🔌 **USB-C Cable** | For uploads and charging |

---

## 🧠 Wiring Diagram

### 🎮 Joystick
| Joystick Pin | Feather Pin | Notes |
|---------------|-------------|-------|
| **GND** | GND | Ground |
| **5V** | 3V | Safe at 3.3 V |
| **VRx** | A0 | X-axis |
| **VRy** | A1 | Y-axis |
| **SW** | 27 | Joystick button |

### 🖥️ OLED Display
| OLED Pin | Feather Pin | Notes |
|-----------|--------------|-------|
| **GND** | GND | Ground |
| **VCC** | 3V | Power |
| **SDA** | 22 | I²C Data |
| **SCL** | 20 | I²C Clock |

---

## 🔋 Power Notes
- LiPo plugs into the JST connector (**Adafruit polarity**: red = right, black = left).  
- USB-C charges the LiPo automatically.  
- Board switches seamlessly between battery and USB.  
- Battery voltage is read through `A13` with a built-in 2:1 divider.  

---

## 💻 Software Setup

### 1️⃣ Install Dependencies
In Arduino IDE → **Library Manager**:
- `ESP32 BLE Mouse` (by T-vK)  
- `Adafruit SSD1306`  
- `Adafruit GFX Library`  

### 2️⃣ Select the Board
- **Board:** `Adafruit ESP32 Feather V2`  
- **Upload Speed:** `115200` (recommended for stability)

### 3️⃣ Upload the Sketch
The full working code integrates:
- BLE mouse movement  
- Battery percentage monitoring  
- OLED status display  

---

## 🖥️ Example OLED Output
`Battery: 85%
Voltage: 3.96V
BLE: Connected`

`If BLE disconnects, it automatically updates to:`
`Battery: 85%
Voltage: 3.96V
BLE: Connected`

---

## 🧩 Future Enhancements
- 💤 Auto OLED sleep after inactivity  
- ⚠️ Low-battery cutoff (< 3.3 V warning)  
- 🔄 Mode toggle (cursor ↔ scroll wheel)  
- 💾 Store last BLE pairing info in NVS  
- 🌙 Deep-sleep power saving  

---

## 🧠 Troubleshooting

| Symptom | Cause | Fix |
|----------|--------|-----|
| No cursor movement | BLE not connected | Re-pair as “FeatherV2 Joystick Mouse” |
| OLED blank | Wrong SDA/SCL pins | Use SDA = 22, SCL = 20 |
| No LEDs on Feather | Cosmetic only; board still works fine |
| Battery not charging | Check JST polarity or LiPo health |

---

## ⚡ Credits
Developed by **David Navarro** using the Adafruit ESP32 Feather V2 and open-source Arduino libraries.  
Special thanks to the open hardware community for documentation and support 💪  

---

## 📸 Optional Add-Ons
If you’d like to extend this project:
- Add a **3D printed enclosure**  
- Implement **OLED auto-sleep** when BLE disconnects  
- Add **scroll mode** toggle with joystick press  
- Add a **low-battery warning** (OLED flashes “LOW BATTERY”)  

---

⭐ If you found this useful, give it a star on GitHub!  
