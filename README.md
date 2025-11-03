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

MIT License

Copyright (c) 2025 fearlessman1

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights 
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell 
copies of the Software, and to permit persons to whom the Software is furnished 
to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all 
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR 
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, 
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE 
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER 
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, 
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE 
SOFTWARE.

---

## Author

**Fearlessman1**
