#include "BitcoinExchange.hpp"

/*
	Constructor/destructor, copy constructor, copy assignment operator
*/

BitcoinExchange::BitcoinExchange() {
	std::string	buffer;

	std::ifstream	csv_data("data.csv");

	if (!csv_data.is_open())
		throw CantOpenFileException();

	int			index = 0;
	while(std::getline(csv_data, buffer)) {
		if (index == 0) {
			index++;
			continue ;
		}
		std::string::iterator	it = std::find(buffer.begin(), buffer.end(), ',');
		if (it == buffer.end()) {
			index++;
			continue ;
		}
		const std::string	before(buffer.begin(), it);
		const std::string	after(it + 1, buffer.end());
		this->_data[before] = std::strtod(after.c_str(), NULL);

		index++;
	}

	csv_data.close();
}
BitcoinExchange::BitcoinExchange(const BitcoinExchange &other) : _data(other._data) {}
BitcoinExchange	&BitcoinExchange::operator=(const BitcoinExchange &other) {
	if (this != &other)
		this->_data = other._data;
	return (*this);
}
BitcoinExchange::~BitcoinExchange() {}

/*
	Member functions
*/

bool	check_date(std::string date) {
	if (date.size() != 10 || date[4] != '-' || date[7] != '-')
		return (false);

	std::string::iterator	year_it = std::find(date.begin(), date.end(), '-');
	const std::string	year(date.begin(), year_it);
	for (size_t i = 0; i < year.size(); ++i) {
		if (!std::isdigit(year[i]))
			return (false);
	}
	int	int_year = atoi(year.c_str());

	std::string::iterator	it = std::find(year_it + 1, date.end(), '-');
	const std::string	month(year_it + 1, it);
	for (size_t i = 0; i < month.size(); ++i) {
		if (!std::isdigit(month[i]))
			return (false);
	}
	int	int_month = atoi(month.c_str());
	if (int_month < 1 || int_month > 12)
		return (false);

	
	const std::string	day(it + 1, date.end());
	for (size_t i = 0; i < day.size(); ++i) {
		if (!std::isdigit(day[i]))
			return (false);
	}
	int	int_day = atoi(day.c_str());
	if (int_day < 1 || int_day > 31)
		return (false);
	
	if ((int_year % 4 == 0 && int_year % 100 != 0) || (int_year % 400 == 0)) {
		if ((int_month < 9 && int_month % 2 != 0) || (int_month >= 8 && int_month % 2 == 0)) {
			if (int_day > 31)
				return (false);
		}
		else if ((int_month < 8 && int_month % 2 == 0 && int_month != 2) || (int_month >= 9 && int_month % 2 != 0)) {
			if (int_day > 30)
				return (false);
		}
		else if (int_month == 2) {
			if (int_day > 29)
				return (false);
		}
	}
	else {
		if ((int_month < 9 && int_month % 2 != 0) || (int_month >= 8 && int_month % 2 == 0)) {
			if (int_day > 31)
				return (false);
		}
		else if ((int_month < 8 && int_month % 2 == 0 && int_month != 2) || (int_month >= 9 && int_month % 2 != 0)) {
			if (int_day > 30)
				return (false);
		}
		else if (int_month == 2) {
			if (int_day > 28)
				return (false);
		}
	}

	return (true);
}

void	BitcoinExchange::convert(const std::string &file) {
	std::string	buffer;

	std::ifstream	input(file.c_str());

	if (!input.is_open())
		throw CantOpenFileException();

	int			index = 0;
	while(std::getline(input, buffer)) {
		if (index == 0) {
			index++;
			continue ;
		}

		size_t	pos = buffer.find(" | ");

		const std::string	before = buffer.substr(0, pos);
		if (!check_date(before)) {
			std::cout << ERR_DATE << before << std::endl;
			continue ;
		}

		const std::string	after = buffer.substr(pos + 3);
		
		if (pos == std::string::npos) {
			index++;
			continue;
		}
	
		char	*endptr;
		float	value = std::strtod(after.c_str(), &endptr);
		if (*endptr != '\0') {
			std::cout << ERR_VALUE;
			continue ;
		}
		if (value < 0) {
			std::cout << ERR_SMALL;
			continue ;
		}
		if (value > 1000) {
			std::cout << ERR_LARGE;
			continue ;
		}

		std::map<std::string, float>::iterator	it = this->_data.lower_bound(before);

		// an iterator to a map acts like a pointer to a std::pair
		// can access the first element element with `iterator->first`
		// `iterator->second` for the second element
		float	rate;
		if (it == this->_data.begin() && it->first != before) {
			std::cout << ERR_DATE << before << std::endl;
			continue ;
		}
		else if (it == this->_data.end() || it->first > before) {
			--it;
			rate = it->second;
		}
		else if (it != this->_data.end() && it->first == before)
			rate = it->second;

		float	final_value = rate * value;

		std::cout << it->first << " => " << value << " = " << final_value << std::endl;
		
		index++;
	}

	input.close();
}

const char*	BitcoinExchange::CantOpenFileException::what() const throw() {
	return ("Error: could not open file");
}