<div align="center">

# 🎮 C++ SFML Game Collection

### *Two complete arcade games built from scratch — no engine, just code.*

![C++](https://img.shields.io/badge/C++-17-00599C?style=for-the-badge&logo=cplusplus&logoColor=white)
![SFML](https://img.shields.io/badge/SFML-2.5-8CC445?style=for-the-badge&logo=sfml&logoColor=white)
![Platform](https://img.shields.io/badge/Platform-Windows%20%7C%20Linux-lightgrey?style=for-the-badge)
![Status](https://img.shields.io/badge/Status-Complete-brightgreen?style=for-the-badge)

<br/>

> Built as part of **Game Programming with C++ (CSE 3545)**
> Siksha 'O' Anusandhan University, ITER · Academic Year 2025–26

</div>

---

## 📦 What's Inside

| Game | Description | Controls |
|------|-------------|----------|
| 🌀 **Maze Runner Ultimate** | Tile-based maze navigation across 3 levels with health & timers | `WASD` + `R` |
| 🚗 **Car Racer** | Endless top-down car dodger with dynamic difficulty scaling | `← →` + `P` + `R` |

---

<br/>

# 🌀 Maze Runner Ultimate

<div align="center">

```
██████████
█S   █   █       S = You (red circle)
█ ██ █ █ █       E = Exit (green tile)
█    █ █ █       # = Wall (costs 1 HP)
████ █ █ █         = Open path
█      █E█
██████████
```

*Navigate. Survive. Escape.*

</div>

### 🎯 How to Play

- Move through the maze using **W A S D**
- Reach the **green exit tile** to advance to the next level
- Hitting a **wall costs 1 HP** — you only have **3**
- Complete all **3 levels** without dying to win

### 🗺️ Levels

```
Level 1 ░░░  10×7  grid  — Intro layout, few dead ends
Level 2 ░░░  12×7  grid  — Longer corridors, more branching
Level 3 ░░░  14×8  grid  — Dense maze, tight navigation required
```

### ⌨️ Controls

```
  W         ↑
A   D    ←  ·  →       R  →  Restart after Win / Loss
  S         ↓
```

### 📊 Live HUD

```
Level: 2   Health: ❤️ ❤️ ░
Level Time: 18 sec   Total Time: 43 sec
```

### 🔊 Sound Design

| Sound | When |
|-------|------|
| `move.wav` | Every successful step |
| `wall.wav` | Wall collision (HP lost) |
| `win.wav` | Exit reached |

### 🛠️ Build

```bash
g++ maze.cpp -o MazeRunner \
    -lsfml-graphics -lsfml-window \
    -lsfml-audio -lsfml-system

./MazeRunner
```

---

<br/>

# 🚗 Car Racer

<div align="center">

```
┌─────────────────────────┐
│  Score: 1850  Speed: 4  │
│                         │
│      🟡      🔴         │
│           |             │
│    🟡     |    🟡       │
│           |             │
│        🔴              │
│           |             │
│        🚗              │
└─────────────────────────┘
```

*How long can you survive?*

</div>

### 🎯 How to Play

- Dodge **5 types of enemy cars** spawning from the top
- Enemies get **faster and more frequent** every second
- Survive as long as possible — score = **100 pts/second**
- Crash into any enemy → **GAME OVER**

### 📈 Difficulty Curve

```
t = 0s   │ Speed ×1.0 │ 200–400 px/s  │ Spawn: 1.0s
t = 5s   │ Speed ×2.0 │ 400–800 px/s  │ Spawn: ~0.5s
t = 10s  │ Speed ×3.0 │ 600–1200 px/s │ Spawn: ~0.3s
t = 20s  │ Speed ×5.0 │ 1000–2000 px/s│ Spawn: 0.3s ← floor
```

> Speed multiplier grows at **+0.2× per second**. Spawn delay shrinks at **−0.1s per second**, floored at **0.3s**.

### ⌨️ Controls

```
←  →    Move car left / right
 P      Pause / Resume
 R      Restart after Game Over
 1      Easy mode
 2      Medium mode  (default)
 3      Hard mode
```

### 🚙 Enemy Fleet

| Sprite | Type | Trait |
|--------|------|-------|
| `RedCar1.png` | 🔴 Red | Primary enemy, all difficulties |
| `RedCar2.png` | 🔴 Red | Higher speed range |
| `YellowCar1.png` | 🟡 Yellow | Most common in Easy/Medium |
| `YellowCar2.png` | 🟡 Yellow | Medium speed |
| `YellowCar3.png` | 🟡 Yellow | Largest sprite, widest hitbox |

### 🔊 Audio

| Sound | When |
|-------|------|
| `bg.wav` | Looping background music throughout |
| `crash.wav` | On collision — one-shot |

### 🛠️ Build

```bash
g++ cardodge_game.cpp -o CarRacer \
    -lsfml-graphics -lsfml-window \
    -lsfml-audio -lsfml-system

./CarRacer
```

---

<br/>

## 🏗️ Tech Stack

```
Language  →  C++ 17
Graphics  →  SFML 2.5  (rendering, input, audio, windowing)
Compiler  →  GCC / MinGW  (g++ -std=c++17)
Editor    →  Visual Studio Code
OS        →  Windows 10 / Linux Ubuntu 22.04
```

## ⚙️ Prerequisites

```bash
# Ubuntu / Debian
sudo apt-get install libsfml-dev

# Windows — download SFML 2.5 from:
# https://www.sfml-dev.org/download.php
# Link: -lsfml-graphics -lsfml-window -lsfml-audio -lsfml-system
```

---

<br/>

## 🧠 Concepts Demonstrated

```
✅  OOP & Inheritance       Abstract Car base → PlayerCar / EnemyCar derived classes
✅  Polymorphism            Virtual update(dt) dispatched without type branching
✅  Delta-time Physics      Frame-rate-independent movement (speed × dt)
✅  Tile-based Design       String-array level layouts parsed at runtime
✅  Collision Detection     FloatRect::intersects() (Car) + tile equality (Maze)
✅  Game State Machine      Play → Pause → GameOver → Win with clean restart
✅  Dynamic Difficulty      Spawn compression + speed multiplier growth over time
✅  Audio Integration       SFML Sound (one-shot SFX) + Music (looping stream)
✅  Lambda Functions        loadLevel / startGame as captured lambdas
✅  STL Containers          vector<EnemyCar> managed with erase/remove_if idiom
```

---

<br/>

## 📁 Folder Structure

```
📦 sfml-game-collection/
 ┣ 📂 maze_runner/
 ┃ ┣ 📄 maze.cpp
 ┃ ┗ 📂 assets/
 ┃   ┣ 🔤 DejaVuSans.ttf
 ┃   ┣ 🔊 move.wav
 ┃   ┣ 🔊 wall.wav
 ┃   ┗ 🔊 win.wav
 ┃
 ┣ 📂 car_dodging/
 ┃ ┣ 📄 cardodge_game.cpp
 ┃ ┗ 📂 assets/
 ┃   ┣ 🖼️ WhiteCar.png
 ┃   ┣ 🖼️ RedCar1.png  /  RedCar2.png
 ┃   ┣ 🖼️ YellowCar1.png  /  YellowCar2.png  /  YellowCar3.png
 ┃   ┣ 🔤 KOMIKAP_.ttf
 ┃   ┣ 🔊 bg.wav
 ┃   ┗ 🔊 crash.wav
 ┃
 ┗ 📄 README.md
```

---

<br/>

<div align="center">

Made with ⚡ C++ and SFML

**[Satyam Kumar](https://github.com/Satyam5367)** · B.Tech CSE · SOA University ITER

</div>
