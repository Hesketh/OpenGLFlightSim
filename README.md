# Graphics 2
Created for my Graphics 2 module during my second year at the University of Derby. Features a simple 3D flight simulator where you fly around a customly lit and rendered environment.

![Flying Screenshot](https://raw.githubusercontent.com/Hesketh/OpenGLFlightSim/master/screenshots/flying.png)

Custom loading of .OBJ model are brought into the scene and rendered using a custom lit shader. A custom skybox shader is also used to give the illusion of the scene being a large expanse.

![Coin Screenshot](https://raw.githubusercontent.com/Hesketh/OpenGLFlightSim/master/screenshots/coins.png)

To make this renderer slightly more exciting to look at I added a slight game element. Around the scene are 8 golden coins that need collecting by driving the plane into them. Using a simple Axis-Aligned Bounding Box algorithm I check for collisions each frame. (A more advanced example of my collision detection and resoltion skills can be found [in my Game Behaviour project](https://github.com/Hesketh/GameBehaviour))