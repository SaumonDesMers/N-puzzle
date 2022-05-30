#include <iostream>

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <cstdlib>
#include <ctime>
#include <cmath>

using namespace std;

struct vec2;
struct Game;
struct Turn;

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
} npos(-1, -1);

struct Game {
	typedef vector<vector<int>> Grid;

	Grid grid;
	int size;
	vec2 emptyPos;

	Game(int _s = 0, Grid _g = Grid()) : grid(_g), size(_s) {
		for (int i = 0; i < size; i++)
			grid[i].insert(grid[i].begin(), size, 0);
	}
	Game(vector<int> tab, int _s) : size(_s) {
		for (int row = 0; row < size; row++) {
			for (int col = 0; col < size; col++) {
				grid[row].push_back(tab[row * size + col]);
				if (tab[row * size + col] == 0)
					emptyPos.set(row, col);
			}
		}
	}
	Game(Game const &src) : grid(src.grid) {}
	Game operator=(Game const &src) { grid = src.grid; return *this; }

	int &at(vec2 pos) {
		return grid[pos.row][pos.col];
	}

	bool outOfBound(vec2 pos) {
		return pos.row < 0 || pos.row >= size || pos.col < 0 || pos.col >= size;
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
		for (int row = 0; row < size; row++) {
			for (int col = 0; col < size; col++) {
				if (grid[row][col] == val)
					return vec2(row, col);
			}
		}
		return npos;
	}

	void print() {
		for (int row = 0; row < size; row++) {
			for (int col = 0; col < size; col++) {
				cout << grid[row][col];
			}
			cout << endl;
		}
	}

};

struct Node {
	vector<Node *> childs;
	Node *parent;

	Game game;

	Node(Game _g, Node *_p = NULL) : childs(vector<Node *>()), parent(_p), game(_g) {}
	Node(Node const &src) : childs(src.childs), parent(src.parent), game(src.game) {}
	Node operator=(Node const &src) {
		childs = src.childs;
		parent = src.parent;
		game = src.game;
		return *this;
	}

	void clear() {
		for (size_t i = 0; i < childs.size(); i++)
			childs[i]->clear();
		delete this;
	}

	void expand() {
		vector<Game> nextTurns = game.getNextTurns();
		for (size_t i = 0; i < nextTurns.size(); i++)
			childs.push_back(new Node(nextTurns[i], this));
	}

};

int manhattanDistance(Game &game, Game &goal) {
	int val = 0;
	for (int i = 1; i < game.size * game.size; i++) {
		vec2 pos = game.find(i);
		vec2 goalPos = goal.find(i);
		val += abs(pos.row - goalPos.row) + abs(pos.col - goalPos.col);
	}
	return val;
}

Node *AStart(Game start, Game goal, int (*heuristique)(Game &, Game &), int nb = -1) {
	vector<Node *> open;
	vector<Node *> closed;
	Node *root = new Node(start);

	open.push_back(root);

	while (--nb) {
		Node *current = open.back();
		open.pop_back();
		closed.push_back(current);

		if (heuristique(current->game, goal) == 0)
			return current;

		current->expand();

		for (size_t i = 0; i < current->childs.size(); i++) {
			open.push_back(current->childs[i]);
		}

		if (open.empty())
			break;

		sort(open.begin(), open.end(), [heuristique, &goal](Node *n1, Node *n2) {
			return heuristique(n1->game, goal) < heuristique(n2->game, goal);
		});

		// for (size_t i = 0; i < open.size(); i++)
		// 	cerr << "(" << heuristique(open[i]->game, goal) << ") ";
		// cerr << endl;
	}
	return NULL;
}

int main(int argc, char const *argv[])
{
	(void)argc;
	(void)argv;

	vector<int> goal = {1,2,3,8,0,4,7,6,5};
	vector<int> start = {1,2,3,8,0,4,7,6,5};

	Node *n = AStart(Game(start, 3), Game(goal, 3), manhattanDistance, 100);

	if (n == NULL)
		cout << "No solution found" << endl;
	else {
		cout << "Solution found" << endl;
	}

	return 0;
}
