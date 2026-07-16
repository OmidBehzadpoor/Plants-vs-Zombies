# 🌻 Plants vs Zombies — BP Project
 
A fan-made clone of **Plants vs Zombies** built in **C** using the [raylib](https://www.raylib.com/) library.
 
---
 
## 📸 Screenshots
 
![Menu](screenshots/menu.png)
![Gameplay](screenshots/gameplay.png)
 
---
 
## 🎮 Features
 
- 4 playable levels
- Multiple plants: Peashooter, Sunflower, Chomper, Rose, Potato Mine
- Shop system to buy plants
- Level select screen
- Music player with in-game soundtrack
- Lawn mower defense mechanic
- GIF animation support
- Save system
---
 
## 🚀 Quick Start
 
> No build tools needed — just download and run.
 
1. Go to the [**Releases**](../../releases) page
2. Download the latest release
3. Extract the zip
4. Run `PlantsVsZombies.exe`
> **Note:** The `assets/` folder must stay in the **same directory** as the executable.
 
---
 
## 🛠️ Build from Source
 
This project uses **C** and **[raylib](https://www.raylib.com/)** and can be built on **Windows, Linux, and macOS**.
 
> **raylib is downloaded automatically** — you don't need to install it manually.  
> You only need **CMake ≥ 3.16**, a C compiler, and an internet connection for the first build.
 
### Prerequisites
 
| Platform | Requirements |
|----------|-------------|
| Windows  | [CMake](https://cmake.org/download/), [MinGW-w64](https://www.mingw-w64.org/) or MSVC |
| Linux    | `sudo apt install cmake gcc libx11-dev libxrandr-dev libxi-dev libxcursor-dev libxinerama-dev libgl1-mesa-dev` |
| macOS    | `brew install cmake` + Xcode Command Line Tools (`xcode-select --install`) |
 
### Step 1 — Clone the repo
 
```bash
git clone https://github.com/OmidBehzadpoor/Plants-vs-Zombies.git
cd Plants-vs-Zombies
```
 
### Step 2 — Build
 
**Windows (MinGW):**
 
```bash
mkdir build && cd build
cmake .. -G "MinGW Makefiles" -DCMAKE_BUILD_TYPE=Release
cmake --build .
```
 
**Windows (MSVC / Visual Studio):**
 
```bash
mkdir build && cd build
cmake ..
cmake --build . --config Release
```
 
**Linux / macOS:**
 
```bash
mkdir build && cd build
cmake .. -DCMAKE_BUILD_TYPE=Release
cmake --build .
```
 
### Step 3 — Run
 
The executable is placed in the `build/` folder. Asset paths are relative to the executable, so you **must run it from inside `build/`**:
 
```bash
cd build
./PlantsVsZombies        # Linux / macOS
PlantsVsZombies.exe      # Windows
```
 
> ⚠️ If you double-click the executable from a file manager it may not find the assets and crash. Always run it from the terminal inside the `build/` folder.
 
---
 
## 📁 Project Structure
 
```
Plants-vs-Zombies/
├── Source/          # All .c source files
│   ├── PlantsVsZombies.c   # Entry point (main)
│   ├── GameLoop.c          # Main game loop & screen state machine
│   ├── Level1–4.c          # Individual level logic
│   ├── Zombie.c / Plant.c  # Entity logic
│   ├── Shop.c              # Shop system
│   ├── menu.c              # Main menu
│   └── ...
├── include/         # Header files (.h)
├── assets/          # Textures, fonts, sounds, GIFs
├── Data/            # Save data & Windows icon resource
└── CMakeLists.txt
```
 
---
 
## 🧑‍💻 For Developers / Contributors
 
If you want to continue development, additional raw assets (fonts, images, GIFs, audio) are available in the **Developer Assets** pre-release:

👉 [Download Dev Assets](../../releases)
 
> Regular players do **not** need these files.

---
 
## 👨‍💻 Developers
 
- **Omid Behzadpoor** ([@OmidBehzadpoor](https://github.com/OmidBehzadpoor))
- *Amirkabir University of Technology (Tehran Polytechnic)*
