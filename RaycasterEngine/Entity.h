#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <string>

#include "Boundary.h"
#include "CircleCollider.h"

#pragma once
class Entity
{
public:

	// Constructor
	explicit Entity(sf::Vector2f _position, float _rotation, int _spriteID, sf::RenderWindow* _window2D, sf::RenderWindow* _window);

	#pragma region Core Functions
	virtual void start();	// Called at the end of the constructor
	virtual void tick();	// Called every frame
	#pragma endregion - These are overriden by child classes

	#pragma region Getters
	Boundary* getRenderer();	// Gets the boundary this entity uses to render
	CircleCollider getCollider();	// Gets the entity's collider
	#pragma endregion

protected:

	sf::Vector2f positon;
	sf::Vector2f direction;

	Boundary* renderer;

	sf::RenderWindow* window2D;
	sf::RenderWindow* window;

	sf::RectangleShape body;
	float collisionRadius;	// The radius of the circle collider
};

