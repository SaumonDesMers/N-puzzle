#include "include.hpp"

struct Config {
	map<string, string> args;
	algo_fct algo;
	int maxIter;
	int weight;
	sort_fct sortSearch;
	heuristique_fct h;
	Game goal;
	Game start;
	size_t size;

	bool load() {
		if (readFile() == EXIT_FAILURE)
			return EXIT_FAILURE;
		if (parse() == EXIT_FAILURE)
			return EXIT_FAILURE;
		return EXIT_SUCCESS;
	}

	bool readFile() {
		ifstream fin("n-puzzle.conf");
		string line;

		while (getline(fin, line)) {
			line = line.substr(0, line.find("#") == string::npos ? line.size() : line.find("#"));
			if (line.empty())
				continue;
			if (line.find("=") == string::npos)
				return EXIT_FAILURE;

			vector<string> tab = split(line, " =");
			args[tab[0]] = tab[1];
		}
		return args.size() == 7 ? EXIT_SUCCESS : EXIT_FAILURE;
	}

	bool parse() {
		for (auto it = args.rbegin(); it != args.rend(); it++) {
			string key = it->first;
			string val = it->second;

			if (key == "algorithme") {
				if (val == "AStart")
					algo = AStart;
			}
			else if (key == "maxIteration") {
				maxIter = atoi(val.c_str());
			}
			else if (key == "weight") {
				weight = atoi(val.c_str());
			}
			else if (key == "sortingfFunction") {
				if (val == "uniformCost")
					sortSearch = uniformCostSearch;
				else if (val == "greedy")
					sortSearch = greedySearch;
			}
			else if (key == "heuristique") {
				if (val == "badPlacedTiles")
					h = badPlacedTiles;
				else if (val == "manhattanDistance")
					h = manhattanDistance;
				else if (val == "manhattanDistance+linearConflict")
					h = manDist_linCon;
			}
			else if (key == "start") {
				if (parseGame(val, start) == EXIT_FAILURE) {
					cout << "There is a problem with the input file" << endl;
					return EXIT_FAILURE;
				}
				size = start.size;
			}
			else if (key == "goal") {
				if (size == 0)
					return EXIT_FAILURE;
				goal = goalGeneration(size, val);
			}
		}
		return args.size() == 7 ? EXIT_SUCCESS : EXIT_FAILURE;
	}

	void print() {
		cout << "algorithme" << " = " << args["algorithme"] << endl;
		cout << "weight" << " = " << args["weight"] << endl;
		cout << "sortingfFunction" << " = " << args["sortingfFunction"] << endl;
		cout << "heuristique" << " = " << args["heuristique"] << endl;
	}

	void printGames() {
		cout << "Start:" << string(size + 6, ' ') << "Goal:" << endl;
		for (size_t row = 0; row < size; row++) {
			for (size_t col = 0; col < size; col++) {
				cout << setw(3) << start.grid[row][col];
			}
			cout << "    ";
			for (size_t col = 0; col < size; col++) {
				cout << setw(3) << start.grid[row][col];
			}
			cout << endl;
		}
	}
};
