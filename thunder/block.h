#ifndef BLOCK_H
#define BLOCK_H

#include "point.h"
#include "utils.h"

class Board;
class Ship;
class Block
{
private:
	static GameConfig::Color backgroundcolor;
	Board* board;
	Point pos[GameConfig::MAX_BLOCK_SIZE];
	Point nextPos[GameConfig::MAX_BLOCK_SIZE];
	unsigned int size = 0;
	LocationInfo locationInfo;
	//char carrierShipID = '\0';	
	char symbol = NULL;
	//bool isCarried = false;
	Ship* carrierShip = nullptr;
	void delTrace();

public:
	Block(){};
	Block(char symbol, Board* board) : symbol(symbol), board(board) {};
	static GameConfig::Color getBackgroundColor() { return backgroundcolor; }
	static void setColor(GameConfig::Color color) { backgroundcolor = color; }	
	void addPoint(int x, int y) { pos[size++].set(x, y); }
	bool move(GameConfig::eKeys direction = GameConfig::eKeys::DOWN, int* carryWeight = nullptr, bool onCommand = false);
	char getSymbol() const { return symbol; }
	bool checkMove(GameConfig::eKeys direction, int* carryWeight);
	unsigned int getSize() const { return size; }
	Point getPos(size_t i) const { return pos[i]; }
	bool static isBlock(char ch);
	
	
	//void setCarrierShipID(char carrierShipID) { this->carrierShipID = carrierShipID; }
	char getCarrierShipID() const;
	bool checkFall(Block* blockToCarry = nullptr, char keyCargoBlock = '\0');
	//void setCarriedBlock(bool isCarried) { this->isCarried = isCarried; }
	bool isCarriedBlock() const { return carrierShip != nullptr; }
	void setCarrierShip(Ship* carrierShip) { this->carrierShip = carrierShip; }
	void removeCarrierShip() { carrierShip = nullptr; }
	Ship* getCarrierShip() const { return carrierShip; }
};

#endif
