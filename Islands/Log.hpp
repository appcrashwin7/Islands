#pragma once

#include <string>
#include <iostream>

class ErrorHandler
{
public:
	static void log(std::string text)
	{
		std::cout << text << std::endl;
	}
	static void logB(std::string text)
	{
		std::cout << text;
	}
};