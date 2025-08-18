# RC Landspeeder (ESP8266 + RemoteXY)

<p align="center">
  <img src="landspeeder_hero.jpg" alt="Two RC Landspeeders on tarmac" width="100%">
</p>

Drive a Star-Wars-style landspeeder with your **phone**. This project uses a **Wemos/LOLIN D1 mini (ESP8266)** and the **RemoteXY** app running as a Wi-Fi access point, so it works anywhere—no internet required.

---

## TL;DR (Quick Start)

1. Open `src/Landspeeder_RemoteXY.ino` in Arduino IDE.  
2. Boards Manager: install **ESP8266** platform; select **LOLIN(WEMOS) D1 R2 & mini**.  
3. Libraries: install **RemoteXY (v3.1.13+)**; **Servo** comes with the ESP8266 core.  
4. Flash the sketch.  
5. On your phone, install **RemoteXY**, choose **Wi-Fi Point**, connect to SSID **`Landspeeder`** (no password by default), port **6377**.  
6. Controls:  
   - **Throttle slider** → `-100..100` (neutral = 0)  
   - **Steering joystick (X)** → `-100..100`  
7. First power-up: wheels off the ground—ESC holds **neutral ~1s** to arm/beep cleanly.

---

## Hardware

- Wemos/LOLIN **D1 mini (ESP8266)**
- Car **ESC** + motor (per ESC)
- Standard **steering servo**
- Power: ESC **BEC 5V** to the D1 mini (or a separate 5V **UBEC**)
- Common ground between ESC/servo/D1 mini

### Wiring

| Function | ESP8266 pin | Notes |
|---|---|---|
| Steering servo signal | **D1 (GPIO5)** | ~1500 µs center, ±400 µs travel |
| ESC signal | **D2 (GPIO4)** | 1500 µs neutral; 1000/2000 µs min/max |
| 5V / GND | 5V / G | From ESC BEC or UBEC; **grounds common** |

> If the ESP ever reboots under load, add a **470–1000 µF** capacitor across 5V/GND near the D1 mini or power it from a UBEC.

---

## Software / Build

- Arduino IDE or Arduino CLI  
- **ESP8266** board package  
- Libraries: **RemoteXY 3.1.13+**, **Servo** (bundled)

Typical board settings: 80 MHz, 4M (FS: none), 115200 baud.

Sketch location: `src/Landspeeder_RemoteXY.ino`

Key pins & controls in the sketch:
- **D1** = steering servo, **D2** = ESC  
- **Throttle** comes from `RemoteXY.Throttle`  
- **Steering** comes from `RemoteXY.joystick_01_x`  
- Neutral is held on boot and when the app disconnects.

To flip a channel, set `REVERSE_THR` or `REVERSE_STR` to `true`.

---

## RemoteXY App

- Install **RemoteXY** on your phone.  
- Connect to **Wi-Fi Point**:
  - **SSID:** `Landspeeder`
  - **Password:** *(empty unless you change it in the sketch)*
  - **Port:** `6377`
- The UI is embedded in firmware (`RemoteXY_CONF[]`), so it loads automatically.

---

## Troubleshooting

- **Motor spins during beeps / no arming:** ESC not seeing neutral or the ESC is faulty. This sketch holds 1500 µs on boot; try another ESC or flip throttle direction.
- **ESP resets under throttle:** BEC sag. Add a **470–1000 µF** cap on 5 V at the D1 mini or use a **UBEC**.
- **Steering/throttle reversed:** set `REVERSE_THR` / `REVERSE_STR = true;`
- **Endpoints feel short/long:** tweak `SERVO_RANGE_US` (steering) or min/max µs for ESC.

---

## Gallery

<p align="center">
  <img src="landspeeder_detail.jpg" alt="RC Landspeeder shells — clean vs weathered" width="900">
</p>

---

## Social Preview

GitHub uses a repository **social preview** when links are shared.  
Upload **`landspeeder_social.jpg`** in your repo:

1. Repo → **Settings → General → Social preview**  
2. Click **Upload an image** and choose `landspeeder_social.jpg` (1280×640).

---

## License

MIT — see [LICENSE](LICENSE).

---

## Credits

- Remote UI powered by **RemoteXY**  
- ESP8266 board: **Wemos/LOLIN D1 mini**  
- Project, wiring, and code assembled by the community & this repo’s maintainer.
