
#include "CircleCollider.h"
#include "VMath.h"

#pragma region Constructor
CircleCollider::CircleCollider(sf::RectangleShape& _body, float _radius, sf::RenderWindow* _window) :
	body(_body)
{
	radius = _radius;
	window = _window;

	// Creates a 2D debug shape, which can be drawn in the 2D Window
	debugBounds = sf::CircleShape(_radius);
	debugBounds.setPosition(body.getPosition());
	debugBounds.setOrigin(sf::Vector2f(radius, radius));
	debugBounds.setFillColor(sf::Color(100, 250, 50));
}
#pragma endregion

#pragma region Collision Detection
// Checks for collision with boxes
bool CircleCollider::checkCollision(BoxCollider _coll, float _moveability)
{
	sf::Vector2f collPos = _coll.getPosition() - _coll.getOrigin();
	sf::Vector2f collHalfSize = _coll.getHalfSize();
	sf::Vector2f pos = body.getPosition();

	float boxWidth = collHalfSize.x * 2;
	float boxHeight = collHalfSize.y * 2;


	// Calculates the closest point on the box colldier to the circle
	float deltaX = pos.x - std::max(collPos.x, std::min(pos.x, collPos.x + boxWidth));
	float deltaY = pos.y - std::max(collPos.y, std::min(pos.y, collPos.y + boxHeight));

	// Checks if that intersection point is within the circle's radius
	if ((deltaX * deltaX + deltaY * deltaY) < (radius * radius))
	{
		// Calculates the intersection on both axis between the circle and the box
		float intersectX = abs(deltaX) - radius;
		float intersectY = abs(deltaY) - radius;

		_moveability = std::min(std::max(_moveability, 0.f), 1.f);	// Clamps the movement amount between 0 and 1


		if (intersectX > intersectY)
		{
			// If the X intersection is greater than the Y intersection...
			// Repel the objects from eachother on the X axis by their intersection, multiplied by the moveability (this changes if the delta is positive or negative)
			if (deltaX > 0.f)
			{
				move(-intersectX * (1.f - _moveability), 0.f);
				_coll.move(intersectX * _moveability, 0.f);
			}
			else
			{
				move(intersectX * (1.f - _moveability), 0.f);
				_coll.move(-intersectX * _moveability, 0.f);
			}
		}
		else
		{
			// Otherwise,
			// Repel the objects from eachother on the Y axis (this changes if the delta is positive or negative)
			if (deltaY > 0.f)
			{
				move(0.f, -intersectY * (1.f - _moveability));
				_coll.move(0.f, intersectY * _moveability);
			}
			else
			{
				move(0.f, intersectY * (1.f - _moveability));
				_coll.move(0.f, -intersectY * _moveability);
			}
		}

		return true;
	}

	return false;
}

// Checks for collisions with other circles
bool CircleCollider::checkCollision_Circle(CircleCollider _coll, float _moveability)
{
	// Circle v Circle collision just checks if the distance between the two circles is less than the sum of their radii

	float sumOfRadius = radius + _coll.getRadius();
	float dist = VMath::getDistance(getPosition(), _coll.getPosition());


	if (dist < sumOfRadius)
	{
		float intersection = sumOfRadius - dist;	// Calculates how much the two circles intersect

		_moveability = std::min(std::max(_moveability, 0.f), 1.f);	// Clamps the movement amount between 0 and 1


		// For hit reaction, obth colliders repel eachother based on the intersection amount
		// However this is multiplied by a "moveability" amount, so that some objects can be completely immobile when collided with, and others can be pushed
		_coll.move((_coll.getPosition().x - getPosition().x) * intersection * _moveability, (_coll.getPosition().y - getPosition().y) * intersection * _moveability);
		move((getPosition().x - _coll.getPosition().x) * (intersection * (1.f - _moveability)), (getPosition().y - _coll.getPosition().y) * (intersection * (1.f - _moveability)));

		return true;
	}
	return false;
}
#pragma endregion

#pragma region Transformation
void CircleCollider::move(float _deltaX, float _deltaY)
{
	body.move(_deltaX, _deltaY);
}
#pragma endregion

#pragma region Draw Functions
void CircleCollider::drawCollider()
{
	window->draw(debugBounds);
}
#pragma endregion

#pragma region Getters
sf::Vector2f CircleCollider::getPosition()
{
	return body.getPosition();
}

float CircleCollider::getRadius()
{
	return radius;
}
#pragma endregion