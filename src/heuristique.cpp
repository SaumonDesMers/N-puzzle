#include "include.hpp"

int manhattanDistance(Game &game, Game &goal) {
	int val = 0;
	for (int i = 1; i < game.size * game.size; i++) {
		vec2 pos = game.find(i);
		vec2 goalPos = goal.find(i);
		val += abs(pos.row - goalPos.row) + abs(pos.col - goalPos.col);
	}
	return val;
}
