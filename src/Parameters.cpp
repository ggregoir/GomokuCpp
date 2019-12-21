#include "Parameters.h"

#include <iostream>

Parameters::Parameters()
{
	this->mode = PlayerVsEngine;
	this->rule = Restricted;
	this->theme = Classic;
	this->priority = true;
}

Parameters::~Parameters() {}


// Setters

void	Parameters::set_theme(Parameters &params, uint8_t theme)
{
	params.theme = static_cast<Theme>(theme);
}

void	Parameters::set_rule(Parameters &params, uint8_t rule)
{
	params.rule = static_cast<Rule>(rule);
}

void	Parameters::set_mode(Parameters &params, uint8_t mode)
{
	params.mode = static_cast<Mode>(mode);
}

void	Parameters::set_priority(Parameters &params, uint8_t priority)
{
	params.priority = (bool)priority;
}


// Getters

uint8_t	Parameters::get_theme(Parameters &params)
{
	return params.theme;
}

uint8_t	Parameters::get_rule(Parameters &params)
{
	return params.rule;
}

uint8_t	Parameters::get_mode(Parameters &params)
{
	return params.mode;
}

uint8_t	Parameters::get_priority(Parameters &params)
{
	return params.priority;
}