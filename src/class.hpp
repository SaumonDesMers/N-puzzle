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

struct vec2;
struct Game;
struct Node;
struct Config;

typedef int (*heuristique_fct)(Game &, Game &);
typedef bool (*sort_fct)(Node *n1, Node *n2);
typedef Node *(*algo_fct)(Config cfg);

struct vec2 {
	int row; int col;
	vec2(int _row = 0, int _col = 0) : row(_row), col(_col) {}
	vec2(string s) {
		string s_row = s.substr(0, s.find_first_not_of("-0123456789"));
		string s_col = s.substr(s.find_last_not_of("-0123456789"), s.size());
		row = atoi(s_row.c_str());
		row = atoi(s_col.c_str());
	}
	vec2(vec2 const &src) : row(src.row), col(src.col) {}
	vec2 &operator=(vec2 const &src) { row = src.row; col = src.col; return *this; }
	bool operator==(vec2 const &src) const { return row == src.row && col == src.col; }
	bool operator!=(vec2 const &src) const { return !(*this == src); }
	void set(int _row, int _col) { row = _row; col = _col; }
	void add(int _row, int _col) { row += _row; col += _col; }
	void add(vec2 &v) { row += v.row; col += v.col; }
	string to_str() { return to_string(row) + " " + to_string(col); }
}; //npos(-1, -1);

struct Game {
	typedef int* Grid;

	Grid grid;
	size_t size;
	size_t emptyPos;

    string hashKey;

	Game() : grid(NULL) {}
	Game(Game const &src) : size(src.size), emptyPos(src.emptyPos), hashKey(src.hashKey) {
        grid = new int[size * size];
        for (size_t i=0; i < size * size; i++)
            grid[i] = src.grid[i];
    }
	Game(Grid _g, size_t _size) : size(_size) {
        grid = new int[size * size];
        for (size_t i=0; i < size * size; i++) {
            grid[i] = _g[i];
			if (grid[i] == 0)
				emptyPos = i;
		}
	}
	Game(vector<int> tab) : size(sqrt(tab.size())) {
        grid = new int[size * size];
		for (size_t i = 0; i < size * size; i++) {
			grid[i] = tab[i];
			if (grid[i] == 0)
				emptyPos = i;
		}
	}

	~Game() {
		delete[] grid;
	}
	
	Game operator=(Game const &src) {
		delete[] grid;
		size = src.size;
		grid = new int[size * size];
        for (size_t i=0; i < size * size; i++)
            grid[i] = src.grid[i];
		emptyPos = src.emptyPos;
		return *this;
	}
	Game operator=(vector<int> tab) {
		delete[] grid;
		size = sqrt(tab.size());
		grid = new int[tab.size()];
		for (size_t i = 0; i < tab.size(); i++) {
			grid[i] = tab[i];
			if (grid[i] == 0)
				emptyPos = i;
		}
		return *this;
	}

	void updateEmptyPos() {
		for (size_t i = 0; i < size; i++) {
			if (grid[i] == 0)
				emptyPos = i;
		}
	}

	int &at(vec2 pos) {
		return grid[pos.row * size + pos.col];
	}

	int &at(size_t pos) {
		return grid[pos];
	}

	bool outOfBound(vec2 pos) {
		return pos.row < 0 || pos.row >= static_cast<int>(size) || pos.col < 0 || pos.col >= static_cast<int>(size);
	}

	vector<Game> getNextTurns() {
		vector<Game> nextTurns;
		vector<size_t> nextEmptyPos;

		size_t emptyPos_row = emptyPos / size;
		size_t emptyPos_col = emptyPos % size;

		if (emptyPos_row > 0) nextEmptyPos.push_back(emptyPos - size);
		if (emptyPos_row < size - 1) nextEmptyPos.push_back(emptyPos + size);
		if (emptyPos_col > 0) nextEmptyPos.push_back(emptyPos - 1);
		if (emptyPos_col < size - 1) nextEmptyPos.push_back(emptyPos + 1);

		for (size_t i = 0; i < nextEmptyPos.size(); i++) {
			Game nextTurn(*this);
			swap(nextTurn.at(nextTurn.emptyPos), nextTurn.at(nextEmptyPos[i]));
			nextTurn.emptyPos = nextEmptyPos[i];
			nextTurns.push_back(nextTurn);
		}
		return nextTurns;
	}

	vec2 find(int val) {
		for (size_t i = 0; i < size * size; i++) {
			if (grid[i] == val)
				return vec2(i / size, i % size);
		}
		return vec2(-1, -1);
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
        vector<int> tab;
        // tab.insert(tab.end(), grid[0], grid[size * size]);
		for (size_t i = 0; i < size * size; i++)
			tab.push_back(grid[i]);
        return tab;
    }

    operator vector<int>() {
        return toTab();
    }

	operator string() {
		string ret;
		for (size_t i = 0; i < size * size; i++)
			ret += to_string(grid[i]);
        return ret;
    }

};

struct Node {
	vector<Node *> childs;
	Node *parent;

	Game game;
	int depth; // GCost
	int HCost;

	Node(Game _g, Node *_p = NULL, int _d = 0, int _hc = 0)
	: childs(vector<Node *>()), parent(_p), game(_g), depth(_d), HCost(_hc) {}
	Node(Node const &src) : childs(src.childs), parent(src.parent), game(src.game), depth(src.depth), HCost(src.HCost) {}
	Node operator=(Node const &src) {
		childs = src.childs;
		parent = src.parent;
		game = src.game;
		depth = src.depth;
		HCost = src.HCost;
		return *this;
	}

	void clear(bool rootReach = false) {
		if (!rootReach && parent != NULL) {
			parent->clear();
			return;
		}
		for (size_t i = 0; i < childs.size(); i++)
			childs[i]->clear(true);
		delete this;
	}

	void expand() {
		vector<Game> nextTurns = game.getNextTurns();
		for (size_t i = 0; i < nextTurns.size(); i++)
			childs.push_back(new Node(nextTurns[i], this, depth + 1));
	}

	void setParent(Node *_p) {
		parent = _p;
		depth = parent->depth + 1;
		for (size_t i = 0; i < childs.size(); i++)
			childs[i]->setParent(this);
	}
};

#endif