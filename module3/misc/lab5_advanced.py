import pygame
import socket
import numpy as np
import time

# Replace with the ESP32 IP address
esp32_ip = "10.67.76.146"
port = 80

# Function to receive data from ESP32
def receive_data():
    with socket.socket(socket.AF_INET, socket.SOCK_STREAM) as s:
        s.connect((esp32_ip, port))
        data = s.recv(1024)  # Receive data from ESP32
        return data.decode()

# Initialize Pygame
pygame.init()

# Define screen dimensions
WIDTH, HEIGHT = 800, 600
screen = pygame.display.set_mode((WIDTH, HEIGHT))
pygame.display.set_caption("Bouncing Wave Visualization")

# Set up some colors
WHITE = (255, 255, 255)
BLUE = (0, 0, 255)

# Parameters for the wave
x_vals = np.linspace(0, 2 * np.pi, WIDTH)  # Map x values across the screen width
wave_amplitude = 1  # Initial wave amplitude
frequency = 2  # Frequency of the wave
speed = 0.1  # Speed of the wave animation
offset = 0  # Offset for wave animation

# Main loop to run the Pygame window
running = True
while running:
    for event in pygame.event.get():
        if event.type == pygame.QUIT:
            running = False

    # Receive photoresistor data from ESP32
    try:
        data = receive_data().strip()
        photoresistor_value = float(data)
        # Normalize the value between 0 and 1 for the wave amplitude
        wave_amplitude = photoresistor_value / 4095.0  # Assuming 12-bit ADC
        wave_amplitude = min(max(wave_amplitude, 0), 1)  # Clamp to 0-1 range
    except (ValueError, socket.error):
        print("Failed to receive data or invalid data")

    # Update the offset for animation
    offset += speed

    # Clear the screen
    screen.fill(WHITE)

    # Generate the y values based on the current wave_amplitude and offset
    y_vals = wave_amplitude * np.sin(frequency * x_vals + offset) * (HEIGHT // 4) + (HEIGHT // 2)

    # Draw the wave
    for i in range(WIDTH - 1):
        pygame.draw.line(screen, BLUE, (i, y_vals[i]), (i + 1, y_vals[i + 1]), 2)

    # Update the display
    pygame.display.flip()

    # Control the frame rate
    time.sleep(0.05)

# Quit Pygame
pygame.quit()
