# RC-Landspeeder-ESP8266-RemoteXY-
D1 mini–powered RC Landspeeder with phone control via RemoteXY (Wi-Fi AP). Steering on D1, ESC on D2. Minimal, reliable mapping—no expo/deadband.

# RC Landspeeder (ESP8266 + RemoteXY)

> D1 mini–powered RC Landspeeder you can drive with your phone.  
> **Pins:** Steering servo = **D1 (GPIO5)**, ESC = **D2 (GPIO4)**.  
> **App:** RemoteXY connects to the ESP’s access point: SSID `Landspeeder`, port `6377`.

https://github.com/ASTDrones/rc-landspeeder-esp8266-remotexy

## Features
- Phone control via **RemoteXY** (Wi-Fi AP; no internet needed)
- Minimal & reliable mapping (no expo/deadband)
- Neutral hold on boot and when disconnected
- Same ESC/servo setup as my MSE droid build

## Hardware
- LOLIN/WEMOS **D1 mini** (ESP8266)
- RC **ESC** (car ESC) + brushed/brushless motor (per ESC)
- Standard **steering servo**
- Power: ESC BEC → 5 V to D1 mini (or external 5 V UBEC). Common ground required.

## Wiring
| Function | ESP8266 pin | Notes |
|---|---|---|
| Steering servo signal | **D1 (GPIO5)** | 1500 µs center, ±400 µs travel |
| ESC signal | **D2 (GPIO4)** | 1500 µs neutral, 1000/2000 µs min/max |
| 5 V / GND | 5V / G | From ESC BEC or UBEC; keep grounds common |

> Tip: If the ESP ever reboots under load, add a **470–1000 µF** cap at 5 V/GND or use a separate UBEC.

## Software
- **Arduino IDE** (or Arduino CLI)
- **ESP8266 board support**
- Libraries:  
  - `RemoteXY` (v3.1.13+)  
  - `Servo` (bundled with esp8266 core)

Board settings (typical): *LOLIN(WEMOS) D1 R2 & mini*, 80 MHz, 4M (FS:no), 115200 baud.

## RemoteXY app
- Install the RemoteXY mobile app.
- Power the Landspeeder. The ESP hosts an AP named **`Landspeeder`**.
- Connect the app to **Wi-Fi Point**: SSID `Landspeeder`, (blank password unless you change it), **port 6377**.
- The UI is embedded in firmware (`RemoteXY_CONF[]`), so it loads automatically.
- Controls:
  - **Throttle** slider: `-100..100` (default 0)
  - **Steering** joystick **X**: `-100..100`

## Build & Flash
1. Clone this repo.
2. Open `src/Landspeeder_RemoteXY.ino` in Arduino IDE.
3. Select the D1 mini board, choose the right COM port.
4. Upload.

## Safety
- Wheels off the ground for first power-up.
- ESC will **hold neutral for ~1s** at boot so it can arm/beep normally.
- The sketch sends neutral when the app is disconnected.

## Troubleshooting
- Motor spins during beeps → ESC not seeing neutral or bad ESC. Hold neutral at boot is included; try another ESC or invert throttle in code.
- Brownouts/reboots → add 470–1000 µF cap at 5 V or use UBEC.
- Reverse directions: set `REVERSE_THR` / `REVERSE_STR` in the sketch.

## License
MIT — see [LICENSE](LICENSE).
