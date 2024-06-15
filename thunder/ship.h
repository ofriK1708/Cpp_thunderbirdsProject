#ifndef SHIP_H
#define SHIP_H
#include <map>
#include "point.h"
#include "utils.h"
class Board;
class Block;
using std::map;
class Ship
{
private:
	Board* board;
	Point pos[GameConfig::MAX_SHIP_SIZE];
	Point nextPos[GameConfig::MAX_SHIP_SIZE];
	Point finishPos[GameConfig::MAX_SHIP_SIZE];
	size_t size = 0;
	size_t finishSize = 0;
	char symbol;
	bool isFinished;
	bool OverLoaded = false;
	int maxCarryWeight;
	GameConfig::Color backgroundcolor;
	LocationInfo shipLocationinfo;
	void delTrace();
	LocationInfo& checkNextObjLocation(GameConfig::eKeys direction, int* carryWeight);
	map<const char,Block*> trunk;
public:
	void init(char symbol, int maxCarryWeight, GameConfig::Color color, Board* Board);
	size_t getSize() const { return size; }
	Point getPos(size_t i) const { return pos[i]; }
	char getSymbol() const { return symbol; }
	GameConfig::Color getBackgroundColor() const { return backgroundcolor; }
	void addPoint(int x, int y) { pos[size++].set(x, y); }
	void addFinishPoint(int x, int y) { finishPos[finishSize++].set(x, y); }
	bool move(GameConfig::eKeys direction);
	void shipFinishLine();
	bool GetFinishStatus() { return isFinished; }
	static bool isShip(char ch);
	auto addToTrunk(const char key, Block* block) { auto result = trunk.insert({ key, block }); return result.second; }
	void removeFromTrunk(const char key) { trunk.erase(key);}
	int getMaxCarryWeight() const { return maxCarryWeight; }
	size_t getTrunkWeight() const;
	void setOverLoaded(bool state) { OverLoaded = true; }
	bool isOverLoaded() const { return OverLoaded; }
		
	
};

#endif
