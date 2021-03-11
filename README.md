# SFML-Raycaster-Engine
A simple 2.5D Raycaster Engine using the SFML library, written in C++

Contains all .cpp and .h files needed, as well as a debug executable.


Classes Included:

Boundary - A line that rays will intersect with in order to draw walls in 3D space

BoxCollider - A collider using AABB collision; only supports rectangular or square shapes

CircleCollider - A circular collider; can colldier with box colliders using AABB collision, or other circle colliders using Cricle v Circle collision

Entity - Objects in the world that will be rendered, but may need more behaviour (e.g: enemies, pickups, ect)

Main - Root of the program

Player - Allows the user to move around the world; stores the RayParticle that renders the scene

Ray - A straight line that checks if it intersects with a boundary; can be infinite or finite

RayParticle - A class that fires all needed rays out, and then draws their hit results in 3D space

Scene - Handles everything that spawns in the level

TextureAtlas - Stores all needed textures for the given scene

VMath - A central Vector Math library

WorldProp - An Entity type that billboards towards the player
