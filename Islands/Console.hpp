#pragma once

#include "textbox.hpp"
#include <vector>

class Console
{
	sf::RectangleShape ConsoleWindow;
	textbox ConsoleInput;

	std::vector<std::string> commands;
	std::vector<std::string> history;

	unsigned lastHistoryCmd;

	sf::Font ConsoleFont;

	bool enable;
public:
	Console()
	{
		ConsoleWindow.setSize(sf::Vector2f(400, 600));
		ConsoleWindow.setFillColor(sf::Color(36, 10, 92, 120));
		
		ConsoleInput.changeVars(sf::Color::White, 16, sf::Text::Style::Regular);
		ConsoleFont.loadFromFile("Data/Fonts/ariali.ttf");
		ConsoleInput.create(ConsoleFont, false, "Type you command here! ", 64);

		lastHistoryCmd = 0;
		enable = true;
	}
	~Console()
	{
		commands.clear();
		history.clear();
	}
	
	bool getEnable() { return enable; }
	void setEnable(bool newVal) { enable = newVal; }

	void pushCommandToHistory(std::string command) { history.push_back(command); }
	std::string getCmdFromHistory(unsigned cmdNumber) { return history[cmdNumber]; }
	std::string getLastCmdFromHistory() { return history.back(); }
	unsigned getHistorySize() { return history.size(); }

	unsigned &getLastHistoryCmdNumber() { return lastHistoryCmd; }

	std::string operator()(sf::Event &event,sf::Vector2f mousePos,bool isMouseClick)
	{
		if (ConsoleInput.isClick(mousePos, isMouseClick))
		{
			ConsoleInput.switchEnable();
		}
		return ConsoleInput.operator()(event);
	}

	void clearConsole()
	{
		commands.clear();
		ConsoleInput.setString("");
	}
	void clearHistory() { history.clear(); }

	std::string getCurrentText() { return ConsoleInput.getString(); }
	void setCurrentText(std::string text) { ConsoleInput.setString(text); }

	size_t getCommandsSize() { return commands.size(); }
	void pushText(std::string &text) { commands.push_back(text); }
	std::string getText(unsigned index) { return commands[index]; }
	std::string getLastText() { return commands.back(); }

	void setPosition(sf::Vector2f position)
	{
		ConsoleWindow.setPosition(position);
		ConsoleInput.setPosition(position + sf::Vector2f(20, 560));
	}

	sf::RectangleShape getWindow() { return ConsoleWindow; }
	sf::Text getInputText() { return ConsoleInput.getText(); }

	//function for /giveItem command
	void giveItemCheck(std::string command, ItemDefContainer &Items, PlayerInventory &Inv)
	{
		bool firstParam = true;
		std::string idStr;
		std::string amountStr;
		size_t begPos = command.find("m") + 2;
		size_t i = begPos;

		while (i < command.size())
		{
			if (command[i] != ' ')
			{
				if (firstParam)
				{
					idStr += command[i];
				}
				else
				{
					amountStr += command[i];
				}
			}
			else
			{
				firstParam = false;
			}
			i++;
		}

		int id = std::stoi(idStr);
		if (id <= 0) { commands.push_back("id is equal 0 or smaller"); return; }
		if (static_cast<unsigned>(id) > Items.getContainer().size()-1) { commands.push_back("item with this id does not exist"); return; }
		int amount = std::stoi(amountStr);
		if (amount <= 0) { commands.push_back("amount is equal 0 or smaller"); return; }
		if (static_cast<unsigned>(amount) > MAXIMUM_STACK_SIZE) { commands.push_back("amount is higher than MAXIMUM_STACK_SIZE"); return; }
		if (static_cast<unsigned>(amount) > Items.getDefinition(id)->getMaxStack()) { commands.push_back("amount is higher than Item::MaxStack"); return; }

		Inv.pushItem(ItemField(id, amount), Items.getDefinition(id)->getMaxStack());
		pushCommandToHistory(command);

		return;
	}

	//function for /placeObject command
	void placeObjectCheck(std::string command, ObjectDefContainer &GObjects, World &GWorld)
	{
		uint16_t param = 1;
		std::string tileX;
		std::string tileY;
		std::string objectId;

		size_t begPos = command.find('t');
		size_t i = begPos + 2;

		while (i < command.size())
		{
			if (command[i] != ' ')
			{
				switch (param)
				{
				case 1:
					tileX += command[i];
					break;
				case 2:
					tileY += command[i];
					break;
				case 3:
					objectId += command[i];
					break;
				default:
					break;
				}
			}
			else
			{
				param++;
			}
			i++;
		}
		sf::Vector2i tile;
		tile.x = std::stoi(tileX);
		tile.y = std::stoi(tileY);

		if (tile.x < 0 || tile.y < 0) 
		{ 
			commands.push_back(std::string("tile param must have value bigger than 0!")); 
			return;
		}
		if (static_cast<unsigned>(tile.x) > WorldSize || static_cast<unsigned>(tile.y) > WorldSize)
		{
			commands.push_back(std::string("tile param must have value smaller than World::WorldSize!"));
			return;
		}

		int objId = std::stoi(objectId);
		if (objId < 0)
		{
			commands.push_back(std::string("objectId param must have value bigger than 0!"));
			return;
		}
		if (static_cast<unsigned>(objId) > GObjects.getSize() - 1)
		{
			commands.push_back(std::string("objectId param must have value smaller than Objects.Size()"));
			return;
		}

		if (GObjects.getDefinition(objId)->getType() == ObjectType::Default)
		{
			GWorld.setObject(static_cast<sf::Vector2u>(tile), new Object(objId));
		}
		pushCommandToHistory(command);
	}
};