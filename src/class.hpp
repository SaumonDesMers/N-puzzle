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

using namespace std;

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
	string to_str() { return to_string(col) + " " + to_string(row); }
}; //npos(-1, -1);

struct Game {
	typedef vector<vector<int> > Grid;

	Grid grid;
	size_t size;
	vec2 emptyPos;

	Game() {}
	Game(Game const &src) : grid(src.grid), size(src.size), emptyPos(src.emptyPos) {}
	Game(Grid _g) : grid(_g), size(_g.size()) {
		updateEmptyPos();
	}
	Game(vector<int> tab) : size(sqrt(tab.size())) {
		for (size_t row = 0; row < size; row++) {
			grid.push_back(vector<int>());
			for (size_t col = 0; col < size; col++) {
				grid[row].push_back(tab[row * size + col]);
				if (tab[row * size + col] == 0)
					emptyPos.set(row, col);
			}
		}
	}
	
	Game operator=(Game const &src) {
		grid = src.grid;
		size = src.size;
		emptyPos = src.emptyPos;
		return *this;
	}
	Game operator=(Grid _g) {
		grid = _g;
		size = _g.size();
		updateEmptyPos();
		return *this;
	}
	Game operator=(vector<int> tab) {
		size = sqrt(tab.size());
		for (size_t row = 0; row < size; row++) {
			grid.push_back(vector<int>());
			for (size_t col = 0; col < size; col++) {
				grid[row].push_back(tab[row * size + col]);
				if (tab[row * size + col] == 0)
					emptyPos.set(row, col);
			}
		}
		return *this;
	}

	void updateEmptyPos() {
		for (size_t row = 0; row < size; row++) {
			for (size_t col = 0; col < size; col++) {
				if (grid[row][col] == 0)
					emptyPos.set(row, col);
			}
		}
	}

	int &at(vec2 pos) {
		return grid[pos.row][pos.col];
	}

	int &at(int pos) {
		return grid[pos / size][pos % size];
	}

	bool outOfBound(vec2 pos) {
		return pos.row < 0 || pos.row >= static_cast<int>(size) || pos.col < 0 || pos.col >= static_cast<int>(size);
	}

	vector<Game> getNextTurns() {
		vector<Game> nextTurns;
		vector<vec2> nextEmptyPos = {
			vec2(emptyPos.row, emptyPos.col + 1),
			vec2(emptyPos.row, emptyPos.col - 1),
			vec2(emptyPos.row + 1, emptyPos.col),
			vec2(emptyPos.row - 1, emptyPos.col)
		};
		for (size_t i = 0; i < 4; i++) {
			if (!outOfBound(nextEmptyPos[i])) {
				Game nextTurn(*this);
				swap(nextTurn.at(nextTurn.emptyPos), nextTurn.at(nextEmptyPos[i]));
				nextTurn.emptyPos = nextEmptyPos[i];
				nextTurns.push_back(nextTurn);
			}
		}
		return nextTurns;
	}

	vec2 find(int val) {
		for (size_t row = 0; row < size; row++) {
			for (size_t col = 0; col < size; col++) {
				if (grid[row][col] == val)
					return vec2(row, col);
			}
		}
		return vec2(-1, -1);
	}

	void print() {
		for (size_t row = 0; row < size; row++) {
			for (size_t col = 0; col < size; col++) {
				cout << setw(3) << grid[row][col];
			}
			cout << endl;
		}
	}

    vector<int> toTab() {
        vector<int> tab;
        for (size_t i = 0; i < size; i++)
            tab.insert(tab.end(), grid[i].begin(), grid[i].end());
        return tab;
    }

    operator vector<int>() {
        return toTab();
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