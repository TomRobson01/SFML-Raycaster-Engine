#include <SFML/Graphics.hpp>

#include "BoxCollider.h"

#pragma once
class CircleCollider
{

public:
	CircleCollider(sf::RectangleShape& _body, float _radius, sf::RenderWindow* _window);	// Constructor

	bool checkCollision(BoxCollider _coll, float _resistance);				// Checks for collision with _coll - Circle v AABB
	bool checkCollision_Circle(CircleCollider _coll, float _resistance);	// Checks for collision with _coll - Circle v Circle

	void move(float _deltaX, float _deltaY);	// Moves the collider's bounds by _deltaX and _deltaY
	void drawCollider();	// Draws the collision bounds in 2D

	#pragma region Getters
	sf::Vector2f getPosition();	// Gets the collision bound's position
	float getRadius();			// Gets the collision bound's radius
	#pragma endregion

private:

	float radius;

	sf::RectangleShape& body;		// A bounding box, used for basic movement
	sf::CircleShape debugBounds;	// A circle shape that can be drawn in 2D to debug the size of the collider

	sf::RenderWindow* window;	// The 2D render window
};

