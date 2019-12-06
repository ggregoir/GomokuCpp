#pragma once

#include <string>


class Parameters;

class Menu
{

	struct SubMenu
	{
		std::string		name;
		int				choice[4];
		int				nb_choices;
		int				parent;
		void			(*set)(Parameters &params, uint8_t to_set);
		uint8_t			(*get)(Parameters &params);
	};

	public:
		Menu(void);
		~Menu(void);

		void			loop(Parameters &params);
		void			clear();

	private:
		const SubMenu	tree[17];
		
		int				getInput(int max_index);
		void			displayMenu(int index, Parameters &params);
		void			goodGame();

};