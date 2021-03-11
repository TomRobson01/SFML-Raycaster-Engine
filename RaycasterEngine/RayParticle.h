#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <vector>
#include <string>

#include "Ray.h"
#include "Boundary.h"
#include "TextureAtlas.h"

// Stores all data needed for rendering a column
struct RayData
{
	float hitDist;
	float angleOffset;
	float intersectionValue;
	sf::Color boundaryColour;
	int textureID;
	bool hit;
};

// Stores all data that needs to be drawn for each column
struct DrawData
{
	std::vector<RayData> drawData;
};

#pragma once
class RayParticle
{
public:

	RayParticle(std::vector<Boundary*> _boundaries, sf::RenderWindow* _window2D, sf::RenderWindow* _window, TextureAtlas* _tAtlas);	// Constructor

	void emitRays();	// Casts rays out, and populates the draw buffer with the hit data
	void drawScene3D();	// Renders the scene in 3D

	#pragma region Transformation Functions
	void updatePos(sf::Vector2f _newPos);
	void updateRot(float _newRot);
	#pragma endregion

	#pragma region Getters/Setters
	sf::Vector2f getDirection();
	void setDirection(sf::Vector2f _newDir);
	#pragma endregion




private:

	sf::RenderWindow* window;
	sf::RenderWindow* window2D;

	sf::Vector2f position;
	sf::Vector2f direction;
	
	std::vector<Ray*> rays;	// The rays the particle will cast

	std::vector<Boundary*> boundaries;	// The boundaries this particle tries to draw

	std::vector<DrawData> drawData;	// The Draw Buffer - Contains all data that needs to be drawn

	std::vector<sf::Texture> textures;	// Stores textures from the TextureAtlas

	float rotation;
	float columnWidth;	// The width of any given column
};

