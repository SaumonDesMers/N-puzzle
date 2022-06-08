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
			return false;
	}
	return true;
}

Game stringToInt(vector<string> tab) {
	Game game;
	game.size = atoi(tab[0].c_str());
	for (size_t i = 1; i < tab.size(); i++) {
		vector<string> rowStr = split(tab[i]);
		vector<int> row;
		for (size_t j = 0; j < rowStr.size(); j++)
			row.push_back(atoi(rowStr[j].c_str()));
		game.grid.push_back(row);
	}
	game.updateEmptyPos();
	return game;
}

bool checkValue(Game game) {
	Game::Grid grid = game.grid;
	if (grid.size() != game.size)
		return false;
	for (size_t row = 0; row < game.size; row++) {
		if (grid[row].size() != game.size)
			return false;
	}
	vector<bool> value(grid.size() * grid.size());
	for (size_t row = 0; row < grid.size(); row++) {
		for (size_t col = 0; col < grid.size(); col++) {
			if (grid[row][col] >= 0 && grid[row][col] < static_cast<int>(value.size()))
				value[grid[row][col]] = true;
		}
	}
	// for (size_t i = 0; i < value.size(); i++)
	// 	cout << value[i] << " ";
	// cout << endl;
	return all_of(value.begin(), value.end(), [](bool b) { return b; });
}

bool parseGame(string fileName, Game &game) {
	// cout << "a" << endl;
	vector<string> tab = readFile(fileName);
	// cout << "b" << endl;
	vector<string> tabWithoutComment = filterComment(tab);
	// cout << "c" << endl;
	if (!checkStr(tabWithoutComment))
		return false;
	// cout << "d" << endl;
	game = stringToInt(tabWithoutComment);
	// cout << "e" << endl;
	// game.print();
	if (!checkValue(game))
		return false;
	// cout << "f" << endl;
	return true;
}