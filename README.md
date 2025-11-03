# LD2411S  
[HiLink LD2411S](https://www.hlktech.net/index.php?id=1152) — 24GHz mmWave Static and Motion Sensor  
ESPHome Integration (updated for latest ESPHome versions)

![LD2411S](https://www.hlktech.net/res/_cache/auto/14/1459.png)

---

## 🧾 Credits  
Original integration created by the [initial project author](https://github.com/Chreece/LD2411S-ESPHome).  
This version has been updated to be compatible with the latest **ESPHome** releases, which now use **external components** instead of deprecated custom components.

---

## 🔧 Updates in This Version  
- Converted to **ESPHome external component** and can now be compiled.
- Removed number entities for *min/max distance* and *unoccupied time* (and their readouts), as they did not work reliably across all tested boards (only 1 of 3).  
  - These parameters can now be configured directly via the **HiLink App**: [HLKRadarTool](https://www.pgyer.com/Lq8p).  
- Simplified setup and improved compatibility with the ESP-IDF framework.  
- Preserved all functional entities (presence, motion, distance, Bluetooth control)

---


## 🔌 Wiring

| LD2411S | ESP |
|----------|-----|
| **Vin**  | 5V  |
| **GND**  | GND |
| **TX**   | RX  |
| **RX**   | TX  |

---

## 📡 Entities Exposed  
- **Distance** – Distance to target (in cm)  
- **Motion** – True if motion is detected  
- **Presence** – True if target is present  
- **Bluetooth** – Turn Bluetooth module on or off  
- **Reboot Module** – Reboot only the LD2411S  
- **Factory Reset** – Restore default LD2411S settings  

---

## 📝 Description  
The **HiLink LD2411S** detects **motion** and **presence** within a configurable range using 24GHz mmWave radar technology.  
It includes a built-in Bluetooth module compatible with the [HLKRadarTool app](https://www.pgyer.com/Lq8p) for adjusting radar parameters such as detection range and unoccupied delay times.

OTA updates are also available via Bluetooth.

---

## 🧠 Notes   
- The removed distance and unoccupied time settings can still be tuned via the **HiLink mobile app**.  
- Works reliably across ESP32 boards using the ESP-IDF framework.

---

## 🙌 Acknowledgements  
Thanks to the original creator for the initial ESPHome integration and documentation.  
This fork focuses on **modernizing compatibility** and **improving reliability** for current ESPHome versions.
