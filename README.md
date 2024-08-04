# Speed Monitoring and Alert System

## Description

This project uses an ESP32 and rotary encoder to monitor vehicle speed. It calculates revolutions per second (RPS) based on wheel rotations and activates an LED if the speed exceeds predefined limits. Alerts are also sent to the serial monitor when limits are breached.

## Features

- **Speed Measurement:** Measures wheel speed using a rotary encoder.
- **Speed Limits:** Checks if the speed exceeds maximum allowed or additional thresholds.
- **LED Indicator:** Lights up to signal when speed limits are exceeded.
- **Serial Output:** Provides feedback on speed limits and alerts.

## Components Used

- **ESP32 Microcontroller**
- **Rotary Encoder (CLK and DT pins)**
- **LED**

## Code Overview

- **Definitions and Constants:**
  - `CLK_PIN`: Encoder clock pin.
  - `DT_PIN`: Encoder data pin.
  - `LED_PIN`: LED indicator pin.
  - `WHEEL_CIRCUMFERENCE`: Wheel circumference in meters.
  - `INACTIVITY_TIMEOUT`: Timeout before turning off the LED if no speed change is detected.
  - `MAX_SPEED_KMH`: Maximum allowed speed in km/h.
  - `SPEED_OVER_LIMIT`: Additional speed limit in km/h.

- **Functions:**
  - `handleEncoder()`: ISR to calculate RPS.
  - `setup()`: Initializes serial communication and calculates RPS limits.
  - `loop()`: Checks speed and controls the LED.
## Wokwi Simulation
You can view and interact with the simulation of this project on Wokwi: [Temperature Alert System Simulation](https://wokwi.com/projects/404388578889858049)
