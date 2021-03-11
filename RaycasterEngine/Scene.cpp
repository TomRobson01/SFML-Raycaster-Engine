
#include "Scene.h"

#pragma region Constructor
Scene::Scene(sf::RenderWindow* _window2D, sf::RenderWindow* _window)
{
	window = _window;
	window2D = _window2D;

	// Defines texture atlas
	std::vector<std::string> textures;

	textures.push_back("Assets/Textures/Test/WallTest.png");
	textures.push_back("Assets/Textures/Test/DoorTest.png");
	textures.push_back("Assets/Textures/Test/LampPost.png");
	textures.push_back("Assets/Textures/Test/AlphaTest.png");

	tAtlas = new TextureAtlas(textures, "Assets/Textures/Debug/DefaultTexture.png");

	// Loads player
	player = new Player(window2D, window, tAtlas);

	// Creates entities to test
	entities.push_back(new WorldProp(sf::Vector2f(250, 250), 0, 3, window2D, window, player, 5));
	entities.push_back(new WorldProp(sf::Vector2f(100, 250), 0, 3, window2D, window, player, 5));

	for (int i = 0; i < entities.size(); i++)
	{
		boundaries.push_back(entities[i]->getRenderer());
	}

	// Create some bounaries to test
	boundaries.push_back(new Boundary(sf::Vector2f(175, 225), 180, 50, window2D, sf::Color(175, 175, 175, 255), 4, true));
	boundaries.push_back(new Boundary(sf::Vector2f(200, 200), 90, 50, window2D, sf::Color(175, 175, 175, 255), 1));
	boundaries.push_back(new Boundary(sf::Vector2f(175, 175), 0, 50, window2D, sf::Color(175, 175, 175, 255), 2));
	boundaries.push_back(new Boundary(sf::Vector2f(150, 200), 270, 50, window2D, sf::Color(175, 175, 175, 255), 1));

	player->setBoundaries(boundaries);
}
#pragma endregion

#pragma region Draw Functions
// Renders all boundaries onto the 2D Window
void Scene::renderBoundaries()
{
	if (boundaries.size() > 0)
	{
		for (int i = 0; i < boundaries.size(); i++)
		{
			boundaries[i]->draw2D();
		}
	}
}

#pragma endregion

#pragma region Tick
// Called Every Frame
void Scene::tick()
{
	player->tick();	// Updates the player

	// Updates and calculates physics for all entities
	for (int i = 0; i < entities.size(); i++)
	{
		entities[i]->tick();
		entities[i]->getCollider().drawCollider();
		player->getCollider().checkCollision_Circle(entities[i]->getCollider(), 0.f);
	}

	// Calculates all collisions for all boundaries
	for (int i = 0; i < boundaries.size(); i++)
	{
		if (boundaries[i]->getHasCollider())
		{
			boundaries[i]->getCollider().drawCollider();
			player->getCollider().checkCollision(boundaries[i]->getCollider(), 0.f);
		}
	}
}
#pragma endregion

#pragma region Getters
std::vector<Boundary*> Scene::getBoundaries()
{
	return boundaries;
}

sf::RenderWindow* Scene::getWindow2D()
{
	return window2D;
}

sf::RenderWindow* Scene::getWindow3D()
{
	return window;
}
#pragma endregion


