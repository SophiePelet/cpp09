#ifndef BITCOINEXCHANGE_HPP
#define BITCOINEXCHANGE_HPP

#include <exception>
#include <iostream>
#include <fstream>
#include <map>
#include <string>
#include <algorithm>
#include <cstdlib>

#define	ERR_DATE	"Error: bad input => "
#define	ERR_VALUE	"Error: invalid bitcoin value\n"
#define	ERR_LARGE	"Error: too large a number\n"
#define	ERR_SMALL	"Error: not a positive number\n"

class BitcoinExchange
{
	public:
		BitcoinExchange();
		BitcoinExchange(const BitcoinExchange &other);
		BitcoinExchange &operator=(const BitcoinExchange &other);
		~BitcoinExchange();

		void	convert(const std::string &file);

		class CantOpenFileException : std::exception
		{
			const char *what() const throw();
		};

	private:
		std::map<std::string, float> _data;
};

#endif