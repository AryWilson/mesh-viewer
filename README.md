# mesh-viewer

Implements a simple PLY viewer

TODO: Add a representative image for your project here

## How to build

*Windows*

Open git bash to the directory containing this repository.

```
mesh-viewer $ mkdir build
mesh-viewer $ cd build
mesh-viewer/build $ cmake ..
mesh-viewer/build $ start mesh-viewer.sln
```

Your solution file should contain two projects: `mesh-viewer` and `test-ply-mesh`.
To run from the git bash command shell, 

```
mesh-viewer/build $ ../bin/Debug/test-ply-mesh.exe
mesh-viewer/build $ ../bin/Debug/mesh-viewer.exe
```

*macOS*

Open terminal to the directory containing this repository.

```
mesh-viewer $ mkdir build
mesh-viewer $ cd build
mesh-viewer/build $ cmake ..
mesh-viewer/build $ make
```

To run each program from build, you would type

```
mesh-viewer/build $ ../bin/mesh-viewer
```

## Demo of basic features

The viewing position can be roated by left-clicking and dragging the mouse aroudn the model.
(gif)
The distance from the model can be increased and decreaed via the mouse scroll.
(gif)
This viewer has many models that can be cycled through by pressing the 'n' key. The previous model can be accessed by pressing the 'p' key.
(gif)
This veiwer has a 5 shaders that can be cycled through by pressing the 's' key. The normal shader, a vertex phong shader, a pixel phong shader, a cortoon shader, and a blue gradient shader.
(gif)
The position of the light can be altered by pressing the arrow keys.
(gif)

## Unique features 

Blue shader (gif)
Toon shader (gif)
Moving the light source (gif)
Cycle through material colors (gif)
<!-- Cycle through light colors (gif) -->
