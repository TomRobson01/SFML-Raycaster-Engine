#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>

#include "Entity.h"
#include "Player.h"
#include "CircleCollider.h"

#pragma once
class WorldProp : public Entity
{

public:
	
	// Constructors - adds WorldProp specific parameters atop of the default Entity Constructor's parameters
	explicit WorldProp(sf::Vector2f _position, float _rotation, int _spriteID, sf::RenderWindow* _window2D, sf::RenderWindow* _window, Player* _playerRef, float _collisionRadius) : Entity(_position, _rotation, _spriteID, _window2D, _window) 
	{ 
		playerRef = _playerRef; 
		collisionRadius = _collisionRadius;  

		body.setPosition(_position);
		body.setSize(sf::Vector2f(collisionRadius, collisionRadius) * 2.f);
		body.setOrigin(body.getSize() / 2.f);
	}

	void tick();	// Caleld every frame


private:
	Player* playerRef;

};

