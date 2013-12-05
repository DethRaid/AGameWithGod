A GAME WITH GOD 
v not.yet.complete
David Dubois

CONTROLS:
WASD 		- move
RF 		- move up/down. Useful for staying on top of the terrain
Move mouse	- look around

Vertical looking is not supported. Strafing only moves one along the x-axis.

TO RUN THE GAME:
Open the "Release" folder and run "AGameWithGod.exe"

GAMEPLAY:
One cam move around the game world in all the axis. As one approaches the temple, the terrain
goes from a flat desert to a hilly meadow.

WORKING FEATURES:
-OBJ rendering
-GLSL shader rendering
-Texture mapping
-Terrain deformation
-Grass
-Movement (mostly)
-Looking (vertical looking will not be supported)

HALF-CODED FEATURES:
-Battles between humans and monsters
-Humans turning into monsters
-Terrain becoming a flat desert as one enters battles
-Shooting a projectile to attack
-Battle AI

UN-TOUCHED FEATURES:
-Terrain collision

COMPILING:
The code will only compile in Microsoft Visual Studio 2012. This is because of some 
compiler-specific #pragma directives and some C++ 11 features, like range-based for loops.
However, the code is provided for review.

One must also have the Glew.h file in one's include directory, as well as Glew.lib, OpenGL32.lib,
and GLU.lib in one's library directory.

Enjoy!