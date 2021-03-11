#include "Boundary.h"
#include "VMath.h"

#pragma region Constructor
Boundary::Boundary(sf::Vector2f _position, float _rotation, float _width, sf::RenderWindow* _window, sf::Color _colour, int _textureId, bool _isTransparent, bool _hasCollider)
{
	window = _window;
	colour3D = _colour;
	textureId = _textureId;
	isTransparent = _isTransparent;
	hasCollider = _hasCollider;

	// Sets boundary to face target direction
	facingDirection = sf::Vector2f(0, -1);
	facingDirection = VMath::rotateVector(facingDirection, _rotation);

	// Creates boundary extents based on the midpoint and rotation
	midPoint = _position;
	pointA = midPoint + (VMath::getRightVector(facingDirection) * (_width / 2.f));
	pointB = midPoint - (VMath::getRightVector(facingDirection) * (_width / 2.f));

	// Generates a sf::Body used for physics
	body.setPosition(_position);
	body.setSize(sf::Vector2f(std::max(pointA.x - pointB.x, pointB.x - pointA.x), std::max(pointA.y - pointB.y, pointB.y - pointA.y)));
	body.setOrigin(body.getSize() / 2.f);

}
#pragma endregion

#pragma region Drawing Functions
// Draws debug data in the 2D Window
void Boundary::draw2D()
{
	#pragma region Draw Renderer Line
	sf::Vertex line[] =
	{
		sf::Vertex(pointA, colour3D),
		sf::Vertex(pointB, colour3D)
	};
	window->draw(line, 2, sf::Lines);
	#pragma endregion

	#pragma region Draw Normal
	sf::Vertex normal[] =
	{
		sf::Vertex(midPoint, sf::Color(255, 0, 0, 128)),
		sf::Vertex(midPoint + (facingDirection * 10.f), sf::Color(255, 0, 0, 128))
	};
	window->draw(normal, 2, sf::Lines);

	#pragma endregion
}
#pragma endregion

#pragma region Transformations
// Forces the position to a set value, updating the extents
void Boundary::setMidPoint(sf::Vector2f _position)
{
	midPoint = _position;

	pointA = midPoint + (VMath::getRightVector(facingDirection) * 25.f);
	pointB = midPoint - (VMath::getRightVector(facingDirection) * 25.f);
}

// Rotates the boundary, updating the extents
void Boundary::rotate(float _angle)
{
	facingDirection = VMath::rotateVector(facingDirection, _angle);

	pointA = midPoint + (VMath::getRightVector(facingDirection) * 25.f);
	pointB = midPoint - (VMath::getRightVector(facingDirection) * 25.f);
}

// Forces the rotation ot a set value, updating the extents
void Boundary::setRotation(sf::Vector2f _rotation)
{
	facingDirection = _rotation;

	pointA = midPoint + (VMath::getRightVector(facingDirection) * 25.f);
	pointB = midPoint - (VMath::getRightVector(facingDirection) * 25.f);
}
#pragma endregion

#pragma region Getters
sf::Vector2f Boundary::getPointA()
{
	return pointA;
}

sf::Vector2f Boundary::getPointB()
{
	return pointB;
}

sf::Color Boundary::get3DColour()
{
	return colour3D;
}

int Boundary::getTextureId()
{
	return textureId;
}

BoxCollider Boundary::getCollider()
{
	return BoxCollider(body, window);
}

bool Boundary::getHasCollider()
{
	return hasCollider;
}

bool Boundary::getIsTransparent()
{
	return isTransparent;
}


sf::Vector2f Boundary::getMidPoint()
{
	return midPoint;
}


sf::Vector2f Boundary::getRotation()
{
	return facingDirection;
}
#pragma endregion

