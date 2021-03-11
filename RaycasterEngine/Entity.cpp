
#include "Entity.h"
#include "VMath.h"


#pragma region Constructor
Entity::Entity(sf::Vector2f _position, float _rotation, int _spriteID, sf::RenderWindow* _window2D, sf::RenderWindow* _window)
{
	positon = _position;

	direction = sf::Vector2f(0, -1);
	direction = VMath::rotateVector(direction, _rotation);

	window = _window;
	window2D = _window2D;

	renderer = new Boundary(positon, 0, 50, window2D, sf::Color(175, 175, 175, 255), _spriteID, true, false);

	start();
}
#pragma endregion

#pragma region Default Functions
void Entity::start()
{
}

void Entity::tick()
{
	renderer->setMidPoint(positon);
	renderer->setRotation(direction);
}
#pragma endregion These are overridden by child classes

#pragma region Getters
Boundary* Entity::getRenderer()
{
	return renderer;
}

CircleCollider Entity::getCollider()
{
	return CircleCollider(body, collisionRadius, window2D);
}
#pragma endregion