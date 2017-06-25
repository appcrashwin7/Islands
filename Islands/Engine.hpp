#pragma once

#include <SFML/Graphics.hpp>
#include <cstdlib>
#include <ctime>

#include "IslandApp.hpp"

#include "CollisionDetect.hpp"

#include "PlayerGui.hpp"

#include "GameComponentsLoader.hpp"
#include "GameComponentsUnloader.hpp"

#include "ItemDefContainer.hpp"
#include "LyingItemsContainer.hpp"

#include "playerCharacter.hpp"

#include "Media.hpp"
#include "ObjectArray.hpp"
#include "Log.hpp"
#include "World.hpp"

#include "Console.hpp"

class Engine
{
	World GameWorld;
	Media mediaContainer;
	playerCharacter player;

	PlayerGui GameGui;

	ObjectArray RawObjects;

	ItemDefContainer Items;
	LyingItemsContainer LyingItems;

	sf::View camera;
	sf::Clock GameClock;
	Console GameConsole;

	void loadGameComponents();

	void checkPlayerEnvironment();
	void checkPlayerBehaviour(IslandApp &app);
	bool checkPlayerPos();

	void spawnPlayer();

	void pushChangesToGui();
	void checkGuiOperations(EquipmentType type, sf::Vector2u field);

	void drawConsole(IslandApp &app);

	void drawTile(sf::Vector2u tileIndex, sf::RenderWindow &window, sf::RectangleShape &shp);
	void drawObject(sf::Vector2u objectIndex, sf::RenderWindow &window, sf::RectangleShape &shp);

	void drawWorld(IslandApp &app);

	void drawPlayerGui(IslandApp & app);
public:
	~Engine();

	void init();
	void operator()(IslandApp &app,char key,mouseWheel last,bool isMouseClick);

	void manageConsole(sf::Event &event, sf::Vector2f mousePos, bool isMouseRClick);

	void DrawAll(IslandApp &app);
};