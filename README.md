# Acoustic Guitar Tuner

## Overview
This project is an acoustic guitar tuner designed to assist both professional musicians and beginners who may not yet have a trained ear. The device listens to the sound of plucked guitar strings and, based on how close the sound is to the correct pitch, provides instructions on an LCD screen to guide the user in tuning their guitar. The tuner is simple to use and starts functioning immediately when connected to a power source.

## How It Works
The tuner is based on the Arduino Uno microcontroller, which captures sound from the environment and analyzes it using the Fast Fourier Transform (FFT) algorithm to determine the sound wave frequency. The detected frequency is then compared to predefined values corresponding to standard guitar notes, and feedback is displayed on the LCD screen.

### Key Steps in Operation:
1. The device captures ambient sound using a microphone.
2. A series of samples are collected and processed using FFT.
3. The dominant frequency is extracted and compared with reference values.
4. The system determines which guitar string is being tuned.
5. Feedback is provided via an LCD display and LED indicators:
   - **Red LEDs** indicate whether the pitch is too high or too low.
   - **A green LED** signals correct tuning.

## Components Used
- **Arduino UNO R3** (microcontroller)
- **Sound Sensor** (microphone module)
- **LCD Display 16x2** (visual feedback)
- **3 LEDs** (2 red, 1 green for tuning indicators)
- **3 Resistors (220Ω)** (for LED protection)
- **2 Resistors (1kΩ)** (for additional circuitry adjustments)

## Frequency Mapping
| String | Frequency Range (Hz) | Correct Frequency (Hz) |
|--------|----------------------|------------------------|
| **E (Low)**  | 62 - 102  | 83  |
| **A**       | 100 - 120 | 110 |
| **D**       | 120 - 165 | 147 |
| **G**       | 165 - 210 | 196 |
| **B**       | 210 - 290 | 247 |
| **E (High)** | 290 - 380 | 330 |

## Usage Instructions
1. Connect the tuner to a power source.
2. Pluck a guitar string.
3. Observe the LCD display and LED indicators:
   - If a **red LED** lights up, adjust the string accordingly.
   - When the **green LED** lights up, the string is correctly tuned.
4. Repeat for all strings.
