#include "include.hpp"
#include "config.hpp"

void exec(Config config) {
	cout << "#########################################\n";
	config.printGames();

	cout << endl;
	config.print();
	cout << endl;
	config.algo(config);

	cout << "#########################################" << endl;
}

int main()
{
	Config config;
	if (config.load() == EXIT_FAILURE) {
		cout << "Error" << endl;
		return 1;
	}

	if (isSolvable(config.start, config.goal))
		exec(config);
	else
		cout << "Game not solvable" << endl;
	
	return 0;
}
