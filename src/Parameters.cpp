#include "Parameters.h"

#include <iostream>

Parameters::Parameters()
{
	this->mode = PlayerVsPlayer;
	this->rule = Standard;
	this->theme = Classic;
}

Parameters::~Parameters() {}


// Setters

void	Parameters::setTheme(Parameters &params, uint8_t theme)
{
	params.theme = static_cast<Theme>(theme);
}

void	Parameters::setRule(Parameters &params, uint8_t rule)
{
	params.rule = static_cast<Rule>(rule);
}

void	Parameters::setMode(Parameters &params, uint8_t mode)
{
	params.mode = static_cast<Mode>(mode);
}

void	Parameters::setPriority(Parameters &params, uint8_t priority)
{
	params.priority = (bool)priority;
}


// Getters

uint8_t	Parameters::getTheme(Parameters &params)
{
	return params.theme;
}

uint8_t	Parameters::getRule(Parameters &params)
{
	return params.rule;
}

uint8_t	Parameters::getMode(Parameters &params)
{
	return params.mode;
}

uint8_t	Parameters::getPriority(Parameters &params)
{
	return params.priority;
}


void	Parameters::debugState()
{
	std::cout << "Theme: " << this->theme << std::endl;
	std::cout << "Rule: " << this->rule << std::endl;
	std::cout << "Mode: " << this->mode << std::endl;
	std::cout << "Priority: " << this->priority << std::endl;
}