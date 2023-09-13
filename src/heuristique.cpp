#include "include.hpp"

int badPlacedTiles(Game &game, Game &goal) {
	int val = 0;
	for (size_t i = 0; i < game.size * game.size; i++)
		val += (game.at(i) == goal.at(i) ? 0 : 1);
	return val;
}

int manhattanDistance(Game &game, Game &goal) {
	int val = 0;
	for (size_t i = 1; i < game.size * game.size; i++) {
		int size = game.size;
		val += ::abs(game.tilesPos[i] / size - goal.tilesPos[i] / size) + ::abs(game.tilesPos[i] % size - goal.tilesPos[i] % size);
	}
	return val;
}

int linearConflict(Game &game, Game &goal) {
	int count = 0;
	int size = game.size;
	// for each tiles
	for (size_t i = 1; i < game.size * game.size; i++) {

		// vec2 pos = game.find(i);
		// vec2 goalPos = goal.find(i);
		int pos = game.tilesPos[i];
		int goalPos = goal.tilesPos[i];

		// if tile is in the correct row but wrong col
		if (pos / size == goalPos / size/* && pos % size != goalPos % size*/) {
			// for each neighbour tiles at his right
			for (size_t col = pos % size + 1; col < game.size; col++) {
				int n = game.grid[pos / size * game.size + col];
				// pass if neighbour is the empty tile
				if (n == 0)
					continue;
				// vec2 nGoalPos = goal.find(n);
				int nGoalPos = goal.tilesPos[n];
				// if neighbour is in the correct row and its goal col is at the left of the current tile's goal col
				if (pos / size == nGoalPos / size && nGoalPos % size < goalPos % size)
					count++;
			}
		}
		// if tile is in the correct col but wrong row
		if (pos % size == goalPos % size/* && pos / size != goalPos / size*/) {
			// for each neighbour tiles below it
			for (size_t row = pos / size + 1; row < game.size; row++) {
				int n = game.grid[row * game.size + pos % size];
				// pass if neighbour is the empty tile
				if (n == 0)
					continue;
				// vec2 nGoalPos = goal.find(n);
				int nGoalPos = goal.tilesPos[n];
				// if neighbour is in the correct col and its goal row is above the current tile's goal row
				if (pos % size == nGoalPos % size && nGoalPos / size < goalPos / size)
					count++;
			}
		}
	}
	return count;
}

int manDist_linCon(Game &game, Game &goal) {
	return manhattanDistance(game, goal) + 2 * linearConflict(game, goal);
}

bool uniformCostSearch(Node *n1, Node *n2) {
	return n1->depth + n1->HCost > n2->depth + n2->HCost;
}

bool greedySearch(Node *n1, Node *n2) {
	return n1->HCost > n2->HCost;
}
