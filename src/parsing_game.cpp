#include "include.hpp"

vector<string> readFile(string fileName) {
	vector<string> tab;
	ifstream file(fileName);

	string str;
	while(getline(file, str))
		tab.push_back(str);
	return tab;
}

vector<string> filterComment(vector<string> tab) {
	vector<string> gameStr;
	for (size_t i = 0; i < tab.size(); i++) {
		size_t size = tab[i].find_first_of('#');
		string str = tab[i].substr(0, size != string::npos ? size : tab[i].size());
		if (!str.empty())
			gameStr.push_back(str);
	}
	return gameStr;
}

bool checkStr(vector<string> tab) {
	for (size_t i = 0; i < tab.size(); i++) {
		if (tab[i].find_first_not_of("0123456789 ") != string::npos)
			return EXIT_FAILURE;
	}
	return EXIT_SUCCESS;
}

vector<int> stringToInt(vector<string> lines) {
	vector<int> grid;
	size_t size = atoi(lines[0].c_str());
	// cout << "1" << endl;

	// check number of row
	if (size != lines.size() - 1)
		return grid;

	for (size_t i = 1; i < lines.size(); i++) {
		// cout << "2" << endl;
		vector<string> rowStr = split(lines[i], " ");

		// check number of value per row
		if (rowStr.size() != size) {
			grid.clear();
			break;
		}

		vector<int> row;
		// cout << "3" << endl;
		for (size_t j = 0; j < rowStr.size(); j++)
			row.push_back(atoi(rowStr[j].c_str()));
		// cout << "4" << endl;
		grid.insert(grid.end(), row.begin(), row.end());
	}
	// cout << "6" << endl;
	return grid;
}

bool checkValue(vector<int> grid) {
	for (size_t i = 0; i < grid.size(); i++) {
		if (grid[i] < 0 && grid[i] > static_cast<int>(grid.size() - 1))
			return EXIT_FAILURE;
	}
	return EXIT_SUCCESS;
}

bool parseGame(string fileName, Game &game) {
	// cout << "a" << endl;
	vector<string> tab = readFile(fileName);
	if (tab.empty() == EXIT_FAILURE)
		return EXIT_FAILURE;
	// cout << "b" << endl;
	vector<string> tabWithoutComment = filterComment(tab);
	// cout << "c" << endl;
	if (checkStr(tabWithoutComment) == EXIT_FAILURE)
		return EXIT_FAILURE;
	// cout << "d" << endl;
	vector<int> grid = stringToInt(tabWithoutComment);

	if (grid.size() == 0)
		return EXIT_FAILURE;
	// cout << "e" << endl;
	// game.print();
	if (checkValue(grid) == EXIT_FAILURE)
		return EXIT_FAILURE;
	// cout << "f" << endl;

	game = grid;
	// cout << "g" << endl;
	// game.print();
	return EXIT_SUCCESS;
}