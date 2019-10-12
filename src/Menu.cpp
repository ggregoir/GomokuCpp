#include "Menu.h"
#include "Parameters.h"
#include <iostream>
#include <sstream>

using namespace std;

namespace color
{
	string	red = "\033[0;31m";
	string	green = "\033[0;33m";
	string reset = "\033[0m";
}

Menu::Menu(void) : tree
{
	{ "Welcome to gomoku !", {1, 6, -1, -1}, 2, 0 },
		{ "Play", {2, 3, 4, 5}, 4, 0 },
			{ "Player Vs Player", {-1, -1, -1, -1}, 0, 1, Parameters::setMode, Parameters::getMode },
			{ "Player Vs Engine", {-1, -1, -1, -1}, 0, 1, Parameters::setMode, Parameters::getMode },
			{ "Engine Vs Engine", {-1, -1, -1, -1}, 0, 1, Parameters::setMode, Parameters::getMode },
			{ "Start the game", {-1, -1, -1, -1}, 0, 1 },
		{ "Parameters", {7, 10, 13, -1}, 3, 0 },
			{ "Theme", {8, 9, -1, -1}, 2, 6 },
				{ "Classic", {-1, -1, -1, -1}, 0, 7, Parameters::setTheme, Parameters::getTheme },
				{ "Dark", {-1, -1, -1, -1}, 0, 7, Parameters::setTheme, Parameters::getTheme },
			{ "Rule", {11, 12, -1, -1}, 2, 6 },
				{ "Standard", {-1, -1, -1, -1}, 0, 10, Parameters::setRule, Parameters::getRule },
				{ "Restricted", {-1, -1, -1, -1}, 0, 10, Parameters::setRule, Parameters::getRule },
			{ "First to play", {14, 15, -1, -1}, 2, 6 },
				{ "Player 1 plays first", {-1, -1, -1, -1}, 0, 13, Parameters::setPriority, Parameters::getPriority },
				{ "Player 2 plays first", {-1, -1, -1, -1}, 0, 13, Parameters::setPriority, Parameters::getPriority },

} {}

Menu::~Menu(void) {}

int		Menu::getInput(int max_index)
{
	string	input = "";
	int		choice_index = 0;

	while (true)
	{
		cout << "Please enter a valid index: ";
		getline(cin, input);

		// This code converts from string to number safely.
		stringstream myStream(input);
		if (input == "quit")
			exit(EXIT_SUCCESS);
		if (myStream >> choice_index)
		{
			if (choice_index > 0 && choice_index <= max_index)
				break ;
		}
		cout << "Invalid index, please try again" << endl;
	}
	return choice_index;
}

void	Menu::displayMenu(int index, Parameters &params)
{
	int	choice_index;
	int	i = 0;

	if (index >= 15 || index < 0)
	{
		cout << "index error in displayMenu" << endl;
		exit(EXIT_FAILURE);
	}
	cout << tree[index].name << endl;
	while (i < tree[index].nb_choices)
	{
		choice_index = tree[index].choice[i];
		if (tree[choice_index].get && tree[choice_index].get(params) == i)
			cout << i + 1 << ") " << color::green << tree[choice_index].name << color::reset << endl;
		else
			cout << i + 1 << ") " << tree[choice_index].name << endl;
		i++;
	}
	if (index == 0)
		cout << i + 1 << ") " << "Exit" << endl;
	else
		cout << i + 1 << ") " << "Back" << endl;
}

void	Menu::loop(Parameters &params)
{
	int		input = 0;
	int		index = 0;
	int		choice_index = 0;
	bool	quit = false;

	while (!quit)
	{
		clear();
		displayMenu(index, params);
		input = getInput(tree[index].nb_choices + 1);
		if (input == tree[index].nb_choices + 1)
		{
			if (index == 0)
				exit(EXIT_SUCCESS);
			else
				index = tree[index].parent;
		}
		else
		{
			choice_index = tree[index].choice[input - 1];
			if (choice_index == 5) // index for starting the game in play menu
				quit = true;
			else if (!tree[choice_index].get)
				index = choice_index;
			else
				tree[choice_index].set(params, input - 1);
		}
		
	}

}

void	Menu::clear()
{
	cout << "\e[1;1H\e[2J";
}