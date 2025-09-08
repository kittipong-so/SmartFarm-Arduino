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
*   Breadboard (optional, if used for prototyping)
*   Power Supply for Arduino

### Software:
*   Arduino IDE
*   Libraries:
    *   `DHT sensor library` (for DHT11)
    *   `Adafruit GFX Library` (for OLED)
    *   `Adafruit SSD1306 Library` (for OLED)
