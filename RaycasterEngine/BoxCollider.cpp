
#include "BoxCollider.h"

#pragma region Constructor
BoxCollider::BoxCollider(sf::RectangleShape& _body, sf::RenderWindow* _window) :
	body(_body)
{
	body = _body;
	window = _window;

	body.setFillColor(sf::Color(100, 250, 50));
}
#pragma endregion

#pragma region Collision Detection
// Checks for collision with other boxes
bool BoxCollider::checkCollision(BoxCollider _coll, float _moveability)
{
	sf::Vector2f collPos = _coll.getPosition();
	sf::Vector2f collHalfSize = _coll.getHalfSize();
	sf::Vector2f pos = getPosition();
	sf::Vector2f halfSize = getHalfSize();

	// Calculates the distance between the two boxes
	float deltaX = collPos.x - pos.x;
	float deltaY = collPos.y - pos.y;

	// Calculates the intersection between the two boxes
	float intersectX = abs(deltaX) - (collHalfSize.x + halfSize.x);
	float intersectY = abs(deltaY) - (collHalfSize.y + halfSize.y);


	// Intersections will be negative if a collision exists
	if (intersectX < 0.0f && intersectY < 0.0f)
	{
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
#pragma endregion

#pragma region Transformation
void BoxCollider::move(float _deltaX, float _deltaY)
{
	body.move(_deltaX, _deltaY);
}
#pragma endregion

#pragma region Draw Functions
void BoxCollider::drawCollider()
{
	window->draw(body);
}
#pragma endregion

#pragma region Getters
sf::Vector2f BoxCollider::getPosition()
{
	return body.getPosition();
}

sf::Vector2f BoxCollider::getHalfSize()
{
	return body.getSize() / 2.f;
}

sf::Vector2f BoxCollider::getOrigin()
{
	return body.getOrigin();
}
#pragma endregion
