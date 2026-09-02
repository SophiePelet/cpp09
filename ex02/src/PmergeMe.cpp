#include "PmergeMe.hpp"

/*
	Constructor/destructor, copy constructor, copy assignment operator
*/
PmergeMe::PmergeMe() {}
PmergeMe::PmergeMe(const PmergeMe &other) : _vec_number(other._vec_number), _deque_number(other._deque_number) {}
PmergeMe	&PmergeMe::operator=(const PmergeMe &other) {
	if (this != &other) {
		_vec_number = other._vec_number;
		_deque_number = other._deque_number;
	}
	return (*this);
}
PmergeMe::~PmergeMe() {}

/*
	Parsing
*/
bool	PmergeMe::check_input(int ac, char **av) {
	std::string	input;
	std::string	word;

	for (int i = 1; i < ac; ++i) {
		input = av[i];
	
		std::stringstream	ss(input);

		while (ss >> word) {
			if (word.size() == 1 && word[0] == '+') {
				std::cerr << ERR_TYPE << std::endl;
				return (false);
			}

			for (unsigned int j = 0; j < word.size(); ++j) {
				if (!isdigit(word[j]) && !(j == 0 && word[j] == '+')) {
					std::cerr << ERR_TYPE << std::endl;
					return (false);
				}
			}

			long int	num = std::strtol(word.c_str(), NULL, 10);
			if (num < INT_MIN || num > INT_MAX) {
				std::cerr << ERR_OVERFLOW << std::endl;
				return (false);
			}

			_vec_number.push_back(static_cast<int>(num));
			_deque_number.push_back(static_cast<int>(num));
		}
	}
	return (true);
}

void	PmergeMe::sortVector() {
	std::vector<std::pair<int, int>>	pairs;
	bool	has_remainder = false;
	int	remainder = -1;
	int	vec_size = _vec_number.size();

	//store a remainder if odd size of vector
	if (_vec_number.size() % 2 != 0) {
		remainder = _vec_number[vec_size];
		_vec_number.pop_back();
		vec_size -= 1;
	}

	//create the pair (biggest number first)
	for (int i = 0; i < vec_size; i += 2) {
		int	a = _vec_number[i];
		int	b = _vec_number[i + 1];

		if (a > b)
			pairs.push_back(std::make_pair(a, b));
		else
			pairs.push_back(std::make_pair(b, a));
	}
}