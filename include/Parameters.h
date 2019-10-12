#pragma once

#include <cstdint>

enum Theme
{
	Classic,
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
	Restricted
};

class Parameters
{
	private:
		Theme	theme;
		Mode	mode;
		Rule	rule;
		bool	priority; // true => player1 plays first

	public:
		Parameters();
		~Parameters();

		// Setters
		static void		setTheme(Parameters &params, uint8_t theme);
		static void		setRule(Parameters &params, uint8_t rule);
		static void		setMode(Parameters &params, uint8_t mode);
		static void		setPriority(Parameters &params, uint8_t priority);

		// Getters
		static uint8_t	getTheme(Parameters &params);
		static uint8_t	getRule(Parameters &params);
		static uint8_t	getMode(Parameters &params);
		static uint8_t	getPriority(Parameters &params);

		// Debug
		void		debugState();
};

