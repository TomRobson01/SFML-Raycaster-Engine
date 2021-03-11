#include "VMath.h"

#define PI 3.14159265f

#pragma region Getters
sf::Vector2f VMath::getMidpoint(sf::Vector2f _a, sf::Vector2f _b)
{
	return (_a + _b) / 2.f;
}

float VMath::getDistance(sf::Vector2f _v1, sf::Vector2f _v2)
{
	return sqrtf(powf(_v2.x - _v1.x, 2) + powf(_v2.y - _v1.y, 2) * 1.0f);
}

#pragma region Directions
sf::Vector2f VMath::getForwardVector(sf::Vector2f _target)
{
	return normalize(_target);
}

sf::Vector2f VMath::getRightVector(sf::Vector2f _target)
{
	return normalize(rotateVector(_target, 90));
}

float VMath::getAngle(sf::Vector2f _target)
{
	return atan2f(_target.y, _target.x);
}
#pragma endregion

#pragma endregion

#pragma region Transformations
// Calculates the direction between a vector and a pivot point, turning a target vector to use that direction 
sf::Vector2f VMath::lookAt(sf::Vector2f _targetVector, sf::Vector2f _lookPoint, sf::Vector2f _pivotPoint)
{
	_targetVector.x = _lookPoint.x - _pivotPoint.x;
	_targetVector.y = _lookPoint.y - _pivotPoint.y;

	_targetVector = normalize(_targetVector);

	return _targetVector;
}

// Rotates the vector a set amount of degrees
sf::Vector2f VMath::rotateVector(sf::Vector2f _target, float _rotateAmount)
{
	// Calculates rotation amounts
	float theta = (_rotateAmount * PI) / 180;

	float cosine = cos(theta);
	float sine = sin(theta);

	// Applys rotation to vector
	sf::Vector2f startingDir = _target;
	_target.x = startingDir.x * cosine - startingDir.y * sine;
	_target.y = startingDir.x * sine + startingDir.y * cosine;

	return _target;
}
#pragma endregion

#pragma region Utilities
// Forces the vector to have a length of 1 - maintains direction
sf::Vector2f VMath::normalize(sf::Vector2f _target)
{
	float length = sqrt((_target.x * _target.x) + (_target.y * _target.y));
	if (length != 0)
	{
		_target = sf::Vector2f(_target.x / length, _target.y / length);
	}

	return _target;
}
#pragma endregion
