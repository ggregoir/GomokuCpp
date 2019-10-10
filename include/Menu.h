#pragma once

#include <string>

class Parameters;

class Menu
{

	struct SubMenu
	{
		std::string		name;
		int				choice[5];
		void			(*set)(Parameters *params);
	};


	private:
		const SubMenu	tree[3];


	public:
		Menu(void);
		~Menu(void);

		// Display
		void	displayMenu(int index);

		// Debug
		void	debugTree();

};