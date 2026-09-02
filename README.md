# Morse Code Hand Detection with LCD Output

## Overview
This project detects hand landmarks using MediaPipe and OpenCV, and interfaces with an external microcontroller[cite: 2]. It processes hand gestures, translates them into Morse code and text, and sends this data via a Serial connection to an Arduino[cite: 2, 3]. The Arduino then presents the results in real-time on a 16x2 LCD screen[cite: 3].

## Hardware Requirements
*   Arduino-compatible microcontroller[cite: 3].
*   16x2 Liquid Crystal Display (LCD)[cite: 3].
*   **LCD Wiring:** Data and control pins connected to Arduino digital pins 12, 11, 5, 4, 3, and 2[cite: 3].
*   **Contrast Control:** LCD contrast pin connected to PWM-enabled pin 6[cite: 3].

## Software Dependencies
*   **Python Libraries:** `opencv-python` (`cv2`), `numpy`, `matplotlib`, `mediapipe` (Vision tasks), and `pyserial`[cite: 2].
*   **Arduino Libraries:** `<LiquidCrystal.h>`[cite: 3].

## System Architecture

### 1. Computer Vision & Processing (Python)
*   **Landmark Extraction:** The Python script reads an input image, converts it to RGB format, and utilizes MediaPipe to extract 21 specific hand landmarks, ranging from the wrist to the finger tips[cite: 2].
*   **Visualization:** A custom `draw_landmarks_on_image` function uses OpenCV drawing utilities to render the hand skeleton with specific color groupings and connecting lines[cite: 2]. The resulting image is plotted using Matplotlib[cite: 2].
*   **Serial Transmission:** The system initializes a serial connection on `COM3` at a `9600` baud rate to send the processed data to the Arduino[cite: 2]. 

### 2. Hardware Display (C++/Arduino)
*   **Initialization:** The Arduino sets up the 16x2 LCD and configures the contrast using an analog write value of 110 on pin 6[cite: 3].
*   **Data Parsing:** The board reads incoming serial data at a `9600` baud rate, expecting a string formatted with a `|` delimiter (e.g., `MorsePart|TextPart`)[cite: 3].
*   **Screen Updates:** The parsed Morse code is printed on the first row (starting at cursor position 7), and the translated text is printed on the second row (starting at cursor position 6)[cite: 3]. 
*   **Text Formatting:** To maintain screen clarity, the Arduino pads the output with spaces to overwrite old characters and ensures the text part does not exceed 10 characters by slicing the end of the string[cite: 3].
