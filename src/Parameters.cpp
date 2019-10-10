#include "Parameters.h"
#include <iostream>

Parameters::Parameters()
{
	this->mode = PlayerVsPlayer;
	this->rule = Standard;
	this->theme = Light;
}

Parameters::~Parameters() {}


// Setters

void	Parameters::setTheme(Theme theme)
{
	this->theme = theme;
}

void	Parameters::setRule(Rule rule)
{
	this->rule = rule;
}

void	Parameters::setMode(Mode mode)
{
	this->mode = mode;
}

void	Parameters::setPriority(bool priority)
{
	this->priority = priority;
}


// Getters

Theme	Parameters::getTheme()
{
	return this->theme;
}

Rule	Parameters::getRule()
{
	return this->rule;
}

Mode	Parameters::getMode()
{
	return this->mode;
}

bool	Parameters::getPriority()
{
	return this->priority;
}


void	Parameters::debugState()
{
	std::cout << "Theme: " << this->theme << std::endl;
	std::cout << "Rule: " << this->rule << std::endl;
	std::cout << "Mode: " << this->mode << std::endl;
	std::cout << "Priority: " << this->priority << std::endl;
}