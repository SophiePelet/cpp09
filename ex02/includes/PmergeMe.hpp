#ifndef PMERGEME_HPP
#define PMERGEME_HPP

#include <iostream>
#include <vector>
#include <deque>
#include <sstream>
#include <string>
#include <climits>
#include <cstdlib>
#include <utility>

#define	ERR_TYPE		"Error: unauthorized character in the input"
#define	ERR_OVERFLOW	"Error: number is out of bounds"

class	PmergeMe {
	public:

	PmergeMe();
	PmergeMe(const PmergeMe &other);
	PmergeMe &operator=(const PmergeMe &other);
	~PmergeMe();

	//parsing

	bool	check_input(int ac, char **av);
	void	sortVector();

	//sorting functions go here

	private:

	std::vector<int>	_vec_number;
	std::deque<int>		_deque_number;
};

#endif