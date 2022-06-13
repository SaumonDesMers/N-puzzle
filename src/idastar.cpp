#include "include.hpp"
#include "config.hpp"

#define FOUND -1

Node *IDAStar(Config cfg) {
	int limit = cfg.h(cfg.start, cfg.goal);
	int i = 0;
	Node *start = new Node(cfg.start);
	Node *goal = new Node(cfg.goal);
	for (; i < cfg.maxIter; i++) {
		int tmp = recusiveSearch(start, goal, 0, limit, cfg.h);
		if (tmp == FOUND)
			return NULL; // FOUND
		limit = tmp;
	}
}

int recusiveSearch(Node *current, Node *goal, int g, int limit, heuristique_fct h) {
	int f = g + h(current->game, goal->game);
	if (f > limit)
		return f;
	
}