#include "include.hpp"
#include "config.hpp"

#define FOUND -1

Node *solution = NULL;

int recusiveSearch(Node *current, int g, int limit, Config &cfg) {
	static unordered_map<string, Node *> explored;
	unordered_map<string, Node *>::iterator it = explored.find(current->game->hashKey);
	if (it == explored.end()) {
		current->cost.H = cfg.h(current, cfg.goal);

		if (current->cost.H == 0) {
			solution = current;
			return FOUND;
		}

		current->expand();
		explored[current->game->hashKey] = current;
	}
	else {
		current = it->second;
	}

	int f = g + current->cost.H;
	if (f > limit)
		return f;

	int minLimit = INT_MAX;
	for (size_t i = 0; i < current->childs.size(); i++) {
		int tmp = recusiveSearch(current->childs[i], g + 1, limit, cfg);
		if (tmp == FOUND)
			return FOUND;
		minLimit = min(minLimit, tmp);
	}
	return minLimit;
}

Node *IDAStar(Config &cfg) {
    cout << "------- IDAStar -------" << endl;

	auto start = chrono::system_clock::now();
	auto end = chrono::system_clock::now();

	Node *root = new Node(new Game(*cfg.start)); // copy of start to avoid double free (start and goal are deleted in Config destructor)
	int limit = cfg.h(root, cfg.goal);
	int i = 0;
	for (; i < cfg.maxIter; i++) {
		int tmp = recusiveSearch(root, 0, limit, cfg);
		if (tmp == FOUND)
			break;
		limit = tmp;
	}

	end = chrono::system_clock::now();

	cout << "Iteration count = " << i << endl;
	getSolution(solution);
	printTime(end-start, "execution time = ");
    cout << "------------------------" << endl;
	root->clear();
	return NULL;
}
