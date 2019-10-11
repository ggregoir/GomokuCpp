#include "Menu.h"
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
	{ "Welcome to gomoku !", {1, 5, -1, -1}, 2, 0, nullptr },
		{ "Play", {2, 3, 4, -1}, 3, 0, nullptr },
			{ "Player Vs Player", {-1, -1, -1, -1}, 0, 0, nullptr },
			{ "Player Vs Engine", {-1, -1, -1, -1}, 0, 0, nullptr },
			{ "Engine Vs Engine", {-1, -1, -1, -1}, 0, 0, nullptr },
		{ "Parameters", {6, 9, 12, -1}, 3, 0, nullptr },
			{ "Theme", {7, 8, -1, -1}, 2, 5, nullptr },
				{ "Classic", {-1, -1, -1, -1}, 0, 6, nullptr },
				{ "Dark", {-1, -1, -1, -1}, 0, 6, nullptr },
			{ "Rule", {10, 11, -1, -1}, 2, 5, nullptr },
				{ "Standard", {-1, -1, -1, -1}, 0, 9, nullptr },
				{ "Restricted", {-1, -1, -1, -1}, 0, 9, nullptr },
			{ "First to play", {13, 14, -1, -1}, 2, 5, nullptr },
				{ "Player 1 plays first", {-1, -1, -1, -1}, 0, 12, nullptr },
				{ "Player 2 plays first", {-1, -1, -1, -1}, 0, 12, nullptr },

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

void	Menu::displayMenu(int index)
{
	int	choice_index;
	int	i = 0;

	if (index >= 15 || index < 0)
	{
		cout << "index error in displayMenu" << endl;
		exit(EXIT_FAILURE);
	}
	cout << this->tree[index].name << endl;
	while (i < this->tree[index].nb_choices)
	{
		choice_index = this->tree[index].choice[i];
		cout << i + 1 << ") " << this->tree[choice_index].name << endl;
		i++;
	}
	if (index == 0)
		cout << i + 1 << ") " << "Exit" << endl;
	else
		cout << i + 1 << ") " << "Back" << endl;
}

void	Menu::loop(Parameters *params)
{
	int		input = 0;
	int		index = 0;
	bool	quit = false;

	while (!quit)
	{
		this->clear();
		this->displayMenu(index);
		input = this->getInput(this->tree[index].nb_choices + 1);
		if (input == this->tree[index].nb_choices + 1)
		{
			if (index == 0)
				quit = true;
			else
				index = this->tree[index].parent;
		}
		else
		{
			cout << "input: " << input << endl;
			index = this->tree[index].choice[input - 1];
		}
	}

}

void	Menu::clear()
{
	cout << "\e[1;1H\e[2J";
}