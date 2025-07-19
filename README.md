# voicebot-over-wifi
A DIY WiFi-enabled talking robot that can receive commands and speak responses using text-to-speech. Ideal for IoT, voice control, and embedded systems learning projects.

---

## 🔧 Features

- 📶 WiFi connectivity for remote control
- 🗣️ Speech output using text-to-speech (TTS)
- 💬 Send commands from a phone or PC over HTTP/WebSocket
- 🔌 Powered by ESP32/NodeMCU (customizable)
- 🔊 Speaker integration for audible responses
- 🧠 Programmable responses and voice messages

---

## 🚀 Getting Started

### 📁 Clone the Repository

```bash
git clone https://github.com/your-username/wifi-talking-robot.git
cd wifi-talking-robot
🧰 Hardware Requirements
ESP32 or NodeMCU board

Speaker (e.g., DFPlayer Mini + speaker or I2S DAC)

Power supply (battery or USB)

Breadboard & jumper wires

(Optional) Microphone / Sensor for expansion

🖥️ Software Requirements
Arduino IDE or PlatformIO

ESP32 / ESP8266 board packages installed

Libraries:

WiFi.h

ESPAsyncWebServer.h

DFRobotDFPlayerMini (if using DFPlayer)

ESP8266SAM (for TTS on ESP8266)

ESP32 I2S (if using ESP32 + external DAC)

⚙️ How It Works
Connect to WiFi using the ESP board.

Host a local web server or connect to a cloud API.

Receive text commands (via HTTP or MQTT).

Convert text to speech using onboard or external TTS module.

Output sound through speaker.

📱 Example Command Flow
Send a POST request to /speak:

http
Copy
Edit
POST /speak
Content-Type: application/json

{
  "message": "Hello, I am your WiFi Talking Robot!"
}
Robot responds through speaker:
"Hello, I am your WiFi Talking Robot!"

🖼️ Project Diagram
text
Copy
Edit
[ WiFi Command ] ---> [ ESP32 / NodeMCU ] ---> [ TTS Module ] ---> [ Speaker ]
📸 Media
Add demo video or photos here

📄 License
This project is licensed under the MIT License. See the LICENSE file for more details.

🙋‍♂️ Author
Made with ❤️ Aniket Pawar
Feel free to contribute or fork!

💡 Future Improvements
Add voice recognition

Connect to Google Assistant / Alexa

Battery monitoring

Mobile app control

