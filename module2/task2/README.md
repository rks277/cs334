# cs334-submarine
This is the repository for project 2 of CS334. 

Welcome to the **Submarine Tracker** game! This is a Python game created using Pygame that simulates a submarine exploring the ocean depths, searching for treasure. The game is controlled via an ESP32 connected to joysticks, buttons, and LEDs, and the submarine's position and state are sent via serial communication.

The goal of the game is to navigate the submarine to find hidden underwater treasure, while encountering various game states such as a tutorial screen, winning and losing screens based on gameplay outcomes.

## Features

- **Joystick-Controlled Submarine**: Use the ESP32-connected joysticks for each player's controler to control the submarine's movement along the X, Y, and Z axes.
- **Treasure Hunt**: Find the treasure hidden somewhere on the ocean floor. The submarine's current coordinates and the treasure's coordinates are displayed.
- **Visual Cues**: The submarine's appearance and its surroundings are visually rendered, including a treasure and various game states.
- **Game States**: 
  - **Tutorial Mode**: Displays instructions on how to play the game.
  - **Win/Lose Mode**: Shows different backgrounds and messages depending on whether the player finds the treasure or not.
- **ESP32 and Arduino Integration**: The game receives input from an ESP32 device via serial communication, which reads joystick and button input and transmits the submarine's position and states to Pygame.

## Setup and Requirements

### Hardware:
- **ESP32**: Microcontroller that interfaces with Pygame via serial communication.
- **Joystick**: Used to control the submarine's X, Y, and Z axes.
- **Buttons, Switches, and LEDs**: Used for additional interaction and visual feedback.

### Software:
- **Python 3.7+**: Required to run the game code.
- **Pygame**: Library used for game rendering. Install via pip:
  ```bash
  pip install pygame

# 2. Game mechanics

At a high level, this is a collaborative, primarily two-player game. **Player 1** is in charge of controlling the submarine’s longitude and latitude using a joystick, switching the submarine on and off (ie. powering the game on and off). Player 1 also has a “grab treasure” button.

**Player 2** is in charge of navigating the submarine, and controlling its depth. The three by two matrix of LEDs on the left depict the depth (*surface, mid-depth, or deep-underwater*) of the treasure (gold/yellow LEDs) as well as the submarine (blue LEDs). On the top right, player 2 has a “radar” where the central LED (blue) blinks at a frequency proportional to the submarines current distance from the treasure. The LED on the top right (green) lights up when the *x-y-z* coordinates of the submarine are equal to those of the treasure. Player 2 also has a switch on the side of their controller which when flipped toggles between tutorial mode (where the treasure is known to be at the origin) and game mode (where the treasure is randomly placed at a lattice point in the grid [-100,100]X[-100,100]).

Additionally, there is a GUI display interface which shows the state of the game (tutorial, game, win, lose), and in game mode shows exactly where the treasure and the submarine is as well as their precise coordinates. This display is intended to be used in different ways depending on the game mode. When the submarine is at the same coordinates as the treasure, both players must press the button on their controller ***simultaneously*** to grab the treasure, and then if they were correct the game is either won or lost.

Below is a table outlining each control.

**Player 1 (Submarine Captain)**

| **Control** | **Function** | **Notes** |
| --- | --- | --- |
| Switch | Turns the game/submarine on/off | - |
| Joystick | Moves the *x-y* coordinates of the submarine | - |
| Button | When pressed simultaneously with player 2’s attempts to grab the treasure | - |

**Player 2 (Submarine Navigator)**

| **Control** | **Function** | **Notes** |
| --- | --- | --- |
| Switch | Toggles the game between tutorial mode and actual game mode | Location of treasure is randomized on boot, so toggle this switch with the game will switch to the *same* randomized treasure to avoid the game being too hard |
| Joystick | Moves the *z* coordinate of the submarine | The *x* axis of this joystick does not affect anything |
| Button | When pressed simultaneously with player 1’s attempts to grab the treasure | - |
| Blue column of LEDs | Displays the submarine’s current depth (*z* coordinate) | Either 0,1,2 |
| Yellow column of LEDs | Displays the treasure’s current depth (*z* coordinate) | Either 0,1,2 |
| Blue LED at the center of the radar | Blinks at a frequency proportional to the distance between the treasure and the submarine | - |
| Green LED at the top right | Turns on if the submarine is at the treasure | Very bright despite being connected to a large resistor! |