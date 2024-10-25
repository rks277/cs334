import socket
import pygame
import sys

# Wi-Fi server configuration
HOST = '0.0.0.0'  # Listen on all available interfaces
PORT = 80  # Same port as the ESP32 server

# Initialize pygame
pygame.init()
screen = pygame.display.set_mode((600, 400))
pygame.display.set_caption('ESP32 Sensor Data Display')
font = pygame.font.SysFont(None, 36)

# Initialize colors
WHITE = (255, 255, 255)
BLACK = (0, 0, 0)

# Initialize sensor values
photoresistor_value = 0
touch_value = 0

# Function to draw the sensor values on the screen
def draw_sensor_data(photoresistor, touch):
    screen.fill(WHITE)
    photo_text = font.render(f'Photoresistor: {photoresistor}', True, BLACK)
    touch_text = font.render(f'Touch Sensor: {touch}', True, BLACK)
    
    screen.blit(photo_text, (50, 150))
    screen.blit(touch_text, (50, 200))
    pygame.display.flip()

# Create a TCP/IP socket
sock = socket.socket(socket.AF_INET, socket.SOCK_STREAM)

# Bind the socket to the host and port
sock.bind((HOST, PORT))

# Listen for incoming connections
sock.listen(1)
print(f'Server listening on port {PORT}...')

try:
    while True:
        # Handle pygame events
        for event in pygame.event.get():
            if event.type == pygame.QUIT:
                pygame.quit()
                sys.exit()

        # Wait for a connection
        connection, client_address = sock.accept()
        try:
            print(f'Connection from {client_address}')

            # Receive the data in small chunks
            data = connection.recv(1024)
            if data:
                # Decode and parse the received sensor data
                data_str = data.decode('utf-8')
                print(f'Received: {data_str}')
                
                # Extract photoresistor and touch sensor values from the string
                try:
                    parts = data_str.split(',')
                    photoresistor_value = parts[0].split(':')[-1].strip()
                    touch_value = parts[1].split(':')[-1].strip()
                except IndexError:
                    pass

                # Update the pygame display with the received sensor values
                draw_sensor_data(photoresistor_value, touch_value)

        finally:
            # Clean up the connection
            connection.close()

except KeyboardInterrupt:
    print("Server is shutting down...")
finally:
    sock.close()
