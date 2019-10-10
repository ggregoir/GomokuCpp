#include "Menu.h"
#include <iostream>

using namespace std;

namespace color
{
	string	red = "\033[0;31m";
	string	green = "\033[0;33m";
	string reset = "\033[0m";
}

Menu::Menu(void) : tree{
		{
			"Gomoku",
			{1, 2, 0, -1, -1},
			nullptr
		},
		{
			"Play",
			{0, -1, -1, -1, -1},
			nullptr
		},
		{
			"Parameters",
			{-1, -1, -1, -1, -1},
			nullptr
		}
	}
{}

Menu::~Menu(void) {}

// Display

void	Menu::displayMenu(int index)
{
	int	choice_index;

	if (index >= 3 || index < 0)
	{
		cout << "index error in displayMenu" << endl;
		return ;
	}
	cout << this->tree[index].name << ":" << endl;

	for (int i = 0; i < 5; i++)
	{
		choice_index = this->tree[index].choice[i];
		if (choice_index == -1)
			break ;
		else if (index == 0 && choice_index == 0)
			cout << i + 1 << ") " << "Exit" << endl;
		else if (choice_index == 0)
			cout << i + 1 << ") " << "Back" << endl;
		else
			cout << i + 1 << ") " << this->tree[choice_index].name << endl;
	}
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
