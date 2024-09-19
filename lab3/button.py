import sys
import RPi.GPIO as GPIO # Import Raspberry Pi GPIO library
import time

GPIO.setwarnings(False) # Ignore warning for now
GPIO.setmode(GPIO.BOARD) # Use physical pin numbering
GPIO.setup(10, GPIO.IN, pull_up_down=GPIO.PUD_DOWN) # Set pin 10 to be an input pin and set initial value to be pulled low (off)

last = GPIO.LOW
n = 0
while True: # Run forever
    if GPIO.input(10) == GPIO.HIGH and GPIO.input(10) != last:
        last = GPIO.input(10)
        print("Button was pushed! " + str(n))
        time.sleep(0.05)
        n += 1


GPIO.cleanup() # Clean up
