#include "UserInterface.h"
#include "GameManager.h"
#include "Parameters.h"
#include "Menu.h"
#include "macros.h"
#include "Parameters.h"
#include "Menu.h"
#include "GameManager.h"

int main(int ac, char **av) 
{
	Parameters		params;
	Menu			menu;

	if (ac == 1 || (strcmp(av[1], "--nomenu") && strcmp(av[1], "-n")))
		menu.loop(params);
	GameManager(params).run_loop();
}
