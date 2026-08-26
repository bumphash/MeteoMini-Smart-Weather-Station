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

## 3. Hardware Architecture

### 4.1 Outdoor ESP32

The Outdoor Unit is controlled by an ESP32 microcontroller. Its primary function is to acquire environmental data from the SCD41 and BME680 sensors and transmit the measurements to the Main Unit.

The ESP32 communicates with the sensors, performs the initial processing of the measurements and prepares the data packet for wireless transmission.

Communication with the Main Unit is performed using ESP-NOW. This allows the Outdoor Unit to operate as an independent measurement node without requiring a permanent connection to the local web interface.

The Outdoor ESP32 is therefore responsible for:

- sensor data acquisition;
- initial data processing;
- measurement packet preparation;
- wireless transmission via ESP-NOW;
- periodic measurement updates.

- ### 4.2 SCD41 CO₂ Sensor

The SCD41 is used in the Outdoor Unit for environmental monitoring. It provides measurements of:

- CO₂ concentration;
- temperature;
- relative humidity.

The sensor is connected to the Outdoor ESP32 and its measurements are periodically read by the firmware.

The CO₂ measurement provides an additional environmental parameter that is not available from the BME680 or DHT11 sensors. Temperature and humidity data from the SCD41 can also be used as additional environmental measurements and for comparison with the other sensors.

The collected SCD41 data is transmitted to the Main Unit together with the measurements from the BME680.
**Wi-Fi**
↕
**User Web Browser**

### 4.3 BME680 Environmental Sensor

The BME680 is used as the second environmental sensor in the Outdoor Unit.

It provides measurements related to:

- temperature;
- relative humidity;
- atmospheric pressure;
- gas resistance.

The ESP32 periodically reads the BME680 measurements and includes the available values in the data packet transmitted to the Main Unit.

Using the BME680 together with the SCD41 allows the Outdoor Unit to collect a wider range of environmental parameters from a single location.

### 4.4 Main ESP32

The Main ESP32 is the central controller of the MeteoMini system.

It receives measurement packets from the Outdoor ESP32 through ESP-NOW and simultaneously reads the local DHT11 sensor.

The Main ESP32 processes the received and local measurements and makes the resulting data available to the rest of the system.

Its main functions include:

- receiving Outdoor Unit measurements;
- reading the local DHT11 sensor;
- processing measurement data;
- controlling the ST7789 display;
- managing W25Q32 flash memory;
- storing historical measurements;
- serving the web interface;
- processing commands received from the web interface;
- managing system settings;
- providing Wi-Fi connectivity for user access.

- ### 4.5 DHT11 Local Sensor

The DHT11 is installed in the Main Unit and provides local temperature and relative humidity measurements.

Unlike the SCD41 and BME680, which are installed in the Outdoor Unit, the DHT11 measures the environmental conditions at the location of the Main Unit.

The Main ESP32 reads the DHT11 data and combines it with the measurements received from the Outdoor Unit.

This allows MeteoMini to monitor environmental conditions at two different locations within the same system.

### 4.6 W25Q32 Flash Memory

The W25Q32 is an external non-volatile SPI flash memory connected to the Main ESP32.

It is used as local storage for two major parts of the MeteoMini system:

1. Web interface resources.
2. Historical measurement data.

The web application files are stored directly in the W25Q32 and served by the Main ESP32 when a user connects to the station through Wi-Fi.

Historical sensor measurements are also stored in the same flash memory. The stored data can later be accessed through the History section of the web interface.

Using external flash memory provides persistent local storage while keeping the system independent of an external database or cloud service.

### 4.7 ST7789 IPS Display

The Main Unit uses a 2.0-inch 320×240 IPS color display based on the ST7789 controller.

The display is connected to the Main ESP32 using the SPI interface.

It provides a local graphical user interface for displaying current measurements and system information.

The display supports different visual modes, including Day Mode and Night Mode. This allows the same interface to be used during both normal daytime operation and in low-light environments.

### 4.8 ESP-NOW Communication

ESP-NOW is used as the wireless communication protocol between the Outdoor ESP32 and the Main ESP32.

The Outdoor Unit acts as the measurement node and periodically transmits sensor data to the Main Unit.

The Main Unit receives the data and integrates it with measurements from the local DHT11 sensor.

The communication architecture can therefore be summarized as:

<p align="center">
  <b>Outdoor ESP32 → ESP-NOW → Main ESP32</b>
</p>

This separation allows the measurement hardware to be located outdoors while the main processing, storage, display and user interface remain in the Main Unit.

### 4.9 Wi-Fi and Web Server

The Main ESP32 creates and operates the MeteoMini web server.

Users can connect to the Main Unit through Wi-Fi using a standard web browser. The web application is stored locally in the W25Q32 flash memory and is served directly by the Main ESP32.

The web interface provides access to:

- current measurements;
- weather information;
- historical data;
- system settings;
- display modes;
- system information.

The web interface also provides control functions, allowing the user to configure available system parameters remotely without directly interacting with the embedded hardware.



</p>
# 5. Pinout & Wiring

This section documents the electrical connections between the ESP32 controllers and the sensors, display and external flash memory.

## 5.1 Outdoor Unit — ESP32 + BME680

The BME680 is connected to the Outdoor ESP32 using the I²C interface.

| ESP32 OUTDOOR | BME680 | Function  |
| ------------- | ------ | --------- |
| 3.3V          | VCC    | Power     |
| GND           | GND    | Ground    |
| GPIO22        | SCL    | I²C Clock |
| GPIO21        | SDA    | I²C Data  |

## 5.2 Outdoor Unit — ESP32 + SCD41

The SCD41 is connected to the same I²C bus as the BME680.

| ESP32 OUTDOOR | SCD41 | Function  |
| ------------- | ----- | --------- |
| 3.3V          | VCC   | Power     |
| GND           | GND   | Ground    |
| GPIO22        | SCL   | I²C Clock |
| GPIO21        | SDA   | I²C Data  |

Both sensors share the same I²C bus:

**GPIO22 → SCL**
**GPIO21 → SDA**

## 5.3 Main Unit — ESP32 + ST7789 Display

The Main Unit uses a 2.0-inch 320×240 IPS color display based on the ST7789 controller.

| ST7789 Display | ESP32 Main | Function          |
| -------------- | ---------- | ----------------- |
| VCC            | 3.3V       | Power             |
| GND            | GND        | Ground            |
| CLK            | GPIO18     | SPI Clock         |
| SDA / MOSI     | GPIO23     | SPI Data          |
| CS             | GPIO15     | Chip Select       |
| DC             | GPIO2      | Data / Command    |
| RST            | GPIO4      | Reset             |
| BLK            | GPIO32     | Backlight Control |

## 5.4 Main Unit — ESP32 + DHT11

The DHT11 is connected to the Main ESP32 as a local temperature and humidity sensor.

| DHT11    | ESP32 Main | Function    |
| -------- | ---------- | ----------- |
| VCC (+)  | 3.3V       | Power       |
| D (DATA) | GPIO27     | Sensor Data |
| GND (-)  | GND        | Ground      |

## 5.5 Main Unit — ESP32 + W25Q32

The W25Q32 external flash memory is connected to the Main ESP32 using SPI.

| W25Q32 Module | ESP32 Main | Function    |
| ------------- | ---------- | ----------- |
| VCC           | 3.3V       | Power       |
| GND           | GND        | Ground      |
| CLK           | GPIO25     | SPI Clock   |
| DI            | GPIO26     | MOSI        |
| D0            | GPIO14     | MISO        |
| CS            | GPIO21     | Chip Select |

## 5.6 Interface Summary

| Interface | ESP32 Unit     | Connected Devices | GPIO                                    |
| --------- | -------------- | ----------------- | --------------------------------------- |
| I²C       | Outdoor        | SCD41 + BME680    | SDA: GPIO21, SCL: GPIO22                |
| SPI       | Main           | ST7789            | CLK: GPIO18, MOSI: GPIO23               |
| SPI       | Main           | W25Q32            | CLK: GPIO25, MOSI: GPIO26, MISO: GPIO14 |
| Digital   | Main           | DHT11             | GPIO27                                  |
| ESP-NOW   | Outdoor ↔ Main | ESP32 ↔ ESP32     | Wireless                                |
| Wi-Fi     | Main           | Web Browser       | Wireless                                |


# 6. Software Architecture

The MeteoMini software is divided into two embedded firmware components and a local web application.

The **Outdoor ESP32 firmware** is responsible for sensor acquisition and wireless transmission. The **Main ESP32 firmware** acts as the central application controller, manages local hardware, stores measurement data and provides the web interface.

## 6.1 Outdoor Unit Firmware

The Outdoor ESP32 firmware is responsible for collecting environmental data from the SCD41 and BME680 sensors.

The firmware periodically performs the following operations:

1. Initializes the connected sensors.
2. Reads the current measurements from the SCD41.
3. Reads the current measurements from the BME680.
4. Processes the acquired sensor values.
5. Creates a measurement data packet.
6. Transmits the packet to the Main ESP32 using ESP-NOW.
7. Repeats the measurement cycle.

The Outdoor Unit operates independently from the user interface. Its primary purpose is reliable acquisition and transmission of outdoor environmental measurements.

## 6.2 Main Unit Firmware

The Main ESP32 firmware is the central software component of MeteoMini.

It performs several tasks simultaneously:

* receives measurements from the Outdoor ESP32;
* reads the local DHT11 sensor;
* processes measurement data;
* controls the ST7789 display;
* manages the W25Q32 flash memory;
* stores historical measurements;
* runs the local web server;
* serves the web application;
* processes commands received from the web interface;
* manages system settings.

The Main Unit combines data received from the Outdoor Unit with measurements from the local DHT11 and makes the resulting information available to both the local display and the web interface.

## 6.3 ESP-NOW Communication

ESP-NOW is used as the communication layer between the two ESP32 controllers.

The Outdoor ESP32 acts as the transmitting node, while the Main ESP32 acts as the receiving node.

The Outdoor Unit sends a structured measurement packet containing the available sensor values. The Main Unit receives the packet and updates the corresponding environmental parameters.

The communication path is:

<p align="center">
  <b>Outdoor Sensors → Outdoor ESP32 → ESP-NOW → Main ESP32</b>
</p>

This architecture separates outdoor measurement acquisition from the main processing and user-interface functions.

## 6.4 Measurement Processing

After receiving data from the Outdoor Unit, the Main ESP32 processes the measurements together with the local DHT11 data.

The resulting dataset represents the current state of the monitored environment and is used by several system components:

* local display;
* web Dashboard;
* Weather page;
* historical data storage;
* other system functions requiring current measurements.

The Main ESP32 therefore acts as the central data processing point of the system.

## 6.5 W25Q32 Data Storage

The W25Q32 flash memory provides persistent local storage for the MeteoMini application.

Two main types of data are stored in the flash memory:

### Web Application

The web interface resources are stored locally on the W25Q32. The Main ESP32 reads these resources from the flash memory and serves them to connected clients through the local web server.

### Historical Measurements

Measurement records are also stored in the W25Q32. The stored records are used by the History section of the web interface to display previously collected environmental data.

This architecture allows MeteoMini to operate without an external database or cloud storage service.

## 6.6 Local Web Server

The Main ESP32 runs the MeteoMini web server directly.

When a user connects to the station through Wi-Fi, the ESP32 serves the web application stored in the W25Q32.

The browser-based interface communicates with the Main ESP32 to obtain current measurements and perform available control and configuration operations.

The web server therefore provides the connection between the embedded system and the user.

## 6.7 Web Application

The MeteoMini web application provides a graphical interface for monitoring and controlling the station.

The main sections are:

* **Dashboard** — general overview of the system and current measurements.
* **Weather** — detailed current environmental information.
* **History** — previously recorded measurements.
* **Settings** — system configuration and available controls.
* **About** — general information about the MeteoMini system.

The web application is stored locally in the W25Q32 and does not require a separate web server.

## 6.8 Local Display Interface

The Main ESP32 also controls the ST7789 display.

The display provides a local interface for viewing current measurements and system information without accessing the web interface.

The firmware manages the display content and supports different visual modes, including Day Mode and Night Mode.

## 6.9 Software Data Flow

The overall software data flow can be summarized as:

<p align="center">
  <b>
  Sensors<br>
  ↓<br>
  Outdoor ESP32<br>
  ↓<br>
  ESP-NOW<br>
  ↓<br>
  Main ESP32<br>
  ↙ ↓ ↘<br>
  Display · W25Q32 · Web Server<br>
  ↓ &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; ↓<br>
  Local UI &nbsp;&nbsp;&nbsp;&nbsp;&nbsp; Web Browser
  </b>
</p>

