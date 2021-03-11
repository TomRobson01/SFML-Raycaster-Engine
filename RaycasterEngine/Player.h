#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>

#include "RayParticle.h"
#include "Ray.h"
#include "Boundary.h"
#include "CircleCollider.h"
#include "TextureAtlas.h"

#pragma once
class Player
{

public:

	Player(sf::RenderWindow* _window2D, sf::RenderWindow* _window, TextureAtlas* _tAtlas);	// Constructor

	void tick();	// Called every frame

	void inputHandling();	// Handles input, movement, and rotation

	void setBoundaries(std::vector<Boundary*> _boundaries);	// Sets up boundaries to render, also sets up renderer

	#pragma region Getters
	CircleCollider getCollider();
	sf::Vector2f getPosition();
	#pragma endregion

private:

	RayParticle* particle;	// The RayParticle responsible for rendering this player's view

	sf::Vector2f position;
	sf::Vector2f direction;	// The direction the player is facing
	float rotation;			// The rotation of the player in degrees

	sf::Vector2i mousePosLastFrame;	// The position of the mouse on the screen last frame - used to detect mouse movement

	float mouseSensitivity;
	float moveSpeed;

	float collisionRadius;

	sf::RenderWindow* window;
	sf::RenderWindow* window2D;

	std::vector<Boundary*> boundaries;	// All the boundaries in the scene this player can render

	sf::RectangleShape body;
	
	TextureAtlas* textureAtlas;	// A pointer to the TextureAtlas that has all the texture data stored in memory
	
};

