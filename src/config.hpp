#include "include.hpp"

struct Config {
	map<string, string> args;
	algo_fct algo;
	int maxIter;
	int weight;
	sort_fct sortSearch;
	heuristique_fct h;
	Game *goal;
	Game *start;
	size_t size;

	Config() : algo(NULL), maxIter(0), weight(0), sortSearch(NULL), h(NULL), goal(NULL), start(NULL), size(0) {}

	~Config() {
		cerr << "Config destructor" << endl;
		delete goal;
		delete start;
	}

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

		if (args.count("algorithme") == 0
			|| args.count("maxIteration") == 0
			|| args.count("weight") == 0
			|| args.count("sortingFunction") == 0
			|| args.count("heuristique") == 0
			|| args.count("start") == 0
			|| args.count("goal") == 0)
			return EXIT_FAILURE;
		
		string val = args["algorithme"];
		if (val == "AStar")
			algo = AStar;
		else if (val == "IDAStar")
			algo = IDAStar;
		else if (val == "iterativeBrainless")
			algo = iterativeBrainless;
		else if (val == "recursiveBrainless")
			algo = recursiveBrainless;
		else
			return EXIT_FAILURE;
		
		val = args["maxIteration"];
		maxIter = atoi(val.c_str());

		val = args["weight"];
		weight = atoi(val.c_str());

		val = args["sortingFunction"];
		if (val == "uniformCost")
			sortSearch = uniformCostSearch;
		else if (val == "greedy")
			sortSearch = greedySearch;
		else
			return EXIT_FAILURE;

		val = args["heuristique"];
		if (val == "badPlacedTiles")
			h = badPlacedTiles;
		else if (val == "manhattanDistance")
			h = manhattanDistance;
		else if (val == "manhattanDistance+linearConflict")
			h = manDist_linCon;
		else
			return EXIT_FAILURE;
		
		val = args["start"];
		vector<string> arg = split(val, ":");
		val = args["goal"];
		if (arg.size() == 1) {
			if (parseGame(arg[0], start) == EXIT_FAILURE)
				return EXIT_FAILURE;
			size = start->size;
			goal = goalGeneration(size, val);
		}
		else if (arg.size() == 2) {
			size = atoi(arg[1].c_str());
			goal = goalGeneration(size, val);
			if (arg[0] == "random")
				start = randomGame(size);
			else if (arg[0] == "shuffle")
				start = shuffleGame(goal, size * 10000);
		}
		else
			return EXIT_FAILURE;

		return EXIT_SUCCESS;
	}

	void print() {
		cout << "algorithme" << " = " << args["algorithme"] << endl;
		cout << "weight" << " = " << args["weight"] << endl;
		cout << "sortingFunction" << " = " << args["sortingFunction"] << endl;
		cout << "heuristique" << " = " << args["heuristique"] << endl;
	}

	void printGames() {
		cout << "Start:" << string(size + 6, ' ') << "Goal:" << endl;
		for (size_t row = 0; row < size; row++) {
			for (size_t col = 0; col < size; col++) {
				cout << setw(3) << start->grid[row * size + col];
			}
			cout << "    ";
			for (size_t col = 0; col < size; col++) {
				cout << setw(3) << goal->grid[row * size + col];
			}
			cout << endl;
		}
	}
};
