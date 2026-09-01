#include "RPN.hpp"

/*
	Constructor/destructor, copy constructor, copy assignment operator
*/

RPN::RPN() {}
RPN::RPN(const RPN &other) : _numbers(other._numbers) {}
RPN &RPN::operator=(const RPN &other) {
	if (this != &other)
		this->_numbers = other._numbers;
	return (*this);
}
RPN::~RPN() {}

/*
	Member function
*/

void	RPN::calculate(const std::string &param) {
	std::string	valid_oper = "+-/*";

	for (size_t i = 0; i < param.length(); ++i) {

		if (param[i] == ' ')
			continue;
		
		else if (isdigit(param[i])) {
			this->_numbers.push(param[i] - '0');
			continue;
		}
		
		if (std::find(valid_oper.begin(), valid_oper.end(), param[i]) != valid_oper.end()) {
			if (this->_numbers.size() < 2) {
				std::cerr << ERR_SMALL << std::endl;
				return ;
			}
			int	value1 = this->_numbers.top();
			this->_numbers.pop();
			int	value2 = this->_numbers.top();
			this->_numbers.pop();

			int	result;

			switch (param[i]) {
				case '+':
					result = value2 + value1;
					this->_numbers.push(result);
					break;
				case '-':
					result = value2 - value1;
					this->_numbers.push(result);
					break;
				case '*':
					result = value2 * value1;
					this->_numbers.push(result);
					break;
				case '/':
					if (value1 == 0)
						throw std::runtime_error("Error: attempted to divide by 0\n");
					result = value2 / value1;
					this->_numbers.push(result);
					break;
			}
		}
		else {
			std::cerr << ERR_PARAM << std::endl;
			return ;
		}
	}

	if (this->_numbers.size() == 1)
		std::cout << this->_numbers.top() << std::endl;
	else
		std::cerr << ERR_END << std::endl;

	return ;
}