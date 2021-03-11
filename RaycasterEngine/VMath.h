#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>

#pragma once
class VMath
{

public:

	#pragma region Getters
	static float getAngle(sf::Vector2f _target);	// Gets the angle of a vector

	static float getDistance(sf::Vector2f _v1, sf::Vector2f _v2);	// Finds the distance between two vectors

	static sf::Vector2f getMidpoint(sf::Vector2f _a, sf::Vector2f _b);	// Finds the midpoint between two vectors

	static sf::Vector2f getForwardVector(sf::Vector2f _target);	// Gets the vectors forwards direction

	static sf::Vector2f getRightVector(sf::Vector2f _target);	// Gets the vectors right direction
	#pragma endregion

	#pragma region Transformations
	static sf::Vector2f lookAt(sf::Vector2f _targetVector, sf::Vector2f _lookPoint, sf::Vector2f _pivotPoint);	// Rotates the target vector around the pivot point to face _lookPoint

	static sf::Vector2f rotateVector(sf::Vector2f _target, float _rotateAmount);	// Rotates the target vector _rotateAmount degrees
	#pragma endregion

	#pragma region Utilities
	static sf::Vector2f normalize(sf::Vector2f _target);	// Clamps the target vector's distance to 1
	#pragma endregion

private:


};

