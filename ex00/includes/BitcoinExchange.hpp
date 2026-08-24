#ifndef BITCOINEXCHANGE_HPP
#define BITCOINEXCHANGE_HPP

#include <exception>
#include <iostream>
#include <fstream>
#include <map>
#include <string>
#include <algorithm>

#define	ERR_DATE	"Error: bad input => "

class BitcoinExchange
{
public:
	BitcoinExchange();
	BitcoinExchange(const BitcoinExchange &other);
	BitcoinExchange &operator=(const BitcoinExchange &other);
	~BitcoinExchange();

	void	check(const std::string &file);

	class CantOpenFileException : std::exception
	{
		const char *what() const throw();
	};

private:
	std::map<std::string, float> _data;
};

#endif