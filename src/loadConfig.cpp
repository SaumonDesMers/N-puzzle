#include "include.hpp"

void loadConfig(Config& config) {
    ifstream fin("config.txt");
    string line;
    string name;
    
    while (getline(fin, line)) {
        istringstream sin(line.substr(line.find("=") + 1));
        if (line.find("algorithme") != -1) {
            sin >> name;
            if (name == "AStart")
                config.algo = AStart;
        }
        else if (line.find("maxIteration") != -1)
            sin >> config.maxIter;
        else if (line.find("weight") != -1)
            sin >> config.weight;
        else if (line.find("sortingfFunction") != -1) {
            sin >> name;
            if (name == "uniformCost")
                config.sortSearch = uniformCostSearch;
            else if (name == "greedy")
                config.sortSearch = greedySearch;
        }
        else if (line.find("heuristique") != -1) {
            sin >> name;
            if (name == "badPlacedTiles")
                config.h = badPlacedTiles;
            else if (name == "manhattanDistance")
                config.h = manhattanDistance;
            else if (name == "manhattanDistance_linearConflict")
                config.h = manDist_linCon;
        }
    }
}
