#include <SFML/Graphics.hpp>

#pragma once
class BoxCollider
{
public:
	BoxCollider(sf::RectangleShape& _body, sf::RenderWindow* _window);	// Constructor

	void move(float _deltaX, float _deltaY);	// Moves the collider's bounds by _deltaX and _deltaY
	void drawCollider();	// Draws the collision bounds in 2D

	bool checkCollision(BoxCollider _coll, float _resistance);	// Checks for collision with _coll

	#pragma region Getters
	sf::Vector2f getPosition();	// Gets the collision bound's position
	sf::Vector2f getHalfSize();	// Gets half the collision bound's size
	sf::Vector2f getOrigin();	// Gets the pivot point of the collision bounds
	#pragma endregion

private:
	sf::RectangleShape& body;	// A rectangle used to represent this colldier's bounds

	sf::RenderWindow* window;	// The 2D Render Window
};

