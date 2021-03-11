#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <string>

#include "BoxCollider.h"

#pragma once
class Boundary
{
public:

	// Constructor
	Boundary(sf::Vector2f _position, float _rotation, float _width, sf::RenderWindow* _window, sf::Color _colour, int _textureId, bool _isTransparent = false, bool _hasCollider = true);

	// Draws the boundary in the 2D Window
	void draw2D();

	// Rotates the boundary _angle degrees
	void rotate(float _angle);

	#pragma region Getters
	sf::Vector2f getPointA();	// Gets the boundaries left-most vertex
	sf::Vector2f getPointB();	// Gets the boundaries right-most vertex

	sf::Color get3DColour();	// Gets the colour to multiply this boundaries texture by in 3D

	int getTextureId();			// Gets the ID this texture has in the TextureAtlasa

	BoxCollider getCollider();	// Gets this boundary's collider

	bool getHasCollider();		// Gets if this boundary has a collider

	bool getIsTransparent();	// Gets if this bounary should be classed as transparent

	sf::Vector2f getMidPoint();	// Gets the position
	sf::Vector2f getRotation();	// Gets the rotation
	#pragma endregion

	#pragma region Setters
	void setMidPoint(sf::Vector2f _position);

	void setRotation(sf::Vector2f _rotation);
	#pragma endregion


private:
	sf::RenderWindow* window;	// 2D Render Window

	sf::Vector2f pointA;	// The left-most vertex from the origin, used for rendering 
	sf::Vector2f pointB;	// The lright-most vertex from the origin, used for rendering 

	sf::Vector2f midPoint;			// The position
	sf::Vector2f facingDirection;	// The rotation

	sf::Color colour3D;	// The colour the texture will be multiplied by

	int textureId;	// The ID in the TextureAtlas this boundary uses

	sf::RectangleShape body;	// A rectangle used for physics

	bool isTransparent;	// Whether or not rays will be stopped when colliding with this boundary
	bool hasCollider;	// Whether or not this boundary will be affected by physics
};

