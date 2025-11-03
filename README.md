# Snake-game-for-arduino
Its a snake game, for only arduino uno R4 wifi. It includes a demo like in the retro games with an AI that plays the game. 
# Snake Game with AI Demo (Arduino UNO R4 WiFi)

**Made by Fearlessman1**

## Overview

This is a Snake game created specifically for the **Arduino UNO R4 WiFi**, featuring a built-in AI demo mode reminiscent of classic retro arcade attract screens.

On startup, the AI automatically plays the game, moving intelligently to collect food and increase its score.
After reaching a defined score limit, it ends the run intentionally and restarts the demo.

Press **Q** at any time to switch into **playable mode**, taking direct control of the snake.
If the player loses or presses **R**, the game gracefully returns to the demo mode with a transition animation.

## Features

* AI demo that plays autonomously in a loop
* Playable mode activated by pressing **Q**
* Animated transitions between modes
* Game over “X” animation
* Snake body self-collision detection
* Edge wrapping (snake reappears on the opposite side)
* Configurable speeds for both AI and playable modes

## Controls

| Key | Action                  |
| --- | ----------------------- |
| W   | Move Up                 |
| A   | Move Left               |
| S   | Move Down               |
| D   | Move Right              |
| Q   | Start the playable mode |
| R   | Return to demo mode     |

## Technical Details

* **Platform:** Arduino UNO R4 WiFi
* **Display:** Integrated 12×8 LED matrix
* **Baud rate:** 9600
* **Language:** C++ (Arduino)

## License

This project is distributed under a **Custom Personal Use License**.

### You are allowed to:

* Use the code for **personal and educational purposes**.
* Modify it privately for your own use.

### You are **not allowed to**:

* Redistribute, re-upload, or publish this project or its modified versions.
* Use it for **commercial**, **promotional**, or **monetized** purposes.
* Include it, in part or in whole, in other distributed works.

If you wish to reference or feature this project publicly, you must obtain explicit permission from the author.

---

## Author

**Fearlessman1**
