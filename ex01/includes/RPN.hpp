#ifndef RPN_HPP
#define RPN_HPP

#include <iostream>
#include <stack>
#include <string>
#include <stdexcept>
#include <algorithm>

#define	ERR_SMALL	"Error: not enough numbers in the stack to make an operation"
#define	ERR_PARAM	"Error: unauthorized character in the input"
#define	MISSING_ARG	"Usage: ./RPN <rpn expression>"
#define	ERR_END		"Error: too many numbers left"

class	RPN {
	public:

	RPN();
	RPN(const RPN &other);
	RPN &operator=(const RPN &other);
	~RPN();

	void	calculate(const std::string &param);

	private:

	std::stack<int>	_numbers;
};

#endif