#include "Ray.h"
#include "Boundary.h"
#include "VMath.h"

#pragma region Constructor
Ray::Ray(sf::Vector2f _origin, sf::Vector2f _direction, sf::RenderWindow* _window, bool _finite, float _dist)
{
	origin = _origin;
	direction = _direction;

	window = _window;

	intersectionValue = 0;

	finite = _finite;
	dist = _dist;
}
#pragma endregion

#pragma region Drawing Functions
void Ray::draw2D()
{
	// Draws a short line in the direction of the ray
	sf::Vertex line[] =
	{
		sf::Vertex(origin),
		sf::Vertex(origin + (direction * 15.f))
	};

	window->draw(line, 2, sf::Lines);
}
#pragma endregion

#pragma region Intersection Checks
bool Ray::cast(Boundary* _boundary)
{
	// Calculates if there are any itnersections between the ray and a given boundary. Solution is based on equations given here https://en.wikipedia.org/wiki/Line%E2%80%93line_intersection

	// Gets the positions for the start and end of the boundary lines
	float x1 = _boundary->getPointA().x;
	float y1 = _boundary->getPointA().y;
	float x2 = _boundary->getPointB().x;
	float y2 = _boundary->getPointB().y;

	// Gets the start and end points of the ray
	float x3 = origin.x;
	float y3 = origin.y;
	float x4 = origin.x + (finite ? direction.x * dist : direction.x);
	float y4 = origin.y + (finite ? direction.y * dist : direction.y);

	// The denominator of the intersection fraction is the same for calculating t and u
	const float denominator = (x1 - x2) * (y3 - y4) - (y1 - y2) * (x3 - x4);

	// If the denominator is 0, the lines are parallel, will never meet, and the function can be broken out of
	if (denominator == 0)
	{
		return false;
	}

	// Calculates t and u - based on the equations on the wiki page
	float t = ((x1 - x3) * (y3 - y4) - (y1 - y3) * (x3 - x4)) / denominator;
	float u = -((x1 - x2) * (y1 - y3) - (y1 - y2) * (x1 - x3)) / denominator;

	// If t is between 0 & 1 (0 and 1 being the bounds of the line), and u is over 0 (past the origin of the ray)
	if (finite ? (t > 0 && t < 1 && u > 0 && u < 1) : (t > 0 && t < 1 && u > 0))
	{
		hitPoint.x = x1 + t * (x2 - x1);
		hitPoint.y = y1 + t * (y2 - y1);

		intersectionValue = t;

		return true;
	}
	else
	{
		return false;
	}
}
#pragma endregion

#pragma region Getters/Setters
sf::Vector2f Ray::getHitPoint()
{
	return hitPoint;
}
sf::Vector2f Ray::getRayOrigin()
{
	return origin;
}
sf::Vector2f Ray::getRayDirection()
{
	return direction;
}
float Ray::getRayIntersectionValue()
{
	return intersectionValue;
}


void Ray::setRayDirection(sf::Vector2f _newDir)
{
	direction = _newDir;
}
#pragma endregion
