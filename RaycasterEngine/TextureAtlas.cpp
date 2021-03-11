#include "TextureAtlas.h"

TextureAtlas::TextureAtlas(std::vector<std::string> _textureDirectories, std::string _defaultTextureDirectory)
{
	// Loads default texture into memory and stores it in a vector
	if (!defaultTexture.loadFromFile(_defaultTextureDirectory))
	{
		// SFML will throw an error here
	}
	textures.push_back(defaultTexture);


	// Loads all textures into memory and stores them in a vector
	for (int i = 0; i < _textureDirectories.size(); i++)
	{
		sf::Texture texture;

		if (!texture.loadFromFile(_textureDirectories[i]))
		{
			// SFML will throw an error here
		}

		textures.push_back(texture);
	}
}

#pragma region Getters
sf::Texture TextureAtlas::getTexture(int index)
{
	return textures[index];
}

sf::Texture TextureAtlas::getDefaultTexture()
{
	return defaultTexture;
}

std::vector<sf::Texture> TextureAtlas::getTextures()
{
	return textures;
}
#pragma endregion
