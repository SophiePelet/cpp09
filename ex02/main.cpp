#include "PmergeMe.hpp"

#define	RESET	"\033[0m"
#define	BLUE	"\033[34m"

int main(int ac, char **av) {
	PmergeMe sorter;

	if (!sorter.check_input(ac, av))
		return (1);
	sorter.printVector("Before: ");

	double v_time = sorter.vectorTime();
	double d_time = sorter.dequeTime();

	sorter.printVector("After:  ");

	std::cout << "Time to process a range of " << sorter.getSize() 
		<< " elements with std::vector : " << v_time << " us" << std::endl;
			  
	std::cout << "Time to process a range of " << sorter.getSize() 
		<< " elements with std::deque : " << d_time << " us" << std::endl;

	return (0);
}