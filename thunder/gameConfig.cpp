#include "gameConfig.h"


const char GameConfig::SHIPS_SYMBOLS[] = {'#', '@'};
const GameConfig::Color GameConfig::SHIPS_COLORS[][NUM_SHIPS] = {{WHITE, WHITE}, {PURPLE, TURQUOISE}};

const char GameConfig::BLOCK_SYMBOLS[] = { '0', '1', '2', '3', '4', '5', '6', '7', '8', '9' };
const int GameConfig::SHIP_MAX_WEIGHT[NUM_SHIPS] = { 6, 2 };
