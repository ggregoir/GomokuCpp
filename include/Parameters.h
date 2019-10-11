#pragma once

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
		void	setTheme(Theme theme);
		void	setRule(Rule rule);
		void	setMode(Mode mode);
		void	setPriority(bool priority);

		// Getters
		Theme	getTheme();
		Rule	getRule();
		Mode	getMode();
		bool	getPriority();

		// Debug
		void	debugState();
};

