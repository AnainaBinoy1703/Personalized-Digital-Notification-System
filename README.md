# Personalized Digital Notification System

This is a personalized digital message display system built using an **ESP32**, **OLED 128x64 display**, **Blynk app**, and **EEPROM (Preferences)**. It lets you send real-time messages from your phone to an OLED screen wirelessly and stores the last message even after restarting.

---

## 🔧 Components Used

| Component         | Quantity | Description                              |
|------------------|----------|------------------------------------------|
| ESP32 Dev Board  | 1        | Wi-Fi enabled microcontroller            |
| OLED Display     | 1        | SSD1306, 128x64 pixels                    |
| Blynk App        | -        | Mobile app to send messages              |
| Jumper Wires     | A few    | For circuit connections                  |
| Breadboard       | 1        | For prototyping                          |

---

## ⚙️ How It Works

1. Connect the OLED display to the ESP32 using I2C (SCL, SDA).
2. Upload the Arduino code from `PDNS.ino`.
3. Use the Blynk app to send messages to the ESP32 via Wi-Fi.
4. The message is displayed on the OLED screen in real time.
5. The last received message is saved to EEPROM so it appears again after rebooting.

---

## 🔌 Circuit Diagram

```plaintext
OLED       →       ESP32  
GND        →       GND  
VCC        →       3.3V  
SCL        →       GPIO22  
SDA        →       GPIO21  
```
## 📷 Display Output

Here is a real-time view of the OLED display receiving messages from the Blynk app.

![OLED Display](images/display.jpg)
![Circuit Diagram](images/circuit.jpg)
---

## 🧠 Block Diagram

This is the block-level view of how the system components interact.

![Block Diagram](images/block.jpg)


---
![Flowchart](images/flowchart.jpg)
## 📜 License

This project is licensed under the MIT License.

---

## 👩‍💻 Author

**Anaina Binoy**  
BTech in Electronics and Communication Engineering  
GitHub: [github.com/AnainaBinoy1703](https://github.com/AnainaBinoy1703)
