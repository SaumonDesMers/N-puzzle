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

Node *AStart(Game start, Game goal, int (*heuristique)(Game &, Game &), int nb = -1);

bool isSolvable(vector<int> game, vector<int> goal);

Game randomGame(size_t size);
Game shuffleGame(Game game, size_t shuffleNb);
Game goalGeneration(size_t size, string type = string());

int manhattanDistance(Game &game, Game &goal);

void printTab(vector<int> tab, string sep = string());

#endif