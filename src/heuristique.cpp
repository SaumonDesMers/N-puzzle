#include "include.hpp"

int manhattanDistance(Game &game, Game &goal) {
	int val = 0;
	for (size_t i = 1; i < game.size * game.size; i++) {
		vec2 pos = game.find(i);
		vec2 goalPos = goal.find(i);
		val += abs(pos.row - goalPos.row) + abs(pos.col - goalPos.col);
	}
	return val;
}

int badPlacedTiles(Game &game, Game &goal) {
	int val = 0;
	for (size_t i = 0; i < game.size * game.size; i++)
		val += (game.at(i) == goal.at(i) ? 0 : 1);
	return val;
}

bool uniformCostSearch(Node *n1, Node *n2) {
	return n1->depth + n1->HCost > n2->depth + n2->HCost;
}

bool greedySearch(Node *n1, Node *n2) {
	return n1->HCost > n2->HCost;
}
