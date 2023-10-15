# Painter.IO 💻

Experience an action packed game with Painter.IO. 

Dive into the colorful world of paintball, where players can buy equipment, engage in battles and strategically build their inventory to beat opponents.

---

## Table of Contents
- [Features](#features)
- [Installation](#installation)
- [Feedback](#feedback)

---

## Features

- **Open-world Environment**: Explore a vast, detailed world filled with strategic positions and surprises.
- **Player Functionality**:
  - **Collectables**: Acquire new equipment and tools to strengthen your player.
  - **Battling**: Engage in dynamic paintball combats, challenging both your reflexes and strategy.
  - **Inventory Management**: Strategically build and manage your inventory for an edge over opponents.
- **Beta Testing Adjustments**: We value player feedback. Post our beta-testing phase, we've incorporated numerous suggestions leading to crucial game design adjustments.

---

## Installation 

Once you have cloned the repository, utilise the make file with `make run` function. 

```cpp
default: main.cpp $(wildcard $(INCLUDE_PATH)/*.cpp)
	g++ -g0 $(CXXFLAGS) $(CPPFLAGS) $(LDFLAGS) main.cpp Implementations/HardBot.cpp Implementations/BotBehaviour.cpp Implementations/Ammo.cpp Implementations/Bullet.cpp Implementations/Collectable.cpp Implementations/Common.cpp Implementations/EasyBot.cpp Implementations/Game.cpp Implementations/Gun.cpp Implementations/Health.cpp Implementations/Object.cpp Implementations/Person.cpp Implementations/Player.cpp Implementations/tileFeature.cpp Implementations/Welcome.cpp Implementations/tileMap.cpp -o painter.IO

run: main.cpp $(wildcard $(INCLUDE_PATH)/*.cpp)
	make default
	./painter.IO

leak: main.cpp $(wildcard $(INCLUDE_PATH)/*.cpp)
	g++ -g3 $(CXXFLAGS) $(CPPFLAGS) $(LDFLAGS) main.cpp Implementations/HardBot.cpp Implementations/BotBehaviour.cpp Implementations/Ammo.cpp Implementations/Bullet.cpp Implementations/Collectable.cpp Implementations/Common.cpp Implementations/EasyBot.cpp Implementations/Game.cpp Implementations/Gun.cpp Implementations/Health.cpp Implementations/Object.cpp Implementations/Person.cpp Implementations/Player.cpp Implementations/tileFeature.cpp Implementations/tileMap.cpp -o painter.IO
	leaks --atExit -- ./painter.IO
```

...
<img src="https://github.com/vas-byte/Painter.IO/blob/49c5247586205f34c05b9201d8b917b0742f50e8/Assets/transparent.png" align="left" height="220px" hspace="20px" vspace="10px">

For every player action within the game, Painter.IO ensures optimized performance and response. 

If a particular in-game element is not user-controlled — for example, _if it's a system-generated NPC_ — the game logic takes  care in determining its behavior and interactions.



<div style="clear: both;"></div>


<br><br>


---


## Feedback
Not applicable as the game is under development.

---

