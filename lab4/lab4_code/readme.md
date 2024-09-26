### Lab 4 Log

#### Print mac address

1. Install esp32 by Espressif Systems through boards manager
2. Select ESP32 Dev Module through tools -> board
3. Copy paste the mac address code from lab instructions
4. Verify and upload

#### Getting Joystick/Button/Switch Output

5. Flash code from https://sankios.imediabank.com/2-axis-joystick to ESP32
6. Connect pins from joystick to ESP32 using female-to-female
7. ESP32 naming is weird (checkout https://www.reddit.com/r/microcontrollers/comments/12l1356/esp32arduino_core_how_do_i_know_which_arduino/)
8. Change the variables in the program to match the GPIO number of the pins we used (there's a pinout map on the notion)
9. Remember to plug in the power (5V)
10. Also re-flash every time you change code
11. Joystick was being weird and doesn't center at half way value between extremes (i.e. \[0, 4095\] and half way is something like 2900)
12. Tried to solve by moving from 5V to 3.3V, didn't work
13. Tried to connect directly to the ESP32
14. Tried to use different GPIO pins and didn't work
15. Reset to step 11 and added button/switch support
16. Successfully got button input, no switch input tho
17. Isolated problem to defective wires, switched out the button for the switch and got digital input.
