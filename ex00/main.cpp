#include "BitcoinExchange.hpp"

int	main(int ac, char **av) {
	if (ac != 2) {
		std::cout << "Error: could not open file" << std::endl;
		return (1);
	}

	try {
		BitcoinExchange	test;

		test.convert(av[1]);
	}
	catch (const std::exception &e) {
		std::cerr << e.what() << std::endl;
	}

}