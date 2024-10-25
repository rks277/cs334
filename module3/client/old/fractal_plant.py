import pygame
from math import cos, sin, radians
import time

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

# Get color based on time (hue variation over time)
def get_color(elapsed_time, angle):
    hue_shift = (elapsed_time * 50) % 360  # Cycle through hue values over time
    red = (230 + hue_shift) % 255
    green = (150 - (0.4 * abs(angle) + hue_shift) % 150) % 255
    blue = (hue_shift + 100) % 255
    return red, green, blue

# Create a surface for drawing leaves with opacity
def draw_leaf(screen, pos, opacity, light_level):
    leaf_surface = pygame.Surface((10, 10), pygame.SRCALPHA)  # Create a transparent surface
    if light_level > 80:
        # Translucent brown leaves when the light is too high (scorched leaves)
        pygame.draw.circle(leaf_surface, (139, 69, 19, opacity), (5, 5), 5)  # Scorched brown leaves
    else:
        # Normal green leaves
        pygame.draw.circle(leaf_surface, (34, 139, 34, opacity), (5, 5), 5)  # Green leaves with transparency
    screen.blit(leaf_surface, (pos[0] - 5, pos[1] - 5))  # Blit the surface onto the screen

# Draw the L-system branches and calculate leaf positions dynamically
def draw_lsystem(screen, s, start_pos, unit, angle_step, elapsed_time, leaf_opacity, angle_offset, light_level):
    pos = start_pos
    angle = -70 + angle_offset
    stack = []
    leaves = []  # To store leaf positions

    for char in s:
        if char == 'F':  # Move forward and draw a line
            dx = cos(radians(angle)) * unit
            dy = sin(radians(angle)) * unit
            new_pos = (pos[0] + dx, pos[1] + dy)
            color = get_color(elapsed_time, angle)  # Get changing color
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
    
    # Draw the leaves with the given opacity and based on light level
    for leaf in leaves:
        draw_leaf(screen, leaf, leaf_opacity, light_level)

# Main function to initialize and run the Pygame window
def main():
    pygame.init()
    dim = (1000, 780)
    screen = pygame.display.set_mode(dim)

    s = generate_string(7)
    start_time = time.time()  # Record the start time
    leaf_opacity = 200  # Set initial opacity for the leaves

    angle_offset = 0  # Variable to adjust the angle of the entire tree
    angle_step = 20

    light_level = 50  # Initial light level (0-100 range)
    water_level = 50  # Initial water level (0-100 range)

    while True:
        screen.fill((255, 255, 255))  # Clear the screen

        # Calculate elapsed time
        elapsed_time = time.time() - start_time

        # Decay light and water levels over time
        light_level = max(0, light_level - 0.05)  # Light fades gradually
        water_level = max(0, water_level - 0.05)  # Water fades gradually

        # Handle key inputs
        keys = pygame.key.get_pressed()
        if keys[pygame.K_SPACE]:
            angle_step += 1  # Increase the angle step when spacebar is pressed

        if keys[pygame.K_l]:  # Press 'L' to increase light
            light_level = min(100, light_level + 2)

        if keys[pygame.K_w]:  # Press 'W' to increase water
            water_level = min(100, water_level + 2)

        # If light is too low, reduce leaf opacity (leaves "fall off")
        if light_level < 20:
            leaf_opacity = max(leaf_opacity - 5, 0)
        elif light_level > 80:
            leaf_opacity = 150  # Leaves become translucent brown but not fully transparent
        else:
            leaf_opacity = min(leaf_opacity + 1, 200)  # Recover opacity if light is good

        # Plant wilts if the water level is too low
        if water_level < 80:
            leaf_opacity = max(leaf_opacity - 10, 0)  # Reduce opacity faster if no water
            angle_step += 0.1  # Cause tree to wilt
        else:
            if angle_step > 20:
                angle_step -= 1 # Plant grows back if water added

        # Handle angle adjustment for the entire tree
        if keys[pygame.K_LEFT]:
            angle_offset -= 2  # Rotate tree left
        if keys[pygame.K_RIGHT]:
            angle_offset += 2  # Rotate tree right

        # Draw the branches and the leaves dynamically
        draw_lsystem(screen, s, (dim[0] / 2 - 200, dim[1]), 2.5, min(angle_step, 90), elapsed_time, leaf_opacity, angle_offset, light_level)

        # Display the light and water levels
        font = pygame.font.SysFont(None, 30)
        light_text = font.render(f'Light Level: {int(light_level)}', True, (0, 0, 0))
        water_text = font.render(f'Water Level: {int(water_level)}', True, (0, 0, 0))
        screen.blit(light_text, (10, 10))
        screen.blit(water_text, (10, 40))

        pygame.display.flip()  # Refresh the display

        # Event handling to close the window
        for event in pygame.event.get():
            if event.type == pygame.QUIT or (event.type == pygame.KEYDOWN and event.key == pygame.K_ESCAPE):
                pygame.quit()
                return

if __name__ == '__main__':
    main()
