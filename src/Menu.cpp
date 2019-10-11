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

Menu::Menu(void) : tree{
		{
			"Welcome to gomoku !",
			{1, 2, -1, -1, -1},
			2,
			0,
			nullptr
		},
		{
			"Play",
			{-1, -1, -1, -1, -1},
			0,
			0,
			nullptr
		},
		{
			"Parameters",
			{-1, -1, -1, -1, -1},
			0,
			0,
			nullptr
		}
	}
{}

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
		if (myStream >> choice_index)
		{
			if (choice_index > 0 && choice_index <= max_index)
				break ;
		}
		cout << "Invalid index, please try again" << endl;
	}
	return choice_index;
}

// Display

void	Menu::displayMenu(int index)
{
	int	choice_index;
	int	i = 0;

	if (index >= 3 || index < 0)
	{
		cout << "index error in displayMenu" << endl;
		return ;
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
	uint8_t	input = 0;
	uint8_t	index = 0;
	bool	quit = false;

	while (!quit)
	{
		this->clear();
		this->displayMenu(index);
		input = this->getInput(this->tree[index].nb_choices + 1);
		if (input == this->tree[index].nb_choices)
		{
			if (index == 0)
				quit = true;
			else
				index = this->tree[index].parent;
		}
		index = this->tree[index].choice[input - 1];
	}

}

void	Menu::clear()
{
	cout << "\033[2J";
}

// Debug

void	Menu::debugTree()
{
	for (int i = 0; i < 3; i++)
	{
    	cout << "Name: " << this->tree[i].name << endl;
		cout << "Choices: ";
		for (const auto& elem : this->tree[i].choice)
		{
			cout << elem << " ";
		}
		cout << endl;
		cout << "Set pointer: " << this->tree[i].set << endl;
		cout << endl;
	}
}
