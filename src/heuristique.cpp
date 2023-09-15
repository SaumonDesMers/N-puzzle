#include "include.hpp"

int badPlacedTiles(Node *node, Game *goal) {
	Game *game = node->game;
	int val = 0;
	for (size_t i = 0; i < game->size * game->size; i++)
		val += (game->at(i) == goal->at(i) ? 0 : 1);

	// this is not needed because not used
	// node->cost.badPlacedTiles = val;
	// node->cost.FCost = val;

	return val;
}

#define MANDIS(pos, goalPos, size) ::abs(pos / size - goalPos / size) + ::abs(pos % size - goalPos % size)

int manhattanDistance(Node *node, Game *goal) {
	Game *game = node->game;
	int size = game->size;

	// manhattan distance taking parent cost into account
	if (node->parent != NULL) {
		int movedTileGoalPos = goal->tilesPos[node->game->lastMove.tileMoved];
		
		// manhattan distance of the moved tile in the parent node
		int movedTileParentPos = node->game->lastMove.prevPos;
		int movedTileParentManDis = MANDIS(movedTileParentPos, movedTileGoalPos, size);

		// manhattan distance of the moved tile in the current node
		int movedTilePos = node->game->lastMove.nextPos;
		int movedTileManDis = MANDIS(movedTilePos, movedTileGoalPos, size);

		node->cost.manhattanDistance = node->parent->cost.manhattanDistance + movedTileManDis - movedTileParentManDis;

		// cerr << "movedTile = " << node->game->lastMove.tileMoved << endl;
		// cerr << "movedTileGoalPos = " << movedTileGoalPos << endl;
		// cerr << "movedTileParentPos = " << movedTileParentPos << endl;
		// cerr << "movedTileParentManDis = " << movedTileParentManDis << endl;
		// cerr << "movedTilePos = " << movedTilePos << endl;
		// cerr << "movedTileManDis = " << movedTileManDis << endl;
		// cerr << "HCost = " << node->cost.manhattanDistance << "\n" << endl;
		return node->cost.manhattanDistance;
	}

	// manhattan distance without taking parent cost into account
	int val = 0;
	for (size_t i = 1; i < game->size * game->size; i++) {
		val += MANDIS(game->tilesPos[i], goal->tilesPos[i], size);
	}
	// cerr << "HCost = " << val << "\n" << endl;
	node->cost.manhattanDistance = val;
	return val;

}

int linearConflict(Node *node, Game *goal) {
	Game *game = node->game;
	int count = 0;
	int size = game->size;
	// for each tiles
	for (size_t i = 1; i < game->size * game->size; i++) {

		// vec2 pos = game->find(i);
		// vec2 goalPos = goal->find(i);
		int pos = game->tilesPos[i];
		int goalPos = goal->tilesPos[i];

		// if tile is in the correct row but wrong col
		if (pos / size == goalPos / size/* && pos % size != goalPos % size*/) {
			// for each neighbour tiles at his right
			for (size_t col = pos % size + 1; col < game->size; col++) {
				int n = game->grid[pos / size * game->size + col];
				// pass if neighbour is the empty tile
				if (n == 0)
					continue;
				// vec2 nGoalPos = goal->find(n);
				int nGoalPos = goal->tilesPos[n];
				// if neighbour is in the correct row and its goal col is at the left of the current tile's goal col
				if (pos / size == nGoalPos / size && nGoalPos % size < goalPos % size)
					count++;
			}
		}
		// if tile is in the correct col but wrong row
		if (pos % size == goalPos % size/* && pos / size != goalPos / size*/) {
			// for each neighbour tiles below it
			for (size_t row = pos / size + 1; row < game->size; row++) {
				int n = game->grid[row * game->size + pos % size];
				// pass if neighbour is the empty tile
				if (n == 0)
					continue;
				// vec2 nGoalPos = goal->find(n);
				int nGoalPos = goal->tilesPos[n];
				// if neighbour is in the correct col and its goal row is above the current tile's goal row
				if (pos % size == nGoalPos % size && nGoalPos / size < goalPos / size)
					count++;
			}
		}
	}
	return 2 * count;
}

int manDist_linCon(Node *node, Game *goal) {
	return manhattanDistance(node, goal) + linearConflict(node, goal);
}

int uniformCostSearch(Node *n) {
	return n->depth + n->HCost;
}

int greedySearch(Node *n) {
	return n->HCost;
}
