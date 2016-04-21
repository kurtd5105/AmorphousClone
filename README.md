# AmorphousClone
Amorphous Plus being recreated in C++. It is intended to be similar to the old flash game, however it may not be exactly how you remember it when complete.

## Compiling
- Requires Visual Studio 2013.
  - Set AmorphousClone as the startup project, it should build GameEngine and AC and then run.
- Requires SDL 2, SDL 2 ttf, Glew.
  - Place under `dependencies/include/*.h` and `dependences/lib/[Debug or Release]/*.lib`  
- Requires arial.ttf from user's computer to be in the **game's** Fonts folder to run (`AmorphousClone/Fonts/` if running in visual studio, otherwise in a folder named Fonts inside the directory with the game).
