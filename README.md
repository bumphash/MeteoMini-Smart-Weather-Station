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

MeteoMini uses a distributed two-node architecture based on ESP32 microcontrollers. The system consists of an **Outdoor Unit** and a **Main Unit**. The two units communicate wirelessly using the ESP-NOW protocol.

### 3.1 Outdoor Unit

The Outdoor Unit is designed to collect environmental measurements directly from the outdoor environment.

The unit is based on an ESP32 microcontroller and uses two environmental sensors:

* **SCD41** — measures carbon dioxide (CO₂), temperature and relative humidity.
* **BME680** — measures temperature, relative humidity, atmospheric pressure and gas resistance.

The ESP32 collects data from both sensors and transmits the measurements wirelessly to the Main Unit using ESP-NOW.

The Outdoor Unit allows the environmental sensors to be physically separated from the main display and control electronics, making it possible to place the measurement unit outside while keeping the Main Unit indoors.

### 3.2 Main Unit

The Main Unit is the central part of the MeteoMini system. It is also based on an ESP32 microcontroller.

The Main Unit receives environmental data from the Outdoor Unit through ESP-NOW and combines it with measurements from its local **DHT11** sensor.

The Main Unit is also responsible for data management, user-interface functionality and communication with the display and web interface.

An external **W25Q32 SPI flash memory** is used for non-volatile storage of measurement data. This allows MeteoMini to retain historical measurements and make them available through the History section of the user interface.

### 3.3 Wireless Communication

Communication between the Outdoor Unit and Main Unit is implemented using **ESP-NOW**.

ESP-NOW provides direct wireless communication between the two ESP32 devices without requiring the Outdoor Unit to connect to a conventional Wi-Fi network for data transmission.

The Outdoor Unit periodically sends the collected sensor measurements to the Main Unit. The Main Unit receives and processes these measurements together with its local sensor data.

### 3.4 Data Flow

The overall measurement and communication flow is:

<p align="center">

**SCD41 + BME680 → Outdoor ESP32 → ESP-NOW → Main ESP32 ← DHT11**

</p>

The Main ESP32 then processes the received and local measurements and provides the resulting data to the storage and user-interface layers.

