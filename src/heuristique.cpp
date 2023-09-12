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
		vec2 pos = game.find(i);
		vec2 goalPos = goal.find(i);
		val += abs(pos.row - goalPos.row) + abs(pos.col - goalPos.col);
	}
	return val;
}

int linearConflict(Game &game, Game &goal) {
	int count = 0;
	vector<vector<vec2>> goalPos;
	// for each tiles
	for (size_t i = 1; i < game.size * game.size; i++) {
		vec2 pos = game.find(i);
		vec2 goalPos = goal.find(i);
		// if tile is in the correct row but wrong col
		if (pos.row == goalPos.row/* && pos.col != goalPos.col*/) {
			// for each neighbour tiles at his right
			for (size_t col = pos.col + 1; col < game.size; col++) {
				int n = game.grid[pos.row * game.size + col];
				// pass if neighbour is the empty tile
				if (n == 0)
					continue;
				vec2 nGoalPos = goal.find(n);
				// if neighbour is in the correct row and its goal col is at the left of the current tile's goal col
				if (pos.row == nGoalPos.row && nGoalPos.col < goalPos.col)
					count++;
			}
		}
		// if tile is in the correct col but wrong row
		if (pos.col == goalPos.col/* && pos.row != goalPos.row*/) {
			// for each neighbour tiles below it
			for (size_t row = pos.row + 1; row < game.size; row++) {
				int n = game.grid[row * game.size + pos.col];
				// pass if neighbour is the empty tile
				if (n == 0)
					continue;
				vec2 nGoalPos = goal.find(n);
				// if neighbour is in the correct col and its goal row is above the current tile's goal row
				if (pos.col == nGoalPos.col && nGoalPos.row < goalPos.row)
					count++;
			}
		}
	}
	// cout << "Conflict count = " << count << endl;
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
