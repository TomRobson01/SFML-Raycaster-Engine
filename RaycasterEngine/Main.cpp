#include <SFML/Graphics.hpp>

#include "Scene.h"

int main()
{
	// Creates 3D and 2D Windows
	sf::RenderWindow window2D(sf::VideoMode(400, 400), "2D Window");
	sf::RenderWindow window(sf::VideoMode(400, 400), "3D Window");

	window2D.setPosition(sf::Vector2i(600, 100));
	window.setPosition(sf::Vector2i(1050, 100));

	window.setFramerateLimit(60);

	// Creates event handler
	sf::Event event;

	// Generates scene
	Scene* scene = new Scene(&window2D, &window);

	// Updates rendering and scene 
	while (window2D.isOpen() && window.isOpen()) 
	{
		#pragma region Closing windows
		while (window2D.pollEvent(event)) {

			if (event.type == sf::Event::Closed) {

				window2D.close();
				window.close();
			}
		}

		while (window.pollEvent(event)) {

			if (event.type == sf::Event::Closed) {

				window2D.close();
				window.close();
			}
		}
		#pragma endregion

		// Clears windows
		window2D.clear();
		window.clear(sf::Color(155, 155, 155, 255));

		// Updates scene
		scene->renderBoundaries();
		scene->tick();

		// Draws changes to windows
		window2D.display();
		window.display();
	}

	return 0;
}