# Smart Farm Monitoring System using Arduino

## Project Overview
This project is an Arduino-based smart farm monitoring system designed to provide real-time insights into critical environmental parameters essential for optimal plant growth. By integrating various sensors and a visual display, it aims to offer a practical and educational demonstration of agricultural automation technologies.

## Features
*   **Real-time Environmental Monitoring:** Continuously collects and displays data.
*   **Temperature & Humidity Sensing:** Utilizes a DHT11 sensor for accurate air condition measurement.
*   **Soil Moisture Detection:** Employs a soil moisture sensor to gauge water levels.
*   **Light Intensity Measurement:** Uses an LDR (Light Dependent Resistor) to monitor ambient light.
*   **Visual Data Display:** Mini OLED screen provides immediate numerical readings of all monitored parameters.
*   **Status Indication:** Multiple LEDs and relays provide visual and automated control feedback.
*   **Arduino Uno Powered:** The core of the system is the versatile Arduino Uno microcontroller.

## Components Used

### Hardware:
*   Arduino Uno
*   DHT11 Temperature and Humidity Sensor
*   Soil Moisture Sensor
*   Light Dependent Resistor (LDR)
*   Mini OLED Display (SSD1306 0.96 inch)
*   4 LEDs (for status indication)
*   3 Relays (for automated control)
*   Jumper Wires
*   Breadboard
*   Power Supply for Arduino

### Software:
*   Arduino IDE
*   Libraries:
    *   `DHT sensor library` (for DHT11)
    *   `Adafruit GFX Library` (for OLED)
    *   `Adafruit SSD1306 Library` (for OLED)



## How It Works
1.  **Initialization:** Upon power-up, the Arduino initializes all connected sensors and the OLED display.
2.  **Data Acquisition:**
    *   The DHT11 sensor is polled to read ambient temperature and humidity.
    *   The soil moisture sensor's analog output is read to determine moisture levels.
    *   The LDR's analog output is read to measure light intensity.
3.  **Data Processing & Display:**
    *   The collected sensor values are processed and mapped to percentages where applicable.
    *   These values are then sent to the mini OLED display to be shown in a user-friendly format.
4.  **Status Indication:**
    *   LEDs provide visual feedback based on sensor readings:
        *   LED 1 blinks if temperature exceeds 35°C.
        *   LED 2 indicates low soil moisture (below 20%).
        *   LED 3 blinks if humidity exceeds 70% or is very low (below 20%).
        *   LED 4 indicates optimal conditions (humidity < 76%, temperature < 33°C, soil moisture > 59%).
    *   Relays are controlled based on temperature and soil moisture:
        *   Relay 1 and 2 control cooling mechanisms (fans) based on temperature.
        *   Relay 3 controls irrigation based on soil moisture.
5.  **Loop:** The process repeats continuously to ensure real-time monitoring.

## Code Structure
*   **Pin Definitions:** Constants for pin assignments.
*   **Sensor Setup:** DHT11 and OLED display initialization.
*   **Timing Variables:** For non-blocking LED blinking and screen switching.
*   **Sensor Values:** Variables to store sensor readings and LED states.
*   **Setup Function:** Initializes serial communication, sensors, relays, LEDs, and OLED display.
*   **Blinking LED Function:** Non-blocking function to blink LEDs.
*   **Relay Control Function:** Controls relays with optional delay.
*   **Display Function:** Updates the OLED display with sensor data.
*   **Loop Function:** Main program loop that reads sensors, processes data, and updates outputs.

