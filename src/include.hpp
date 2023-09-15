#ifndef INCLUDE_HPP
#define INCLUDE_HPP

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <cstdlib>
#include <ctime>
#include <cmath>
#include <cstring>
#include <fstream>
#include <sstream>
#include <chrono>
#include <unordered_map>
#include <climits>
#include "class.hpp"

using namespace std;

struct Config;

bool parseGame(string fileName, Game *&game);

Node *AStar(Config &cfg);
Node *IDAStar(Config &cfg);
Node *iterativeBrainless(Config &cfg);
Node *recursiveBrainless(Config &cfg);

bool isSolvable(vector<int> game, vector<int> goal);

Game * randomGame(size_t size);
Game * shuffleGame(Game * game, size_t shuffleNb);
Game * goalGeneration(size_t size, string type = string());

int badPlacedTiles(Node *gameNode, Game *goal);
int manhattanDistance(Node *gameNode, Game *goal);
int manDist_linCon(Node *gameNode, Game *goal);
int linearConflict(Node *gameNode, Game *goal);

int uniformCostSearch(Node *n);
int greedySearch(Node *n);

void printTab(vector<int> tab, string sep = string());
void getSolution(Node *n);
vector<string> split(string str, string delim);
void printTime(chrono::duration<double> elapsed_seconds, string msg);
void printTree(Node* node);

#endif