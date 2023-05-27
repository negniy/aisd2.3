#pragma once 
#pragma once
#include "stdio.h"
#include <stdlib.h>
#include <string>
#include <ctype.h>
#include <math.h>
#include <locale.h>
#include <windows.h>
#include <conio.h>
#include <time.h>
#include <iostream>
#include "errors.h"

error::error(const char* message)
{
	this->message = _strdup(message);
}

error::error(const error& e)
{
	this->message = _strdup(e.message);
}

error::~error()
{
	free(message);
}

const char* error::get_message() { return message; }

void error::print() { std::cout << message; }