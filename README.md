# MeteoMini — Smart Weather Station

## 1. Project Overview

MeteoMini is a compact IoT-based weather station designed for real-time environmental monitoring, data visualization and historical analysis.

The system combines embedded electronics, environmental sensors, a local display and a web-based interface. Sensor data is collected by the embedded controller, processed by the firmware and presented to the user through the local display and web dashboard.

The web interface provides several functional sections, including Dashboard, Weather, History, Settings and About. These sections allow the user to monitor current environmental conditions, review historical measurements and configure the system.

The local display provides direct access to the current measurements. MeteoMini also includes Day and Night display modes to provide a more comfortable interface under different lighting conditions.

The project is designed as a modular platform that can be extended with additional sensors, monitoring functions and software features.

---

## 2. System Architecture

MeteoMini consists of several interconnected subsystems:

* **Embedded Controller** — controls the sensors, processes measurements and manages the system logic.
* **Environmental Sensors** — collect physical weather parameters from the surrounding environment.
* **Local Display** — provides real-time information directly on the device.
* **Web Interface** — provides remote access to measurements and system functions.
* **Data History** — stores previously collected measurements for later analysis.
* **Configuration System** — allows the user to adjust available system parameters.

The general data flow can be represented as:

<p align="center">

**Sensors → Embedded Controller → Data Processing → Display / Web Interface → Historical Data**

</p>

---

## 3. Hardware Architecture

MeteoMini uses a distributed architecture based on two ESP32 microcontrollers: an **Outdoor Unit** and a **Main Unit**.

The Outdoor Unit is responsible for collecting environmental measurements outside the building. The Main Unit acts as the central controller, receiving outdoor measurements, collecting local measurements, storing historical data and providing the user interface.

### 3.1 Outdoor Unit

The Outdoor Unit is based on an ESP32 microcontroller and is designed for outdoor environmental monitoring.

It uses two sensors:

* **SCD41** — measures CO₂ concentration, temperature and relative humidity.
* **BME680** — measures temperature, relative humidity, atmospheric pressure and gas resistance.

The ESP32 periodically reads the sensor values and transmits the measurements to the Main Unit using the **ESP-NOW** wireless communication protocol.

This architecture allows the Outdoor Unit to be installed separately from the Main Unit while maintaining a direct wireless connection between the two devices.

### 3.2 Main Unit

The Main Unit is based on a second ESP32 microcontroller and acts as the central processing unit of MeteoMini.

The Main Unit receives measurements from the Outdoor Unit through ESP-NOW and also collects local environmental data using a **DHT11** sensor.

The Main Unit is responsible for:

* receiving outdoor sensor measurements;
* reading local sensor data;
* processing and combining measurements;
* storing historical data;
* serving the web interface;
* handling user commands and configuration;
* controlling the local display.

### 3.3 Local Display

The Main Unit is connected to a **2.0-inch 320×240 IPS color display based on the ST7789 controller**.

The display uses the **SPI interface** and provides a local user interface for viewing current measurements and system information.

MeteoMini supports different display modes, including a dedicated Night Mode for operation in low-light conditions.

### 3.4 W25Q32 Flash Memory

The Main Unit uses an external **W25Q32 SPI flash memory** as non-volatile storage.

The W25Q32 is used for two main purposes:

1. **Web Interface Storage** — the HTML, CSS, JavaScript and other required web-interface resources are stored directly in the flash memory.
2. **Historical Data Storage** — recorded environmental measurements are stored in the same memory and are later used by the History section of the interface.

This approach allows the MeteoMini web interface and historical measurement data to be stored locally on the device without requiring an external server or database.

### 3.5 Wi-Fi Web Server

The Main ESP32 operates as a local web server and provides access to the MeteoMini web interface through Wi-Fi.

The web interface is stored in the W25Q32 flash memory and is served directly by the Main ESP32. Users can connect to the station over Wi-Fi using a web browser to monitor measurements and control available system functions.

The web interface provides access to the Dashboard, Weather, History, Settings and About sections.

### 3.6 Wireless Communication

Communication between the Outdoor Unit and Main Unit is implemented using **ESP-NOW**.

The Outdoor ESP32 collects data from the SCD41 and BME680 sensors and transmits the measurements to the Main ESP32.

The Main ESP32 receives the data and combines it with measurements from the local DHT11 sensor. The processed data is then used by the display, web interface and historical data storage.

### 3.7 Overall Data Flow

The complete system data flow can be represented as follows:

<p align="center">

**SCD41 + BME680**
↓
**Outdoor ESP32**
↓
**ESP-NOW**
↓
**Main ESP32**
↑
**DHT11**

**Main ESP32**
↓
**W25Q32** → Web Interface + Historical Data

**Main ESP32**
↓
**ST7789 Display**

**Main ESP32**
↕
**Wi-Fi**
↕
**User Web Browser**

</p>

