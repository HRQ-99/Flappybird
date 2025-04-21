## Flappybird
This is a simple clone of the popular game 'Flappybird'. This is written with Godot - 4.4(.1) using GDExtension in C++.
I am planning on documenting this project, after I am done with it. 

## Contents
- godot-cpp (-b 4.4) repo as a sub-module
- The game project
- include directory for project headers
- src directory for the code
- SCons (requires python) file for building

## Things to know
1. I am not particulary familiar with neither Godot nor C++. As such there might be things that are sub-optimal or too convoluted unnecessarily.

2. There is a binary release, if you want to play or you can compile this project, using SCons(compiling takes a few mintutes coz of godot-cpp).

3. By default, if `scons` command is used, your current platform is used for building. Can specify using `platform=<OS>`.

Find more info, and see the example on Godot online documentation.
[GDExtension(C++) - docs](https://docs.godotengine.org/en/stable/tutorials/scripting/gdextension/gdextension_cpp_example.html)
