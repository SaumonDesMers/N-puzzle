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

// bool isSolvable(Game game, Game goal);
bool isSolvable(vector<int> game, vector<int> goal);

Game randomGame(size_t size);
Game shuffleGame(Game game, size_t shuffleNb);

#endif