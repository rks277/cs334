import socket
import pygame
from math import cos, sin, radians
import time
import random

# Replace with the ESP32 IP address
esp32_ip = "10.67.76.146"
port = 80

def receive_data():
    with socket.socket(socket.AF_INET, socket.SOCK_STREAM) as s:
        s.connect((esp32_ip, port))
        data = s.recv(1024)  # Receive data from ESP32
        return data.decode()

# L-system rules for string generation, including leaves (L)
def generate_string(iterations):
    s = ['X']
    rules = {
        'X': list('F-[[X]+X]+F[+FX]-X[L]'),  # Adding L for leaves at the end of branches
        'F': list('FF')                     # F expansion rule
    }

    for _ in range(iterations):
        new_s = []
        for char in s:
            new_s.extend(rules.get(char, [char]))
        s = new_s
    return s

# Get branch color based on the season
def get_branch_color(elapsed_time, angle, season):
    if season == 'winter':
        return (0, 0, 255)  # Blue branches in winter
    elif season == 'fall':
        return (139, 69, 19)  # Darker brown branches in fall
    elif season in ['spring', 'summer']:
        return (139, 69, 19)  # Brown branches for spring and summer
    else:
        # Default to brown if something unexpected happens
        return (139, 69, 19)

# Create a surface for drawing leaves with opacity and seasonal color logic
def draw_leaf(screen, pos, opacity, light_level, season, turn_brown=False):
    if opacity <= 0:
        return  # Don't draw the leaf if the opacity is 0

    leaf_surface = pygame.Surface((10, 10), pygame.SRCALPHA)  # Create a transparent surface
    
    if season == 'winter':
        return  # No leaves in winter (fully transparent)
    elif season == 'fall' or turn_brown:
        # Turn leaves brown (summer heat damage) or fall colors: emphasize red with occasional orange and yellow
        color = random.choice([(139, 69, 19), (205, 133, 63), (222, 184, 135)])  # Brownish shades
        pygame.draw.circle(leaf_surface, (*color, opacity), (5, 5), 5)
    elif season == 'spring':
        # Sparse cherry blossom colors (pink, purple, violet)
        if random.random() < 0.3:  # Sparse distribution (30% chance to draw a leaf)
            color = random.choice([(255, 182, 193), (219, 112, 147), (148, 0, 211)])  # Pink, purple, violet
            pygame.draw.circle(leaf_surface, (*color, opacity), (5, 5), 5)
    elif season == 'summer':
        # Randomized shades of green
        green_shade = random.randint(34, 139)  # Varying green shade
        pygame.draw.circle(leaf_surface, (0, green_shade, 0, opacity), (5, 5), 5)

    screen.blit(leaf_surface, (pos[0] - 5, pos[1] - 5))  # Blit the surface onto the screen

# Draw the L-system branches and calculate leaf positions dynamically
def draw_lsystem(screen, s, start_pos, unit, angle_step, elapsed_time, leaf_opacity, angle_offset, light_level, season, turn_brown=False):
    pos = start_pos
    angle = -70 + angle_offset
    stack = []
    leaves = []  # To store leaf positions

    for char in s:
        if char == 'F':  # Move forward and draw a line
            dx = cos(radians(angle)) * unit
            dy = sin(radians(angle)) * unit
            new_pos = (pos[0] + dx, pos[1] + dy)
            color = get_branch_color(elapsed_time, angle, season)  # Get branch color based on season
            pygame.draw.line(screen, color, pos, new_pos)
            pos = new_pos
        elif char == '+':
            angle += angle_step
        elif char == '-':
            angle -= angle_step
        elif char == '[':
            stack.append((pos, angle))
        elif char == ']':
            pos, angle = stack.pop()
        elif char == 'L':  # Store leaf positions
            leaves.append(pos)
    
    # Draw the leaves with the given opacity and based on light level and season
    for leaf in leaves:
        draw_leaf(screen, leaf, leaf_opacity, light_level, season, turn_brown)

# Function to switch to the next season
def switch_season(current_season):
    seasons = ['spring', 'summer', 'fall', 'winter']
    next_season = seasons[(seasons.index(current_season) + 1) % len(seasons)]
    return next_season

# Main function to initialize and run the Pygame window
def main():
    pygame.init()
    dim = (1000, 780)
    screen = pygame.display.set_mode(dim)

    s = generate_string(7)
    start_time = time.time()  # Record the start time
    season_start_time = time.time()  # Time tracker for season transitions
    light_over_90_start = None  # To track how long light has been over 90
    leaf_opacity = 200  # Set initial opacity for the leaves

    angle_offset = 0  # Variable to adjust the angle of the entire tree
    angle_step = 20

    light_level = 50  # Initial light level (0-100 range)
    water_level = 50  # Initial water level (0-100 range)

    season = 'spring'  # Set the current season
    season_duration = 20  # Season changes every 20 seconds
    turn_brown = False  # Variable to track if leaves should turn brown in summer due to high light

    while True:
        # Receive data from the ESP32
        try:
            data = receive_data()
            print("Received photoresistor | touch values:", data)
            light, water = map(int, data.split(' | '))
        except Exception as e:
            print("Failed to receive data:", e)

        screen.fill((255, 255, 255))  # Clear the screen

        # Calculate elapsed time
        elapsed_time = time.time() - start_time
        season_elapsed_time = time.time() - season_start_time

        # Switch season every 20 seconds
        if season_elapsed_time > season_duration:
            season = switch_season(season)
            season_start_time = time.time()  # Reset the timer for the new season
            light_over_90_start = None  # Reset the light over 90 timer for the new season
            turn_brown = False  # Reset the brown leaves for the new season

        # Calculate the remaining time until the next season
        time_remaining = max(0, season_duration - int(season_elapsed_time))

        # Decay light and water levels over time
        light_level = max(0, light_level - 0.05)  # Light fades gradually
        water_level = max(0, water_level - 0.05)  # Water fades gradually

        # Handle key inputs
        keys = pygame.key.get_pressed()
        if keys[pygame.K_SPACE]:
            angle_step += 1  # Increase the angle step when spacebar is pressed

        if light < 400:
            light_level = min(100, light_level + 0.5)
        elif light < 200:
            light_level = min(100, light_level + 2)
        elif light > 700:
            light_level = max(0, min(100, light_level - 2))

        water_level = min(100, water_level + 0.1 * (46 - water))

        # Track light over 90 for 10 seconds in summer
        if season == 'summer':
            if light_level > 90:
                if light_over_90_start is None:
                    light_over_90_start = time.time()  # Start the timer
                elif time.time() - light_over_90_start >= 10:
                    turn_brown = True  # Start turning leaves brown after 10 seconds of high light
            else:
                light_over_90_start = None  # Reset the timer if light goes below 90
                turn_brown = False  # Stop turning brown if light is no longer high

        # Leaf opacity fades in fall, and no leaves are drawn in winter
        if season == 'fall':
            leaf_opacity = max(leaf_opacity - (5 * season_elapsed_time / season_duration), 0)  # Gradually fade leaves in fall
        elif season == 'winter':
            leaf_opacity = 0  # No leaves in winter
        else:
            leaf_opacity = min(leaf_opacity + 1, 200)  # Normal opacity adjustments for other seasons

        if water_level < 80:
            leaf_opacity = max(leaf_opacity - 10, 0)
            angle_step += 0.1
        else:
            if angle_step > 20:
                angle_step -= 1

        if keys[pygame.K_LEFT]:
            angle_offset -= 2
        if keys[pygame.K_RIGHT]:
            angle_offset += 2

        # Draw the branches and the leaves dynamically based on the season
        draw_lsystem(screen, s, (dim[0] / 2 - 200, dim[1]), 2.5, min(angle_step, 90), elapsed_time, leaf_opacity, angle_offset, light_level, season, turn_brown)

        # Display the light and water levels
        font = pygame.font.SysFont(None, 30)
        light_text = font.render(f'Light Level: {int(light_level)}', True, (0, 0, 0))
        water_text = font.render(f'Water Level: {int(water_level)}', True, (0, 0, 0))
        season_text = font.render(f'Season: {season}', True, (0, 0, 0))
        timer_text = font.render(f'Time to next season: {time_remaining}s', True, (0, 0, 0))

        screen.blit(light_text, (10, 10))
        screen.blit(water_text, (10, 40))
        screen.blit(season_text, (10, 70))
        screen.blit(timer_text, (10, 100))

        pygame.display.flip()  # Refresh the display

        # Event handling to close the window
        for event in pygame.event.get():
            if event.type == pygame.QUIT or (event.type == pygame.KEYDOWN and event.key == pygame.K_ESCAPE):
                pygame.quit()
                return

if __name__ == "__main__":
    main()
