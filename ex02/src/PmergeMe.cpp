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
		std::vector<int>	copy_dup = _vec_number;

		sort(copy_dup.begin(), copy_dup.end());
		for (size_t	i = 0; i < copy_dup.size(); ++i) {
			const bool has_duplicate = std::adjacent_find(copy_dup.begin(), copy_dup.end()) != copy_dup.end();
			if (has_duplicate) {
				std::cerr << ERR_DUP << std::endl;
				return (false);
			}
		}
	}
	return (true);
}

/*
	Vector sorting
*/

void	PmergeMe::printVector(const std::string &message) const {
	std::cout << message << " ";
	for (size_t i = 0; i < _vec_number.size(); ++i)
		std::cout << _vec_number[i] << " ";
	std::cout << std::endl;
}

std::vector<int>	jacobsthalGenerator(size_t pend_size) {
	std::vector<int>	jacob_sequence;

	jacob_sequence.push_back(0);
	jacob_sequence.push_back(1);

	int i = 2;
	while (true) {
		size_t next_jacob = jacob_sequence[i - 1] + 2 * jacob_sequence[i - 2];
		jacob_sequence.push_back(next_jacob);

		if (next_jacob >= pend_size) {
			break; 
		}
		i++;
	}
	
	return (jacob_sequence);
}

std::vector<int>	PmergeMe::recursiveVector(std::vector<int> numbers) {
	if (numbers.size() <= 1)
		return (numbers);

	std::vector<std::pair<int, int> >	pairs;
	bool	has_remainder = false;
	int		remainder = -1;
	size_t	vec_size = numbers.size();

	//store a remainder if odd size of vector
	if (numbers.size() % 2 != 0) {
		remainder = numbers[vec_size - 1];
		has_remainder = true;
		numbers.pop_back();
		vec_size -= 1;
	}

	//create the pair (biggest number first)
	for (size_t i = 0; i < vec_size; i += 2) {
		int	a = numbers[i];
		int	b = numbers[i + 1];

		if (a > b)
			pairs.push_back(std::make_pair(a, b));
		else
			pairs.push_back(std::make_pair(b, a));
	}

	//create the main chain containing the "winner" (= biggest number)
	std::vector<int>	main_chain;

	for (size_t i = 0; i < pairs.size(); ++i)
		main_chain.push_back(pairs[i].first);
		
	//recursive logic for the use of the pairs
	main_chain = recursiveVector(main_chain);
	
	std::vector<int>	pend_chain;
	
	for (size_t i = 0; i < main_chain.size(); ++i) {
		//find sorted winner in original pairs to get its specific loser
		for (size_t j = 0; j < pairs.size(); ++j) {
			if (main_chain[i] == pairs[j].first) {
				pend_chain.push_back(pairs[j].second);
				break;
			}
		}
	}
	
	if (has_remainder)
		pend_chain.push_back(remainder);
	//INSERTION PHASE
	//insert the loser of the very first winner at the beggining of the main chain
	main_chain.insert(main_chain.begin(), pend_chain[0]);

	//generate Jacobsthal sequence and use it to find where to insert the numbers of the pending chain
	std::vector<int>	jacobsthal_sequence = jacobsthalGenerator(pend_chain.size());

	size_t	previous_jacob = 1;
	for (size_t i = 3; i < jacobsthal_sequence.size(); ++i) {
		size_t	current_jacob = jacobsthal_sequence[i];

		if (current_jacob > pend_chain.size())
			current_jacob = pend_chain.size();

		for (size_t j = current_jacob - 1; j >= previous_jacob; --j) {
			int	target = pend_chain[j];

			std::vector<int>::iterator	it = std::upper_bound(main_chain.begin(), main_chain.end(), target);
			main_chain.insert(it, target);
		}
		previous_jacob = current_jacob;
	}
	
	return (main_chain);
}

void	PmergeMe::sortVector() {
	_vec_number = recursiveVector(_vec_number);
}