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

	// TODO: optimize this by storing the manhattan distance of each tile in the node

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

		return node->cost.manhattanDistance;
	}

	// manhattan distance without taking parent cost into account
	int val = 0;
	for (size_t i = 1; i < game->size * game->size; i++) {
		val += MANDIS(game->tilesPos[i], goal->tilesPos[i], size);
	}
	
	node->cost.manhattanDistance = val;
	return val;

}

int linearConflict(Node *node, Game *goal) {
	Game *game = node->game;
	int count = 0;
	int size = game->size;
	// for each tiles
	for (size_t i = 1; i < game->size * game->size; i++) {

		int pos = game->tilesPos[i];
		int goalPos = goal->tilesPos[i];

		// if tile is in the correct row
		if (pos / size == goalPos / size) {
			// for each neighbour tiles at his right
			for (size_t col = pos % size + 1; col < game->size; col++) {
				int n = game->grid[pos / size * game->size + col];

				// pass if neighbour is the empty tile
				if (n == 0)
					continue;
				
				int nGoalPos = goal->tilesPos[n];
				// if neighbour is in the correct row and its goal col is at the left of the current tile's goal col
				if (pos / size == nGoalPos / size && nGoalPos % size < goalPos % size)
					count++;
			}
		}
		// if tile is in the correct col
		if (pos % size == goalPos % size) {
			// for each neighbour tiles below it
			for (size_t row = pos / size + 1; row < game->size; row++) {
				int n = game->grid[row * game->size + pos % size];

				// pass if neighbour is the empty tile
				if (n == 0)
					continue;
				
				int nGoalPos = goal->tilesPos[n];
				// if neighbour is in the correct col and its goal row is above the current tile's goal row
				if (pos % size == nGoalPos % size && nGoalPos / size < goalPos / size)
					count++;
			}
		}
	}
	// cout << "linearConflict = " << 2 * count << endl;
	return 2 * count;
}

// linear conflict on one row
int linearConfict_row(Game *game, Game *goal, size_t row) {
	int count = 0;
	int size = game->size;

	// for each tiles in that row
	for (size_t col = 0; col < game->size; col++) {

		int pos = row * size + col;

		// pass if tile is empty
		if (game->grid[pos] == 0)
			continue;

		int goalPos = goal->tilesPos[game->grid[pos]];

		// if tile is in the correct row
		if (pos / size == goalPos / size) {
			
			// for each neighbour tiles at his right
			for (size_t n_col = col + 1; n_col < game->size; n_col++) {
				int n = game->grid[pos + n_col - col];

				// pass if neighbour is the empty tile
				if (n == 0)
					continue;

				int nGoalPos = goal->tilesPos[n];
				// if neighbour is in the correct row and its goal col is at the left of the current tile's goal col
				if (pos / size == nGoalPos / size && nGoalPos % size < goalPos % size) {
					// cout << "neighbour is in the correct row and its goal col is at the left of the current tile's goal col" << endl;
					count++;
				}
			}
		}
	}
	return 2 * count;
}

// linear conflict on one col
int linearConfict_col(Game *game, Game *goal, size_t col) {
	int count = 0;
	int size = game->size;

	// for each tiles in that col
	for (size_t row = 0; row < game->size; row++) {

		int pos = row * size + col;

		// pass if tile is empty
		if (game->grid[pos] == 0)
			continue;

		int goalPos = goal->tilesPos[game->grid[pos]];

		// if tile is in the correct col
		if (pos % size == goalPos % size) {

			// for each neighbour tiles below it
			for (size_t n_row = row + 1; n_row < game->size; n_row++) {
				int n = game->grid[pos + (n_row - row) * size];

				// pass if neighbour is the empty tile
				if (n == 0)
					continue;

				int nGoalPos = goal->tilesPos[n];
				// if neighbour is in the correct col and its goal row is above the current tile's goal row
				if (pos % size == nGoalPos % size && nGoalPos / size < goalPos / size) {
					// cout << "neighbour is in the correct col and its goal row is above the current tile's goal row" << endl;
					count++;
				}
			}
		}
	}
	return 2 * count;
}

// linear conflict taking parent cost into account
int linearConflict_opti(Node *node, Game *goal) {
	
	// if node has no parent, return linearConflict
	if (node->parent == NULL) {
		node->cost.linearConflict = linearConflict(node, goal);
		return node->cost.linearConflict;
	}

	Game *game = node->game;
	int size = game->size;

	// TODO: optimize this by storing the linear conflict of each row and col in the node

	// if node has a parent, determine the two rows or cols that have been modified
	if (node->game->lastMove.direction & ROW) {
		// Last move was a row move (left or right) so we need to check the two cols that have been modified
		// The linear conflict of the modified row is the same as the parent node

		// get the two cols that have been modified
		size_t col_1 = node->game->lastMove.prevPos % size;
		size_t col_2 = node->game->lastMove.nextPos % size;

		// get the linear conflict of the two cols for the parent node
		int prev_lc1 = linearConfict_col(node->parent->game, goal, col_1);
		int prev_lc2 = linearConfict_col(node->parent->game, goal, col_2);

		// get the linear conflict of the two cols for the current node
		int lc1 = linearConfict_col(node->game, goal, col_1);
		int lc2 = linearConfict_col(node->game, goal, col_2);

		// update the linear conflict of the current node by substracting the linear conflict of the parent node and adding the linear conflict of the current node
		node->cost.linearConflict = node->parent->cost.linearConflict - prev_lc1 - prev_lc2 + lc1 + lc2;


	} else {
		// Last move was a col move (up or down) so we need to check the two rows that have been modified
		// The linear conflict of the modified col is the same as the parent node

		// get the two rows that have been modified
		size_t row_1 = node->game->lastMove.prevPos / size;
		size_t row_2 = node->game->lastMove.nextPos / size;

		// get the linear conflict of the two rows for the parent node
		int prev_lc1 = linearConfict_row(node->parent->game, goal, row_1);
		int prev_lc2 = linearConfict_row(node->parent->game, goal, row_2);

		// get the linear conflict of the two rows for the current node
		int lc1 = linearConfict_row(node->game, goal, row_1);
		int lc2 = linearConfict_row(node->game, goal, row_2);

		// update the linear conflict of the current node by substracting the linear conflict of the parent node and adding the linear conflict of the current node
		node->cost.linearConflict = node->parent->cost.linearConflict - prev_lc1 - prev_lc2 + lc1 + lc2;

	}

	return node->cost.linearConflict;
}

int manDist_linCon(Node *node, Game *goal) {
	node->cost.HCost = manhattanDistance(node, goal) + linearConflict_opti(node, goal);
	return node->cost.HCost;
}

int uniformCostSearch(Node *n) {
	return n->depth + n->HCost;
}

int greedySearch(Node *n) {
	return n->HCost;
}
