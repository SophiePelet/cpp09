#include "RPN.hpp"

int	main(int ac, char **av) {
	if (ac < 2) {
		std::cerr << MISSING_ARG << std::endl;
		return (1);
	}

	try {
		RPN	calculator;

		calculator.calculate(av[1]);
	}
	catch (const std::exception &e) {
		std::cout << e.what() << std::endl;
	}
}