#ifndef CLASS_HPP
#define CLASS_HPP

#include <iostream>
#include <iomanip>
#include <string>
#include <vector>
#include <algorithm>
#include <cstdlib>
#include <ctime>
#include <cmath>
#include <map>

using namespace std;

#define ROW 0b1100
#define COL 0b0011

#define LEFT 0b1000
#define RIGHT 0b0100
#define UP 0b0010
#define DOWN 0b0001

struct Move {

	int tileMoved;
	size_t prevPos;
	size_t nextPos;
	int direction;

	Move(int _tileMoved = -1, size_t _prevPos = -1, size_t _nextPos = -1, int _direction = -1)
	: tileMoved(_tileMoved), prevPos(_prevPos), nextPos(_nextPos), direction(_direction) {}

	void log() {
		cout << "{tileMoved: " << tileMoved << ", prevPos: " << prevPos << ", nextPos: " << nextPos << ", direction: " << direction << "}" << endl;
	}

};

struct Game {

	int *grid;
	int *tilesPos;
	size_t size;
	Move lastMove;

	string hashKey;

	Game() : grid(NULL), tilesPos(NULL), size(0), hashKey("") {}

	Game(Game const &src) : size(src.size), lastMove(src.lastMove), hashKey(src.hashKey) {

		grid = new int[size * size];
		tilesPos = new int[size * size];

		for (size_t i = 0; i < size * size; i++) {
			grid[i] = src.grid[i];
			tilesPos[grid[i]] = i;
		}
	}

	Game(Game const &src, Move &move) : size(src.size), lastMove(move) {

		grid = new int[size * size];
		tilesPos = new int[size * size];

		for (size_t i = 0; i < size * size; i++) {
			grid[i] = src.grid[i];
			tilesPos[grid[i]] = i;
		}

		this->move(move);
	}

	Game(vector<int> tab) : size(sqrt(tab.size())), lastMove(Move()) {

		grid = new int[size * size];
		tilesPos = new int[size * size];

		for (size_t i = 0; i < size * size; i++) {
			grid[i] = tab[i];
			tilesPos[grid[i]] = i;
		}

		setHash();
	}

	~Game() {
		clear();
	}

	void clear() {
		delete[] grid;
		delete[] tilesPos;
	}

	vector<Move> getMoves() {
		size_t emptyPos = tilesPos[0];
		vector<Move> moves;

		moves.reserve(4);

		if (emptyPos / size > 0)
			moves.push_back(Move(grid[emptyPos - size], emptyPos - size, emptyPos, UP));
		if (emptyPos / size < size - 1)
			moves.push_back(Move(grid[emptyPos + size], emptyPos + size, emptyPos, DOWN));
		if (emptyPos % size > 0)
			moves.push_back(Move(grid[emptyPos - 1], emptyPos - 1, emptyPos, LEFT));
		if (emptyPos % size < size - 1)
			moves.push_back(Move(grid[emptyPos + 1], emptyPos + 1, emptyPos, RIGHT));
		return moves;
	}

	void move(Move &move) {
		swap(grid[move.prevPos], grid[move.nextPos]);
		tilesPos[grid[move.prevPos]] = move.prevPos;
		tilesPos[grid[move.nextPos]] = move.nextPos;
		setHash();
	}

	void setHash() {
		hashKey.clear();
		for (size_t i = 0; i < size * size; i++)
			hashKey += static_cast<char>(grid[i]);
	}

	void print() {
		for (size_t row = 0; row < size; row++) {
			for (size_t col = 0; col < size; col++) {
				cout << setw(3) << grid[row * size + col];
			}
			cout << endl;
		}
	}

	vector<int> toTab() {
		return vector<int>(grid, grid + size * size);
	}

};

struct Cost {

	int FCost;
	int GCost;
	int HCost;

	int badPlacedTiles;
	int manhattanDistance;
	int linearConflict;

	Cost(int _FCost = 0, int _GCost = 0, int _HCost = 0, int _badPlacedTiles = 0, int _manhattanDistance = 0, int _linearConflict = 0)
	: FCost(_FCost), GCost(_GCost), HCost(_HCost), badPlacedTiles(_badPlacedTiles), manhattanDistance(_manhattanDistance), linearConflict(_linearConflict) {}

};

struct Node {
	vector<Node *> childs;
	Node *parent;

	Game *game;
	int depth; // GCost
	int HCost;
	Cost cost;

	Node(Game * _g, Node *_p = NULL, int _d = 0, int _hc = 0)
	: childs(vector<Node *>()), parent(_p), game(_g), depth(_d), HCost(_hc) {}

	void clear(bool clearParent = false) {
		if (clearParent && parent != NULL) {
			parent->clear(true);
			return;
		}
		for (size_t i = 0; i < childs.size(); i++)
			childs[i]->clear();
		delete game;
		delete this;
	}

	void expand() {
		vector<Move> nextMoves = game->getMoves();
		for (size_t i = 0; i < nextMoves.size(); i++)
			childs.push_back(new Node(new Game(*game, nextMoves[i]), this, depth + 1));
	}

	void setParent(Node *_p) {
		parent = _p;
		depth = parent->depth + 1;
		for (size_t i = 0; i < childs.size(); i++)
			childs[i]->setParent(this);
	}
};

#endif