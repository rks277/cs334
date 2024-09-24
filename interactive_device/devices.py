import RPi.GPIO as GPIO
import time

GPIO.setmode(GPIO.BCM)

VRx_pin = 17
VRy_pin = 27
SW_pin = 23
button_pin = 22

GPIO.setup(VRx_pin, GPIO.IN, pull_up_down=GPIO.PUD_DOWN)
GPIO.setup(VRy_pin, GPIO.IN, pull_up_down=GPIO.PUD_DOWN)
GPIO.setup(SW_pin, GPIO.IN, pull_up_down=GPIO.PUD_UP)
GPIO.setup(button_pin, GPIO.IN, pull_up_down=GPIO.PUD_UP)

# Dictionaries
modes = [
    {"up": "Mode 1: Moving up", "left": "Mode 1: Moving left"},
    {"up": "Mode 2: Ascending", "left": "Mode 2: <--"},
    {"up": "Mode 3: ^^^", "left": "Mode 3: <<<"}
]

# Track the current mode (starting at 0)
current_mode = 0

# Variables to track previous states
prev_x_state = None
prev_y_state = None
prev_joy_button_state = None
prev_button_state = None

# Function to read the joystick states and print according to the current mode
def read_joystick():
    global prev_x_state, prev_y_state, prev_joy_button_state
    
    x_state = GPIO.input(VRx_pin)
    y_state = GPIO.input(VRy_pin)
    joy_button_state = GPIO.input(SW_pin)

    # Check X-axis state
    if x_state != prev_x_state:
        if x_state == GPIO.HIGH:
            print("---Joystick let go---")
        elif x_state == GPIO.LOW:
            print(modes[current_mode]["left"])
        prev_x_state = x_state

    # Check Y-axis state
    if y_state != prev_y_state:
        if y_state == GPIO.HIGH:
            print("---Joystick let go---")
        elif y_state == GPIO.LOW:
            print(modes[current_mode]["up"])
        prev_y_state = y_state

    # Check joystick button press
    if joy_button_state != prev_joy_button_state:
        if joy_button_state == GPIO.LOW:
            print("Joystick button pressed")
        prev_joy_button_state = joy_button_state

# Handle button press and modes
def check_button():
    global current_mode, prev_button_state
    
    button_state = GPIO.input(button_pin)

    if button_state != prev_button_state:
        if button_state == GPIO.LOW:
            # Cycle mod 3
            current_mode = (current_mode + 1) % 3
            print(f"Button pressed! Switching to mode {current_mode + 1}")
        prev_button_state = button_state

try:
    print("Powering Up!")
    time.sleep(3)
    while True:
        read_joystick()
        check_button()
        time.sleep(0.1)
except KeyboardInterrupt:
    GPIO.cleanup()