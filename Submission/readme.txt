==How to operate==
Use the UP and DOWN arrows to accelerate and decelerate the forward camera motion.
Use SPACE to stop all forward motion.
Use the LEFT and RIGHT arrows to rotate the camera.
Use the PAGE UP and PAGE DOWN keys to raise or lower the camera.
Use P to move to the location where the screenshot was taken.
Use T to run the tour.
Use E to exit the tour.
Use ESC or Q to exit the program.
The mouse is not used.
Currently the landscape takes a long time to load. Apologies for this.


==Files==
===Top folder===
Camera.cpp - Source for the camera class
Camera.h - Camera header
credits.txt - Attributions
main.cpp - Main method
Model.cpp - Source for the model class
Model.h - Model header
objshader.frag - Fragment shader for world elements
objshader.vert - Vertex shader
readme.txt - This document
screenshot.jpg - Screenshot of interesting location
skyshader.frag - Fragment shader for skybox

===models===
beacon1.obj - Beacon on beam
beacon2.obj
beacon3.obj
beacon4.obj
beam1.obj - Beam across struts
beam2.obj
ceiling1.obj - Ceiling of skybox
dome1.obj - Geodesic dome
dome2.obj
dome3.obj
landingpad1.obj - Landing pad for ship
landingpad2.obj
landingpad3.obj
landingpad4.obj
landscape.obj - Terrain model
panelsupport1.obj - Strut for solar panel
panelsupport2.obj
ship1.obj - Spaceship
ship2.obj
ship3.obj
ship4.obj
skybox1.obj - Skybox wall
skybox2.obj
skybox3.obj
skybox4.obj
solarpanel1.obj - Solar panel
solarpanel2.obj
strut1.obj - Strut supporting beam and beacons
strut2.obj
strut3.obj
strut4.obj
walkway1.obj - Walkway between domes
walkway2.obj

===textures===
beacon.tga - Beacon texture
ceiling.tga - Skybox ceiling texture
dome.tga - Geodesic dome texture
landingpad.tga - Landing pad texture
mars.tga - Terrain texture
ship.tga - Spaceship texture
sky512.tga - Skybox wall with sun texture
skyempty512.tga - Skybox wall without sun texture
strut.tga - Strut and beam texture
sunbattery.tga - Solar panel texture


==Building==
Build with standard options, including OpenGL, GLM, GLFW and GLEW.


==How it works==
Obj files are parsed for vertices, uv coords and normals, and loaded into vbos, which are then referenced by vaos. These vaos are drawn out each render tick. Textures are loaded through GLFW and drawn onto each model in each render tick. Animation is achieved by monitoring the status of each ship and updating its model matrix each render tick.


==Inspiration==
Understanding of texturing and some relevant code from http://www.opengl-tutorial.org/beginners-tutorials/.
Some code used from module tutorials.
Shaders based on tutorial code.