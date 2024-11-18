# tetris
A Tetris Clone

## Debug Compile (LINUX)
```
g++ -std=c++17 main.cpp constants.hpp block.cpp tetromino.cpp timer.cpp -Wall -lSDL2 -lSDL2_image -lSDL2_ttf -lSDL2_mixer -g -o ./bin/app.out
```