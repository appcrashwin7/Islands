#pragma once

#include <string>
#include <fstream>
#include <iostream>

namespace ErrorHandler
{
	inline void log(const std::string &text)
	{
		std::cout << text << std::endl;
	}
	inline void logB(const std::string &text)
	{
		std::cout << text;
	}
	inline void logToFile(const std::string &text)
	{
		std::fstream file("log.txt",std::ios::app | std::ios::out);
		file << text.data() << std::endl;
		file.close();
	}

	inline void clearLogFile()
	{
		std::fstream file("log.txt", std::ios::trunc | std::ios::out);
		file.close();
	}
};