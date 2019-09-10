# Smashball

### About
- **Smashball** is fun physics-based mobile  game developed in C++ using [cocos2dx](https://cocos2d-x.org/) game engine
- [Box2d](https://box2d.org/) C++ physics engine is used for realistic physics simulation
- The objective of the game is to score as many points as possible in one minute by flicking the ball towards a target board. There are multiple stages with different kinds of boards and obstructions, so the optimal strategies would potentially change per stage (see demo below for the different objects implemented).
- Some features implemented:
    1. Implemented following different kinds of `Board`s:
        - `HingeBoard`
        - `SpikyBoard`
        - `StaticBoard`
    2. Implemented following different kinds of `Obstruction`s:
        - `RectangularObstruction`
        - `RectangularHingedObstruction`
        - `TriangularObstruction`
        - `TriangularHingedObstruction`
    3. Implemented `SpikeFixture` that can be attached to a  `SpikyBoard`
    4. Implemented a cool `Wormhole` that can teleport the ball between two locations!
- These objects are implemented in a clean class hierarchy so that the code that lays out levels is generic, and thus level prototyping is quick
- Following additional functionalities are also implemented:
    1. Pause/resume functionality
    2. Combo-multipliers
    3. Highscore saving per stage

### Demo
- Click on the image below to watch a video walkthrough on YouTube

[![Smashball Walkthrough](https://img.youtube.com/vi/vHljHNpq_Mg/0.jpg)](https://youtu.be/vHljHNpq_Mg)

### Repository structure
-  `Classes` contains the source code
-  `Resources` contains the assets/resources
    
### Installation
- [APK](https://drive.google.com/file/d/1GQ39zYNNVaLFEUTjpn9i_2CJ6hYS0ymM/view?usp=sharing)

### Screenshots
![1](Resources/screenshots/1.jpg "1")

![2](Resources/screenshots/2.jpg "2")

![3](Resources/screenshots/3.jpg "3")

![4](Resources/screenshots/4.jpg "4")

![5](Resources/screenshots/5.jpg "5")

![6](Resources/screenshots/6.jpg "6")

![7](Resources/screenshots/7.jpg "7")

![8](Resources/screenshots/8.jpg "8")

![9](Resources/screenshots/9.jpg "9")

![10](Resources/screenshots/10.jpg "10")

![11](Resources/screenshots/11.jpg "11")
