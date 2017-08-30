#pragma once

#include <vector>

#include <SFML/System/Time.hpp>
#include <SFML/System/Vector2.hpp>

#include "ItemField.hpp"

struct LyingItem
{
	sf::Time lyingTime;
	sf::Vector2f lyingPosition;

	ItemField lyingItem;

	
	LyingItem() = default;
	LyingItem(sf::Time atTime,sf::Vector2f atPosition,ItemField item) : 
		lyingTime(atTime), lyingPosition(atPosition), lyingItem(item){}
};

class LyingItemsContainer
{
	std::vector<LyingItem> LyingItems;
	size_t MaxNumberOfLyingItems;
	sf::Vector2f LyingItemsPickUpRange;
public:
	LyingItemsContainer() { MaxNumberOfLyingItems = 0; LyingItemsPickUpRange = sf::Vector2f(); }
	~LyingItemsContainer() { LyingItems.clear(); }

	void init(unsigned MaxSize, sf::Vector2f MinimalItemPickUpDistance)
	{
		MaxNumberOfLyingItems = MaxSize;
		LyingItemsPickUpRange = MinimalItemPickUpDistance;
	}

	size_t getSize() { return LyingItems.size(); }

	void eraseFirstItem() { LyingItems.erase(LyingItems.begin()); }
	void eraseItem(unsigned index) { LyingItems.erase(LyingItems.begin() + index); }

	void pushNewItem(sf::Time time, sf::Vector2f position, ItemField item)
	{
		LyingItems.push_back(LyingItem(time, position, item));
		if (LyingItems.size() >= MaxNumberOfLyingItems) { eraseFirstItem(); }
	}

	sf::Time getTime(unsigned index) { return LyingItems[index].lyingTime; }
	sf::Vector2f getPosition(unsigned index) { return LyingItems[index].lyingPosition; }
	ItemField getItem(unsigned index) { return LyingItems[index].lyingItem; }

	void setItemAmount(unsigned index, unsigned newAmount)
	{
		LyingItems[index].lyingItem.ItemAmount = newAmount;
	}
	void clearOldItems(sf::Time currentGameTime)
	{
		while (true)
		{
			if (LyingItems.size() == 0)
			{
				break;
			}
			else if (currentGameTime - LyingItems[0].lyingTime > sf::Time(sf::seconds(600)))
			{
				eraseFirstItem();
			}
			else
			{
				break;
			}
		}
	}

	sf::Vector2f getLyingItemsPickUpRange() { return LyingItemsPickUpRange; }
};