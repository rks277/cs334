import pygame
import serial
import time

# Set up the serial communication (adjust the port and baud rate accordingly)
ser = serial.Serial('/dev/cu.usbserial-0001', 9600, timeout=1)

# Initialize Pygame
pygame.init()

# Get the current screen resolution for fullscreen
screen_info = pygame.display.Info()
screen_width, screen_height = screen_info.current_w, screen_info.current_h

# Set up the display to fullscreen
screen = pygame.display.set_mode((screen_width, screen_height), pygame.FULLSCREEN)
pygame.display.set_caption("Submarine Tracker")

# Colors
grey = (169, 169, 169)  # Grey color for the submarine body
rust = (183, 65, 14)  # Rusty metallic color for details
black = (0, 0, 0)
gold = (255, 215, 0)  # Gold color for the treasure
white = (255, 255, 255)
window_color = (200, 200, 255)  # Light blue for windows

# Load and set up the background images
game_background = pygame.image.load("background.jpg")  # Main game background
game_background = pygame.transform.scale(game_background, (screen_width, screen_height))

tutorial_background = pygame.image.load("tutorial_background.jpg")  # Tutorial screen background
tutorial_background = pygame.transform.scale(tutorial_background, (screen_width, screen_height))

win_background = pygame.image.load("win_background.jpg")  # Winning screen background
win_background = pygame.transform.scale(win_background, (screen_width, screen_height))

lose_background = pygame.image.load("lose_background.jpg")  # Losing screen background
lose_background = pygame.transform.scale(lose_background, (screen_width, screen_height))

# Submarine and treasure variables
submarine_x, submarine_y, submarine_z = 0, 0, 0
treasure_x, treasure_y, treasure_z = 0, 0, 0
off = False
ended = False

# Font for displaying coordinates
font = pygame.font.Font(None, 24)

def display_coords():
    """Display submarine and treasure coordinates in the top-right corner."""
    coords_text = f"Sub: ({submarine_x}, {submarine_y}, {submarine_z}) | Treasure: ({treasure_x}, {treasure_y}, {treasure_z})"
    text_surface = font.render(coords_text, True, black)
    screen.blit(text_surface, (screen_width - text_surface.get_width() - 10, 10))  # Top-right corner

# Main game loop
running = True
while running:
    # Check for Pygame events (like closing the window)
    for event in pygame.event.get():
        if event.type == pygame.QUIT:
            running = False

    # Read data from the serial port
    if ser.in_waiting > 0:
        try:
            # Read a line of serial data
            line = ser.readline().decode('utf-8').strip()
            data = line.split(',')

            # Parse x, y, z, tX, tY, tZ, off, ended values if valid data received
            if len(data) == 8:
                submarine_x = int(data[0])
                submarine_y = int(data[1])
                submarine_z = int(data[2])
                treasure_x = int(data[3])
                treasure_y = int(data[4])
                treasure_z = int(data[5])
                off = int(data[6])
                ended = int(data[7])
        except:
            pass  # Handle exceptions (like serial read errors)

    # Handle the "ended" state (end screen)
    if ended:
        if submarine_x == treasure_x and submarine_y == treasure_y and submarine_z == treasure_z:
            screen.blit(win_background, (0, 0))  # Display the win screen background
            result_text = font.render("You Won! You found the treasure!", True, (0, 255, 0))  # Green for success
        else:
            screen.blit(lose_background, (0, 0))  # Display the lose screen background
            result_text = font.render("You Lost! The treasure is elsewhere.", True, (255, 0, 0))  # Red for failure
        screen.blit(result_text, (screen_width // 2 - result_text.get_width() // 2, screen_height // 2))
        pygame.display.flip()
        continue

    # Handle the "off" state (tutorial screen)
    if off:
        screen.blit(tutorial_background, (0, 0))  # Display the tutorial screen background
        font = pygame.font.Font(None, 55)
        tutorial_text = font.render("Tutorial: Navigate to the treasure!", True, (255, 255, 255))
        screen.blit(tutorial_text, (screen_width // 2 - tutorial_text.get_width() // 2, screen_height // 2))
        pygame.display.flip()
        continue

    # Blit the game background image to the screen
    screen.blit(game_background, (0, 0))

    # Submarine dimensions
    sub_width = 80
    sub_height = 30

    # Calculate position (center submarine at the given x, y)
    sub_x = 3 * submarine_x + screen_width // 2
    sub_y = -3 * submarine_y + screen_height // 2

    # Draw the submarine body (main rectangle) in grey
    pygame.draw.rect(screen, grey, (sub_x, sub_y, sub_width, sub_height))

    # Draw the front of the submarine (circle for the nose) in grey
    pygame.draw.circle(screen, grey, (sub_x + sub_width, sub_y + sub_height // 2), sub_height // 2)

    # Draw the fin (small rectangle on top of the submarine) in rusty metallic color
    pygame.draw.rect(screen, rust, (sub_x + sub_width // 2, sub_y - sub_height // 2, sub_width // 4, sub_height // 3))

    # Draw the tail fin (small triangle at the back) in rusty metallic color
    pygame.draw.polygon(screen, rust, [(sub_x, sub_y + sub_height // 2),
                                        (sub_x - 10, sub_y + sub_height // 4),
                                        (sub_x - 10, sub_y + 3 * sub_height // 4)])

    # Draw the windows (small circles along the body)
    window_radius = 5  # Radius of the windows
    window_positions = [sub_x + sub_width // 4, sub_x + sub_width // 2, sub_x + 3 * sub_width // 4]  # Positions of windows
    for pos in window_positions:
        pygame.draw.circle(screen, window_color, (int(pos), sub_y + sub_height // 2), window_radius)

    # Draw the treasure as a gold ball
    treasure_screen_x = 3 * treasure_x + screen_width // 2
    treasure_screen_y = -3 * treasure_y + screen_height // 2
    pygame.draw.circle(screen, gold, (treasure_screen_x, treasure_screen_y), 10)  # Treasure size

    # Display submarine and treasure coordinates in the top-right corner
    display_coords()

    # Update the display
    pygame.display.flip()

    # Delay to control frame rate
    time.sleep(0.05)

# Close the serial connection and quit Pygame
ser.close()
pygame.quit()
