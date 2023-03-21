# mesh-viewer

![Alt text](/images/reps.gif?raw=true)

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

The viewing position can be roated by left-clicking and dragging the mouse aroudn the model, and the distance from the model can be increased and decreaed via the mouse scroll.

![Alt text](/images/move.gif?raw=true)

This viewer has many models that can be cycled through by pressing the 'n' key. The previous model can be accessed by pressing the 'p' key.

![Alt text](/images/cycle.gif?raw=true) 

This veiwer has a 5 shaders that can be cycled through by pressing the 's' key. The normal shader, a vertex phong shader, a pixel phong shader, a cortoon shader, and a blue gradient shader.

![Alt text](/images/shaders.gif?raw=true)

The position of the light can be altered by pressing the arrow keys.

![Alt text](/images/light.gif?raw=true) 

## Unique features 

Thermal shader 

![Alt text](/images/thermal.gif?raw=true)

Toon shader 

![Alt text](/images/toon.gif?raw=true) 

Moving the light source 

![Alt text](/images/light.gif?raw=true) 

Cycle through material colors 

![Alt text](/images/col.gif?raw=true) 
<!-- Cycle through light colors ![Alt text](/images/reps.gif?raw=true) -->
