# Morse Code Hand Detection with LCD Output

## Overview
This project detects hand landmarks using MediaPipe and OpenCV, and interfaces with an external microcontroller. It processes hand gestures, translates them into Morse code and text, and sends this data via a Serial connection to an Arduino. The Arduino then presents the results in real-time on a 16x2 LCD screen.

## Hardware Requirements
*   Arduino-compatible microcontroller.
*   16x2 Liquid Crystal Display (LCD).
*   **LCD Wiring:** Data and control pins connected to Arduino digital pins 12, 11, 5, 4, 3, and 2.
*   **Contrast Control:** LCD contrast pin connected to PWM-enabled pin 6.

## Software Dependencies
*   **Python Libraries:** `opencv-python` (`cv2`), `numpy`, `matplotlib`, `mediapipe` (Vision tasks), and `pyserial`.
*   **Arduino Libraries:** `<LiquidCrystal.h>`.

## System Architecture

### 1. Computer Vision & Processing (Python)
*   **Landmark Extraction:** The Python script reads an input image, converts it to RGB format, and utilizes MediaPipe to extract 21 specific hand landmarks, ranging from the wrist to the finger tips.
*   **Visualization:** A custom `draw_landmarks_on_image` function uses OpenCV drawing utilities to render the hand skeleton with specific color groupings and connecting lines. The resulting image is plotted using Matplotlib.
*   **Serial Transmission:** The system initializes a serial connection on `COM3` at a `9600` baud rate to send the processed data to the Arduino. 

### 2. Hardware Display (C++/Arduino)
*   **Initialization:** The Arduino sets up the 16x2 LCD and configures the contrast using an analog write value of 110 on pin 6.
*   **Data Parsing:** The board reads incoming serial data at a `9600` baud rate, expecting a string formatted with a `|` delimiter (e.g., `MorsePart|TextPart`).
*   **Screen Updates:** The parsed Morse code is printed on the first row (starting at cursor position 7), and the translated text is printed on the second row (starting at cursor position 6). 
*   **Text Formatting:** To maintain screen clarity, the Arduino pads the output with spaces to overwrite old characters and ensures the text part does not exceed 10 characters by slicing the end of the string.
