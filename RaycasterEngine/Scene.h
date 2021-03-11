#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <vector>

#include "Boundary.h"
#include "Ray.h"
#include "Player.h"
#include "TextureAtlas.h"
#include "BoxCollider.h"
#include "CircleCollider.h"
#include "Entity.h"
#include "WorldProp.h"

#pragma once
class Scene
{
public:
	Scene(sf::RenderWindow* _window2D, sf::RenderWindow* _window);	// Constructor

	void renderBoundaries();	// Renders the boundaries in 2D

	void tick();	// Called every frame

	#pragma region Getters
	std::vector<Boundary*> getBoundaries();
	sf::RenderWindow* getWindow2D();
	sf::RenderWindow* getWindow3D();
	#pragma endregion

private:

	sf::RenderWindow* window;
	sf::RenderWindow* window2D;

	std::vector<Boundary*> boundaries;	// The boundaries that need to be drawn & calculated for in physics
	std::vector<Entity*> entities;		// The entities that need to be drawn & calculated for in physics

	TextureAtlas* tAtlas;	// The TextureAtlas that stores all the scene's textures

	Player* player;
	
};

