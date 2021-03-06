#pragma once

#include "Recipe.hpp"

#include <SFML/Graphics/Rect.hpp>
#include <string>

typedef std::pair<std::string, unsigned> Yield;
typedef std::vector<Yield> ObjYield;

const std::string NULL_ITEM_YIELD{ "NULL" };
const std::string SELF_ITEM_YIELD{ "SELF" };

enum class ObjectType
{
	Default,
	Chest,
	CraftingPlace,
	Tree,
	Sapling,
	Spawner
};

inline std::string ObjectTypeToString(ObjectType type)
{
	std::string ret("Object::");
	switch (type)
	{
	case ObjectType::Default:
		ret += "Default";
		break;
	case ObjectType::Chest:
		ret += "Chest";
		break;
	case ObjectType::CraftingPlace:
		ret += "CraftingPlace";
		break;
	case ObjectType::Tree:
		ret += "Tree";
		break;
	case ObjectType::Sapling:
		ret += "Sapling";
		break;
	case ObjectType::Spawner:
		ret += "Spawner";
		break;
	default:
		ret += "!IsUndefided";
		break;
	}
	return ret;
}

class ObjectDef
{
	ObjectType type;
	std::string ObjName;
	bool ObjCollision;
	bool ObjDestructible;
	ObjYield Yield;

public:
	ObjectDef()
		:ObjDestructible(false), ObjName(), Yield(), ObjCollision(false), type(ObjectType::Default)
	{}
	ObjectDef(const ObjectDef &other) = delete;
	ObjectDef(ObjectDef &&other) = delete;
	ObjectDef(const std::string &Name, const ObjYield &yield, bool Destructible, bool Collision, ObjectType type = ObjectType::Default)
		:ObjDestructible(Destructible), ObjName(Name), Yield(yield), type(type), ObjCollision(Collision)
	{}
	virtual ~ObjectDef() = default;


	ObjectDef &operator=(const ObjectDef &other) = delete;
	ObjectDef &operator=(ObjectDef &&other) = delete;


	ObjectType getType() const
	{
		return type;
	}
	std::string getName() const
	{
		return ObjName;
	}
	bool getCollision() const
	{
		return ObjCollision;
	}
	bool getDestructible() const
	{
		return ObjDestructible;
	}
	const ObjYield &getYield() const
	{
		return Yield;
	}
};

class ChestDef : public ObjectDef
{
	unsigned Capacity;

public:
	ChestDef() = delete;
	ChestDef(const std::string &Name, bool HaveCollision, const ObjYield &yield, bool Destructible, unsigned ChestCapacity)
		:ObjectDef(Name, yield, Destructible, HaveCollision, ObjectType::Chest), Capacity(ChestCapacity)
	{}
	~ChestDef() = default;


	unsigned getCapacity() const
	{
		return Capacity;
	}
};

class CraftingPlaceDef : public ObjectDef
{
	std::vector<RecipeDef> Recipes;

public:
	CraftingPlaceDef() = delete;
	CraftingPlaceDef(const std::string &Name, const ObjYield &yield, 
		bool Destructible, bool HaveCollision, const std::vector<RecipeDef> &RecipeVect)
		:ObjectDef(Name, yield, Destructible, HaveCollision, ObjectType::CraftingPlace), Recipes(RecipeVect)
	{}
	~CraftingPlaceDef() = default;


	const std::vector<RecipeDef> & getRecipes() const
	{
		return Recipes;
	}
};

class SaplingDef : public ObjectDef
{
	float GrowTime;
	std::string GrowTo;

public:
	SaplingDef() = delete;
	SaplingDef(const std::string &Name, bool HaveCollision, const ObjYield &yield,
		bool Destructible, float TimeForGrow, const std::string &For)
		:ObjectDef(Name, yield, Destructible, HaveCollision, ObjectType::Sapling), GrowTo(For), GrowTime(TimeForGrow)
	{}
	~SaplingDef() = default;


	float getGrowTime() const
	{
		return GrowTime;
	}
	std::string getGrowTo() const
	{
		return GrowTo;
	}
};

class SpawnerDef : public ObjectDef
{
	float SpawnTime;
	std::string MonsterName;

public:
	SpawnerDef() = delete;
	SpawnerDef(const std::string &Name, bool HaveCollision, const ObjYield &yield,
		bool Destructible, float TimeForSpawn, const std::string &MonsterToSpawn)
		:ObjectDef(Name, yield, Destructible, HaveCollision, ObjectType::Spawner), SpawnTime(TimeForSpawn), MonsterName(MonsterToSpawn)
	{}
	~SpawnerDef() = default;


	float getSpawnTime() const
	{
		return SpawnTime;
	}
	std::string getMonsterName() const
	{
		return MonsterName;
	}
};