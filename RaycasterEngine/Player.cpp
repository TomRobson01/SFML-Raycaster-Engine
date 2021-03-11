#include "Player.h"
#include "VMath.h"

#define INPUT_DAMPEN 0.001f

#pragma region Constructor
Player::Player(sf::RenderWindow* _window2D, sf::RenderWindow* _window, TextureAtlas* _tAtlas)
{
	window = _window;
	window2D = _window2D;
	position = sf::Vector2f(100, 300);
	direction = sf::Vector2f(1.f, 1.f);
	textureAtlas = _tAtlas;

	// Default values for movement and collision
	moveSpeed = 500.f;
	mouseSensitivity = 50.f;
	collisionRadius = 5.f;

	// Creates sf::Body used for physiscs
	body.setPosition(position);
	body.setSize(sf::Vector2f(collisionRadius, collisionRadius) * 2.f);
	body.setOrigin(body.getSize() / 2.f);
}
#pragma endregion

#pragma region Tick
void Player::tick()
{
	// Gets facing direction from particle
	direction = particle->getDirection();

	// Cursor handling
	window->setMouseCursorVisible(!window->hasFocus());

	// Movement hanlding (only if the window is focused)
	if (window->hasFocus())
	{
		inputHandling();
	}

	// Keeps the particle allinged with the player
	particle->updatePos(position);
	particle->updateRot(rotation);

	// Draws the collision
	getCollider().drawCollider();

	// Draws normal in 2D Window
	sf::Vertex line[] =
	{
		sf::Vertex(position, sf::Color(255, 0, 0, 255)),
		sf::Vertex(position + (direction * 25.f), sf::Color(255, 0, 0, 255))
	};
	window2D->draw(line, 2, sf::Lines);

	particle->drawScene3D();	// Draws the 3D scene
}
#pragma endregion

#pragma region Input
void Player::inputHandling()
{
	#pragma region Movement
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) || sf::Keyboard::isKeyPressed(sf::Keyboard::W))
	{
		// Move forwards
		body.move(VMath::getForwardVector(direction) * moveSpeed * INPUT_DAMPEN);
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down) || sf::Keyboard::isKeyPressed(sf::Keyboard::S))
	{
		// Move back
		body.move(-VMath::getForwardVector(direction) * moveSpeed * INPUT_DAMPEN);
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left) || sf::Keyboard::isKeyPressed(sf::Keyboard::A))
	{
		// Strafe Left
		body.move(-VMath::getRightVector(direction) * moveSpeed * INPUT_DAMPEN);
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right) || sf::Keyboard::isKeyPressed(sf::Keyboard::D))
	{
		// Strafe Right
		body.move(VMath::getRightVector(direction) * moveSpeed * INPUT_DAMPEN);
	}

	position = body.getPosition();
	#pragma endregion

	// Rotates the player based on mouse movement
	rotation += (sf::Mouse::getPosition().x - mousePosLastFrame.x) * mouseSensitivity * INPUT_DAMPEN;

	// Resets mouse to center of the window
	sf::Vector2i mouseLockPos = window->getPosition();
	mouseLockPos += sf::Vector2i(window->getSize().x / 2, window->getSize().y / 2);
	sf::Mouse::setPosition(mouseLockPos);

	mousePosLastFrame = sf::Mouse::getPosition();
}
#pragma endregion

#pragma region Getters/Setters
// Sets up the boundaries to check for rendering, and creates a new renderer
void Player::setBoundaries(std::vector<Boundary*> _boundaries)
{
	boundaries = _boundaries;
	particle = new RayParticle(boundaries, window2D, window, textureAtlas);
}

CircleCollider Player::getCollider()
{
	return CircleCollider(body, collisionRadius, window2D);
}

sf::Vector2f Player::getPosition()
{
	return position;
}
#pragma endregion
