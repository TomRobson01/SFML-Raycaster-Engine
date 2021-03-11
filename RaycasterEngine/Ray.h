#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>

#include "Boundary.h"

#pragma once
class Ray
{

public:
	Ray(sf::Vector2f _origin, sf::Vector2f _direction, sf::RenderWindow* _window, bool _finite = false, float _dist = 1.f);	// Constructor

	void draw2D();	// Draws the ray in 2D

	bool cast(Boundary* _boundary);	// Casts the ray, and checks for intersection with _boundary

	#pragma region Getters/Setters
	// Ray transformation
	sf::Vector2f getHitPoint();
	sf::Vector2f getRayOrigin();
	sf::Vector2f getRayDirection();


	float getRayIntersectionValue();

	void setRayDirection(sf::Vector2f _newDir);
	#pragma endregion

private:

	sf::Vector2f origin;	// The point the ray is cast from
	sf::Vector2f direction;	// The direction the ray is travelling in
	sf::Vector2f hitPoint;	// The point in world space that the ray hits

	sf::RenderWindow* window;

	float intersectionValue;	// The point along the boundary that the ray hits (0.f - 1.f)

	bool finite;	// Whether or not the ray should be restrained to a set distance
	float dist;		// The distance a finite ray will be cast
};

