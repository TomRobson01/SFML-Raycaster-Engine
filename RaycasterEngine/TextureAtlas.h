#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>

#include <vector>
#include <string>

#pragma once
class TextureAtlas
{
public:

	TextureAtlas(std::vector<std::string> _textureDirectories, std::string _defaultTextureDirectory);	// Constructor

	#pragma region Getters
	sf::Texture getTexture(int index);
	sf::Texture getDefaultTexture();
	std::vector<sf::Texture> getTextures();
	#pragma endregion

private:

	std::vector<sf::Texture> textures;
	sf::Texture defaultTexture;	// The default texture - used as a fallback if a texture can't be retrieved from the textures Vector

};

