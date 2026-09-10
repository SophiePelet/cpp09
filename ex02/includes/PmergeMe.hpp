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
#include <algorithm>

#define	ERR_TYPE		"Error: unauthorized character in the input"
#define	ERR_OVERFLOW	"Error: number is out of bounds"
#define	ERR_DUP			"Error: the sequence contains duplicates"
#define	ERR_ARG			"Error: no arguments"

class	PmergeMe {
	public:

	PmergeMe();
	PmergeMe(const PmergeMe &other);
	PmergeMe &operator=(const PmergeMe &other);
	~PmergeMe();

	//print the vector/deque
	void	printVector(const std::string &message) const;
	void	printDeque(const std::string &message) const;

	//parsing
	bool	check_input(int ac, char **av);
	
	//sorting functions
	void	sortVector();
	void	sortDeque();
	
	private:
	
	std::vector<int>	_vec_number;
	std::deque<int>		_deque_number;
	std::vector<int>	recursiveVector(std::vector<int> numbers);
	std::deque<int>	recursiveDeque(std::deque<int> numbers);
};

#endif