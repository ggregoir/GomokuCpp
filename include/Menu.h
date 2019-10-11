#pragma once

#include <string>

class Parameters;

class Menu
{

	struct SubMenu
	{
		std::string		name;
		int				choice[5];
		int				nb_choices;
		int				parent;
		void			(*set)(Parameters *params);
	};


	private:
		const SubMenu	tree[3];


	public:
		Menu(void);
		~Menu(void);

		int		getInput(int max_index);

		// Display
		void	loop(Parameters *params);
		void	displayMenu(int index);
		void	clear();

		// Debug
		void	debugTree();

};