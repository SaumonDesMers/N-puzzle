#ifndef INCLUDE_HPP
#define INCLUDE_HPP

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <cstdlib>
#include <ctime>
#include <cmath>
#include "class.hpp"

using namespace std;

typedef int (*heuristique_fct)(Game &, Game &);
typedef bool (*sort_fct)(Node *n1, Node *n2);
typedef Node *(*algo_fct)(Game start, Game goal, sort_fct sort, int (*h)(Game &, Game &), int nb);

Node *AStart(Game start, Game goal, sort_fct sort, heuristique_fct h, int maxIter = -1);

bool isSolvable(vector<int> game, vector<int> goal);

Game randomGame(size_t size);
Game shuffleGame(Game game, size_t shuffleNb);
Game goalGeneration(size_t size, string type = string());

int manhattanDistance(Game &game, Game &goal);

bool uniformCostSearch_withDepth(Node *n1, Node *n2);
bool uniformCostSearch_withCost(Node *n1, Node *n2);
bool greedySearch(Node *n1, Node *n2);

void printTab(vector<int> tab, string sep = string());

#endif