
# BMW E87/E90 CAN Bus and Bluetooth Integration

This project is focused on **reverse engineering the BMW E90 and E87 CAN bus** line messages using an **ESP32 board**. It captures these messages and sends them via Bluetooth to Android/iOS smartphones, primarily aimed at **remapping the steering wheel buttons** for custom functions.

## Features
- **CAN Bus Message Reversing**: Capture CAN bus messages from BMW E90/E87 models.
- **Bluetooth Communication**: Send the captured data via Bluetooth to smartphones.
- **ESP32 Integration**: Uses an ESP32 microcontroller for hardware interfacing.
- **Steering Wheel Button Remapping**: Customize and remap unused steering wheel buttons for more functional operations.

## CAN Bus Message Breakdown
The project documents various **CAN message codes** for different devices connected to the vehicle's CAN bus, including:
- **Torque, Clutch, Brake Status**
- **Engine RPM & Throttle Position**
- **Steering Wheel Position**
- **Individual Wheel Speeds**
- **Door Status (Unlocked, Open)**
- **Ignition and Key Status**
- **Battery Voltage & Charge Status**

For a complete list, refer to the message codes section in this repository.

## Tech Stack
- **ESP32 Microcontroller**: Main controller for capturing CAN bus messages.
- **Bluetooth Communication**: For transmitting data to smartphones.
- **C & CMake**: Used for programming and compiling the code.

## Installation
1. Clone the repository:
   ```bash
   git clone https://github.com/llilakoblock/bmw-e87-e90-can-bt.git
   ```
2. Open the project in **PlatformIO** or another supported environment.
3. Flash the firmware to the ESP32 microcontroller:
   ```bash
   platformio run --target upload
   ```

## Usage
1. Install the necessary hardware in the vehicle (ESP32 connected to CAN bus).
2. Connect your Android/iOS device to the ESP32 via Bluetooth.
3. Customize steering wheel buttons or monitor CAN bus messages on the smartphone app.

## Future Enhancements
- **Further CAN Bus Integration**: Explore additional vehicle systems (e.g., HVAC, lighting).
- **Advanced Button Mapping**: Enhance steering wheel button functionality with more custom mappings.
- **Enhanced Bluetooth Communication**: Improve the interface with the smartphone app for smoother operation.

## Contributing
Feel free to contribute to this project by forking the repo, submitting issues, or creating pull requests. Contributions can range from bug fixes, new features, or improving documentation.

## License
This project is licensed under the **MIT License**.


CAN message codes for different car devieces connected to canbus:
| **Can-ID** | **Length** | **DATA Packet HEX**                 | **DATA Packet DECIMAL**                   | **Register Description**                             | **Reg** | **Mini** | **Kcan-1** | **Kcan-2** | **Source** |
|------------|-----------|-------------------------------------|-------------------------------------------|------------------------------------------------------|--------|---------|-----------|-----------|-----------|
| 0x0A8      | 8         | 54 D7 2B D0 2B F0 0F 02             | 084 215 043 208 043 240 015 002           | Torque, Clutch and Brake status                      |        |         | Y         | N         |           |
| 0x0AA      | 8         | 5F 59 FF 00  34 0D 80 99            | 095 089 255 000  052 013 128 153          | Engine RPM and throttle position                    |        |         | Y         | N         |           |
| 0x0C0      | 2         | F4 FF                               | 244 255                                   | ABS / Brake counter                                 |        |         | Y         | N         | JBE       |
| 0x0C4      | 7         | 83 FD FC 00 00 FF F1                | 131 253 252 000 000 255 241               | Steering Wheel position (See 0C8)                    |        |         | Y         | N         |           |
| 0x0C8      | 6         | DD 07 FC 00 00 FF                   | 221 007 252 000 000 255                   | Steering Wheel position (Sent 2× often 0C4)          |        |         | Y         | N         | SZL       |
| 0x0CE      | 8         | DA 02 DC 02 DC 02 D9 02             | 218 002 220 002 220 002 217 002           | Individual Wheel Speeds (4× Pairs)                   |        |         | Y         | N         |           |
| 0x0D7      | 2         | C3 FF                               | 195 255                                   | Counter (Airbag / Seatbelt Related)                  |        |         | Y         | N         |           |
| 0x0E2      | 8         | 81 FF E7 FC FF FF FF FF            | 129 255 231 252 255 255 255 255           | Passenger door status Unlocked, Open                 |        |         | Y         | Y         | JBE       |
| 0x0E6      | 8         | 81 FF E7 FC FF FF FF FF            | 129 255 231 252 255 255 255 255           | Rear Passenger door status Unlocked, Open            |        |         | Y         | Y         | JBE       |
| 0x0EA      | 8         | 81 FF E7 FC FF FF FF FF            | 129 255 231 252 255 255 255 255           | Driver door status Unlocked, Open                    |        |         | Y         | Y         | JBE       |
| 0x0EE      | 8         | 81 FF E7 FC FF FF FF FF            | 129 255 231 252 255 255 255 255           | Rear Driver door status Unlocked, Open               |        |         | Y         | Y         |           |
| 0x0F2      | 8         | F1 FF 87 C0 FF FF FF FF            | 241 255 135 192 255 255 255 255           | Boot status Unlocked, release button, Open           |        |         | Y         | Y         |           |
| 0x0FA      | 3         | C0 00 FF                           | 192 000 255                               | Electric Window controls (Driver controls)           |        |         | Y         |           |           |
| 0x0FB      | 3         | C7 FF FF                            | 199 255 255                               | Electric Window controls (Front Passenger)           | W      |         | Y         |           |           |
| 0x130      | 5         | 45 40 21 8F FE                     | 069 064 033 143 254                       | Ignition and Key status (Term 15 / R ON?)            |        |         | Y         | Y         | CAS       |
| 0x193      | 8         | 27 FE F1 00 F8 50 00 00             | 039 254 241 000 248 080 000 000           | Timer & Cruise control status                        |        |         | Y         |           |           |
| 0x19E      | 8         | 00 E0 B3 FC F0  43 00 65            | 000 224 179 252 240 067 000 101           | ABS / Braking force                                  |        |         | Y         | N         | DSC       |
| 0x1A6      | 8         | 13 4D 46 4D 33 4D D0 FF             | 019 077 070 077 051 077 208 255           | Speed, as used by the instrument cluster             |        |         | Y         | Y         |           |
| 0x1B4      | 8         | 00 D0 E0 F8 00 32 FE 91             | 000 208 224 248 000 050 254 145           | Speed [MPH] Handbrake status                         |        |         | Y         | N         | Kombi     |
| 0x1C2      | 8         | 8D 72 5B 5A FF FF FF FF            | 141 114 091 090 255 255 255 255           | PDC (Reverse) / (Front) Sensor data                  |        |         | Y         |           |           |
| 0x1D0      | 8         | 4C FF 63 CD 5D 37 CD A8             | 076 255 099 208 093 055 205 168           | Engine temp, Pressure sensor & Handbrake             |        |         | Y         | N         |           |
| 0x1D6      | 2         | C0 0C                               | 192 012                                   | MFL (Steering Wheel) Buttons                         |        |         | Y         | Y         | SZL       |
| 0x1E1      | 6         | D4 F1 00 FF FF FF                   | 212 241 000 255 255 255                   | Counter and Door Status (200ms intervals)            |        |         | Y         | Y         |           |
| 0x1E3      | 2         | F1 FF                               | 141 255                                   | Interior Light Switch                                | W      |         | Y         |           |           |
| 0x1EE      | 2         | 00 FF                               | 000 255                                   | Indicator Stalk position                             |        |         | Y         | Y         |           |
| 0x1F6      | 2         | 80 F0                               | 128 240                                   | Indicator Status                                     | W*     |         | Y         | Y         |           |
| 0x202      | 2         | 54 FF                               | 084 255                                   | Lights (Dimmer Status)                               |        |         | Y         | Y         | Kombi     |
| 0x21A      | 3         | 05 12 F7                            | 005 018 247                               | Lighting Status                                      |        |         | Y         | Y         |           |
| 0x23A      | 4         | 00 30 00 60                         | 000 048 000 096                           | Remote Control Keyfob Actions                        |        |         | Y         | Y         |           |
| 0x246      | 5         | 3F  F3 00 FC FF                     | 063  243 000 252 255                      | Air Con, Demister Status                             |        |         | Y         | Y         |           |
| 0x24A      | 2         | 06 FF                               | 006 255                                   | Reverse Status                                       |        |         | Y         |           |           |
| 0x24B      | 2         | 00 F8                               | 000 248                                   | Door status, similar to 2FC                          |        |         | Y         | Y         |           |
| 0x252      | 2         | CE FF                               | 206 255                                   | Windscreen Wiper Status                              |        |         | Y         |           | JBE       |
| 0x264      | 6         | E1 FD  21 A2 7F 1E                  | 225 253  033 162  127 030                 | iDrive Controller (Rotary Control)                   |        |         | Y         |           | CON       |
| 0x267      | 6         | E1 FD CC 01 DE 01                   | 225 253 204 001 222 001                   | iDrive Controller (Direction / Buttons)              |        |         | Y         | Y         | CON       |
| 0x26E      | 8         | 00 40 7F 50 FF FF FF FF            | 000 064 127 080 255 255 255 255           | Ignition Status                                      |        |         | Y         | Y         | CAS       |
| 0x273      | 8         | 1D E1 00 F0 FF 7F DE 04             | 029 225 000 240 255 127 222 004           | CCC / CIC Status                                     |        |         | Y         | N         | CIC       |
| 0x277      | 8         | E1 9D 04 FF                         | 225 157 004 255                           | iDrive controller reply to 0x273                     |        |         | Y         | N         | CON       |
| 0x286      | 2         | 00 FF                               | 000 255                                   | Rear View Mirror, Light sensor                       |        |         | Y         | Y         |           |
| 0x2A6      | 2         | 00 F9                               | 000 249                                   | Windscreen Wiper Controls                            |        |         | Y         | Y         | SZL       |
| 0x2B4      | 2         | 00 F2                               | 000 242                                   | Door locking (Via Remote Control)                    |        |         | Y         |           |           |
| 0x2B8      | 6         | 31 00 F0 00 00 E3                    | 049 000 240 000 000 227                   | Reset Av Fuel / Speed                                |        |         | Y         |           | Radio     |
| 0x2BA      | 5         | 00 00 00 00 10                       | 000 000 000 000 16                        | Counter (Toggle / Heartbeat)                         |        |         | Y         | N         | Kombi     |
| 0x2CA      | 2         | 61 FF                               | 097 255                                   | Outside temperature                                  |        | TBC     | Y         |           | Kombi     |
| 0x2D6      | 3         | FF FC FF                            | 255 252 255                               | Air Conditioning Status                              |        |         | Y         | Y         |           |
| 0x2E6      | 8         | 64 00 00 FF 00 01 3F 34             | 100 000 000 255 000 001 063 052           | Climate control status (Fan and Temp speed)           |        |         | Y         | Y         |           |
| 0x2EA      | 8         | FF FF FF FF FF FF FF 34            | 255 255 255 255 255 255 255 52            | Climate control status (Passenger)                   |        |         | Y         | Y         |           |
| 0x2F8      | 8         | 13 2E 1E 01 4F DC 07 FD             | 019 046 030 001 079 220 007 253           | Report Time and Date                                 |        |         | Y         | Y         | Kombi     |
| 0x2FC      | 7         | 81 01 00 FF FF FF FF               | 129 001 000 255 255 255 255               | Door Status                                          |        |         | Y         | Y         | CAS       |
| 0x328      | 6         | 16 83 A2 04 DE 11                   | 022 126 244 003 222 017                   | 1 Second count from battery removal / reset          |        |         | Y         | Y         | Kombi     |
| 0x32E      | 8         | 00 FF 8F 63 6A 00 2E 0F             | 000 255 143 099 106 000 046 015           | Internal Temp, Light and solar sensors               |        |         | Y         | Y         |           |
| 0x330      | 8         | 7A 5A 00  2D 29 2F 9C 34            | 122 090 000 045 041 047 156 052           | Odometer, Av Fuel, and Range                         |        |         | Y         | Y         | Kombi     |
| 0x349      | 5         | 76 0F BE 1A 00                      | 118 015 190 026 000                       | Fuel Level sensors                                   |        |         | Y         | Y         | JBE       |
| 0x34F      | 2         | FE FF                               | 254 255                                   | Handbrake status                                     |        |         | Y         |           |           |
| 0x362      | 7         | AE F3 1E FF FF FF EA               | 174 241 030 255 255 255 234               | Average MPH & Average MPG                            |        |         | Y         | N         | Kombi     |
| 0x366      | 4         | 78  50 14 FC                       | 120  080 020 252                          | Ext Temp & Range                                     |        |         | Y         | N         | Kombi     |
| 0x380      | 7         | 56 xx 35 32 38 37 xx                | 086 xxx 053 050 056 055 xxx               | VIN Number                                           |        |         | Y         |           | CAS       |
| 0x394      | 8         | 48 0F 10 6B 00 88 58 01             | 072 015 016 107 000 136 088 001           | Hours / Distance since last service                  |        |         | Y         |           |           |
| 0x39E      | 8         | 0B 10 00 0D 1F DF 07 F2             | 011 016 000 013 031 223 007 242           | Set Time and Date                                    |        |         | Y         |           |           |
| 0x3B0      | 2         | FD FF                               | 253 255                                   | Reverse Status                                       |        |         | Y         |           |           |
| 0x3B4      | 8         | A6 F3 00 FC FF FF FF FF            | 165 243 000 252 255 255 255 255           | Battery Voltage & Charge status                      |        |         | Y         | N         |           |
| 0x3B6      | 3         | 00 FC F0                            | 000 252 240                               | Passenger Front Window status                        |        |         | Y         | N         |           |
| 0x3B7      | 3         | 41 F5 F8                            | 065 245 248                               | Driver Rear Window status                            |        |         | Y         | Y         | JBE       |
| 0x3B8      | 3         | 00 FC F0                            | 000 252 240                               | Driver Front Window status                           |        |         | Y         |           |           |
| 0x3B9      | 3         | 41 F5 F8                            | 065 245 248                               | Passenger Rear Window status                         |        |         | Y         |           | JBE       |
| 0x581      | 8         | 40 4D 00 28 FF FF FF FF            | 064 077 000 040 255 255 255 255           | Seatbelt Status                                      |        |         | Y         |           |           |
| 0x7C3      | 8         | xx xx xx xx xx xx xx xx            | xxx xxx xxx xxx xxx xxx xxx xxx           | Keyfob (security, comfort and CBS data)              |        |         | Y         |           | CAS       |

Reg = Register type, W = Writeable (the ID can be emulated by an external Can controller, whilst in the car with no adverse affects)

Source Information
Kombi = Instrument Cluster.
Multi = Multiple sources.
JBE = Junction Box Electronic Module
CAS = Car Access System
SZL = Steering column switch cluster (The SZL is on the 500KHz F-CAN bus. Data is passed onto the K-can via gateway module.)
CON = idrive Controller
DSC = Dynamic Stability Control

Modules:
| **Can-ID** | **Length** | **DATA Packet HEX**      | **DATA Packet DECIMAL**                  | **Register Description**                        | **Reg** |
|------------|-----------|--------------------------|------------------------------------------|------------------------------------------------|---------|
| 600        | 8         | F1 10 1F 5A 80 00 00 09  | 241 016 031 090 128 000 000 009          | JBBF, Junction Box Module                      |         |
| 601        | 8         | F1 10 1F 5A 80 00 00 09  | 241 016 031 090 128 000 000 009          | MRS, Airbag                                    |         |
| 640        | 8         | F1 10 1F 5A 80 00 00 06  | 241 016 031 090 128 000 000 006          | CAS. CAS ELV. car access system                |         |
| 641        | 8         | F1 10 1F 5A 80 00 00 06  | 241 016 031 090 128 000 000 006          | DWA, AntiTheft Alarm System.                   |         |
| 650        | 8         | F1 10 1F 5A 80 00 00 06  | 241 016 031 090 128 000 000 006          | SINE, Siren And Tilt Sensor.                   |         |
| 656        | 8         | F1 10 1F 5A 80 00 00 06  | 241 016 031 090 128 000 000 006          | FZD, functional roof sensor                    |         |
| 660        | 8         | F1 10 1F 5A 80 00 00 06  | 241 016 031 090 128 000 000 006          | KOMBI, Instrument Cluster                      |         |
| 664        | 8         | F1 10 1F 5A 80 00 00 06  | 241 016 031 090 128 000 000 006          | PDC, Rear Parking Sensors                      |         |
| 672        | 8         | F1 10 1F 5A 80 00 00 06  | 241 016 031 090 128 000 000 006          | FRM, Footwell module                           |         |
| 678        | 8         | F1 10 1F 5A 80 00 00 06  | 241 016 031 090 128 000 000 006          | KLIMA, Climate control                         |         |

PT-CAN (500 kHz)
| **Can-ID** | **Length** | **DATA Packet HEX**      | **DATA Packet DECIMAL**                  | **Register Description**   | **Reg** |
|------------|-----------|--------------------------|------------------------------------------|----------------------------|---------|
| 612        | 8         | F1 10 3C 5A 80 00 00 08  | 241 016 060 090 128 000 000 008          | DDE 6.0 N47 module         |         |
| 617        | 8         | F1 10 1F 5A 80 00 00 09  | 241 016 031 090 128 000 000 009          | EKP                        |         |
| 629        | 8         | F1 10 1F 5A 80 00 00 09  | 241 016 031 090 128 000 000 009          | ABS, DSC                   |         |
