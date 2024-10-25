# Seasonal Tree Visualization with ESP32 Sensor Data

This project creates a **seasonal tree visualization** using Pygame that dynamically changes based on data received from an **ESP32** device. The ESP32 collects **photoresistor (light sensor)** and **touch sensor** data, which affect the growth, appearance, and seasonal changes of the tree.

The visualization reflects **real-time environmental changes**, including:
- Leaf colors and opacity based on the current season.
- Leaf damage or fading based on light intensity.
- Seasonal transitions (Spring, Summer, Fall, Winter).
- Water levels affecting plant growth and leaf opacity.

## Features

- **Seasons Representation**:
  - **Spring**: Sparse cherry blossom leaves (pink, purple, violet).
  - **Summer**: Lush green leaves with the possibility of leaves turning brown under high light.
  - **Fall**: Leaves change to red, orange, and yellow and gradually fade.
  - **Winter**: Tree without any leaves; branches turn blue.

- **ESP32 Integration**:
  - The ESP32 sends photoresistor and touch sensor data to Pygame.
  - Photoresistor values affect light levels.
  - Touch sensor values simulate water levels.

- **Real-Time Changes**:
  - As light levels increase or decrease, the leaves’ appearance changes.
  - Water levels influence leaf opacity and tree health (withering and growth).
  - The seasons automatically change over time, transitioning smoothly.

- **Real-Life Plant Watering**:
  - You actually pour watter into the water resevoir and the capacitave touch sensor detects the change in capacitance to record that the plant was watered.

## Table of Contents

- [Requirements](#requirements)
- [Setup Instructions](#setup-instructions)

## Requirements

1. **Hardware**:
   - ESP32 microcontroller with Wi-Fi capability.
   - **Photoresistor** (light sensor) connected to an analog pin.
   - **Touch sensor** connected to a digital pin.

2. **Software**:
   - **Python 3.x** installed on your system.
   - **Pygame** Python library (`pip install pygame`).
   - **Wi-Fi connection** for ESP32 and the computer running the Python script.

3. **Libraries**:
   - Pygame: Install via `pip install pygame`.

## Setup Instructions

### ESP32 Setup

1. Connect your photoresistor to the ESP32's analog pin (e.g., `GPIO 34`) and the touch sensor to a digital pin (e.g., `GPIO 4`).
2. Flash the provided ESP32 code to your ESP32 using the Arduino IDE or PlatformIO.
3. Connect your ESP32 to your Wi-Fi network by updating the Wi-Fi credentials in the ESP32 code.
4. The ESP32 will start sending light and touch sensor data to the Python visualization over Wi-Fi.

### Python Setup

1. **Ensure Required Libraries are Installed on the Raspberry Pi**:
   - Update your Raspberry Pi's package list and upgrade existing packages:
     ```bash
     sudo apt-get update
     sudo apt-get upgrade
     ```
   - Verify that Python 3 is installed:
     ```bash
     python3 --version
     ```
     - If Python 3 is not installed, install it:
       ```bash
       sudo apt-get install python3
       ```
   - Install `pip` for Python 3 if not already installed:
     ```bash
     sudo apt-get install python3-pip
     ```

2. **Install Pygame and Dependencies**:
   - Pygame may require additional packages on the Raspberry Pi due to its graphical nature.
   - Install the necessary SDL dependencies:
     ```bash
     sudo apt-get install libsdl-image1.2-dev libsdl-mixer1.2-dev libsdl-ttf2.0-dev \
                          libsmpeg-dev libportmidi-dev libavformat-dev libswscale-dev \
                          libfreetype6-dev libjpeg-dev
     ```
   - Install Pygame using `pip3`:
     ```bash
     pip3 install pygame
     ```
     - Alternatively, you can install Pygame through `apt-get`:
       ```bash
       sudo apt-get install python3-pygame
       ```

3. **Clone the Repository or Download the Files**:
   - Navigate to your desired directory and clone the repository:
     ```bash
     git clone https://github.com/your-repository/seasonal-tree-visualization.git
     cd seasonal-tree-visualization
     ```
     - If you don't have `git` installed:
       ```bash
       sudo apt-get install git
       ```
     - Or download the ZIP file from GitHub and extract it.

4. **Set the ESP32 IP Address**:
   - Open the Python script (`main.py`) in a text editor:
     ```bash
     nano main.py
     ```
   - Locate the line that sets the `esp32_ip` variable and replace `"your_esp32_ip_address"` with the actual IP address of your ESP32:
     ```python
     esp32_ip = "your_esp32_ip_address"
     ```
     - Save and exit the editor (`Ctrl+X`, then `Y`, then `Enter` in `nano`).

5. **Run the Pygame Visualization**:
   - Execute the Python script using Python 3:
     ```bash
     python3 main.py
     ```
   - The visualization should open in full-screen mode on your Raspberry Pi.

6. **Interacting with the Visualization**:
   - **Light Sensor**: Adjust the amount of light on the photoresistor to change the light level in the visualization.
   - **Watering Sensor**: Pour water on the touch sensor to simulate watering the tree.

7. **Exit the Visualization**:
   - Press the `ESC` key to exit the full-screen mode and close the program.
   - If the window does not close, you can press `Alt+F4` or switch to the terminal and press `Ctrl+C` to terminate the script.

8. **Auto-Start the Visualization on Boot**:
   - If you want the visualization to start automatically when the Raspberry Pi boots up, you can add a command to the `wayfire.ini` file or create a systemd service.
   - Edit `~/.config/wayfire.ini`:
     ```bash
    [autostart]
    autostart_wf_shell = false
    chromium = python path/to/project
     ```

**Note**: Ensure that your Raspberry Pi and ESP32 are connected to the same Wi-Fi network for the socket communication to work properly.

