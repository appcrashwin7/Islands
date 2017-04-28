#pragma once

#include <SFML/Graphics.hpp>
#include <map>
#include "Log.hpp"

enum class TextureContainer : unsigned
{
	TileTextures,
	CharacterTextures,
	ObjectTextures,
	ItemsTextures,
};

class Media
{
	const int size = 10;
	const int pos = 10;

	sf::Image TileImage;

	std::vector <sf::Texture> TileTexture;
	
	std::vector<sf::Texture> CharacterTexture;
	std::vector<sf::Texture> ObjectsTexture;
	std::vector<sf::Texture> ItemsTexture;

public:
	void load()
	{
		TileImage.loadFromFile("Data/Tiles.png");

		TileTexture.resize(12);

		TileTexture[1].loadFromImage(TileImage, sf::IntRect(pos, pos, size, size));//normal
		TileTexture[2].loadFromImage(TileImage, sf::IntRect(pos, pos * 3, size, size));//brigde

		CharacterTexture.push_back(sf::Texture());
		CharacterTexture.back().loadFromFile("Data/char.png", sf::IntRect(0, 0, 40, 60));
	}

	sf::Texture& pushTexture(TextureContainer destinationContainer, std::string fileName, sf::IntRect textCord)
	{
		switch (destinationContainer)
		{
		case TextureContainer::TileTextures:
			TileTexture.push_back(sf::Texture());
			if (!TileTexture.back().loadFromFile(fileName, textCord))
			{
				ErrorHandler::log("Tile texture load incorectly");
			}
			return TileTexture.back();
			break;
		case TextureContainer::CharacterTextures:
			CharacterTexture.push_back(sf::Texture());
			if (!CharacterTexture.back().loadFromFile(fileName, textCord))
			{
				ErrorHandler::log("Character texture load incorectly");
			}
			return CharacterTexture.back();
			break;
		case TextureContainer::ObjectTextures:
			ObjectsTexture.push_back(sf::Texture());
			if (!ObjectsTexture.back().loadFromFile(fileName, textCord))
			{
				ErrorHandler::log("Object texture load incorectly");
			}
			return ObjectsTexture.back();
			break;
		case TextureContainer::ItemsTextures:
			ItemsTexture.push_back(sf::Texture());
			if (!ItemsTexture.back().loadFromFile(fileName, textCord))
			{
				ErrorHandler::log("Item texture load incorectly");
			}
			return ItemsTexture.back();
			break;
		default:
			break;
		}
	}
	sf::Texture& getTexture(size_t index, TextureContainer typeOfContainer)
	{
		switch (typeOfContainer)
		{
		case TextureContainer::TileTextures:
			return TileTexture[index];
			break;
		case TextureContainer::CharacterTextures:
			return CharacterTexture[index];
			break;
		case TextureContainer::ObjectTextures:
			return ObjectsTexture[index];
			break;
		case TextureContainer::ItemsTextures:
			return ItemsTexture[index];
			break;
		default:
			break;
		}
	}

	Media()
	{
		TileTexture.push_back(sf::Texture());
		ObjectsTexture.push_back(sf::Texture());
		ItemsTexture.push_back(sf::Texture());
		CharacterTexture.push_back(sf::Texture());
	}
	~Media()
	{
		ObjectsTexture.clear();
		ItemsTexture.clear();
		TileTexture.clear();
		CharacterTexture.clear();
	}
};