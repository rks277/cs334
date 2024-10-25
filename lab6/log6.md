We began by getting the ESP32 connected to wifi.

Connected to Yale wireless:
ssid = "yale wireless"
password = ""

We conected all the circuitry properly, and then flashed the code on the ESP32 to read this as an analog value.

We then set up the client on the computer and then were able to receive the photoresistance values. 

We then wrote code to plot the data using matplot. 

--- We ran into some issues installing matplot, one option would have been to create a new virtual environment
--- We used sudo apt install python3-pygame

Then everything worked nicely!
