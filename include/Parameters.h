#pragma once

#include <cstdint>

enum Theme
{
	Classic,
	Space,
	Dark
};

enum Mode
{
	PlayerVsPlayer,
	PlayerVsEngine,
	EngineVsEngine
};

enum Rule
{
	Standard,
	Restricted,
	Connect4
};

enum Algorithm
{
	Minimax,
	MinimaxWithPruning,
	Negamax,
	NegamaxWithPruning,
	PVS
};

class Parameters
{

	public:
		Parameters();
		~Parameters();

		// Static setters & getters only used by Menu class
		static void		set_theme(Parameters &params, uint8_t theme);
		static void		set_rule(Parameters &params, uint8_t rule);
		static void		set_mode(Parameters &params, uint8_t mode);
		static void		set_priority(Parameters &params, uint8_t priority);
		static void		set_algorithm(Parameters &params, uint8_t algo);
		static uint8_t	get_theme(Parameters &params);
		static uint8_t	get_rule(Parameters &params);
		static uint8_t	get_mode(Parameters &params);
		static uint8_t	get_priority(Parameters &params);
		static uint8_t	get_algorithm(Parameters &params);

		Theme			theme;
		Mode			mode;
		Rule			rule;
		Algorithm		algo;
		bool			priority;

};

