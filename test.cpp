﻿#include <bits/stdc++.h>

using namespace std;

int precedence(char op)
{
	switch (op)
	{
	case '+':
	case '-':
		return 1;
	case '*':
	case '/':
		return 2;
	case '(':
		return 0;
	default:
		return -1;
	}
}

double calculate(string expression)
{
	// Create a stack to store the operands and operators.
	stack<double> operands;
	stack<char> operators;

	// Iterate over the expression.
	for (int i = 0; i < expression.length(); i++)
	{
		// If the current character is an operand, push it onto the stack of operands.
		if (isdigit(expression[i]))
		{
			operands.push(expression[i] - '0');
		}
		else if (expression[i] == '.')
		{
			// If the current character is a decimal point, push it onto the stack of operands.
			operands.push(expression[i]);
		}
		else if (expression[i] == '(')
		{
			// If the current character is a left parenthesis, push it onto the stack of operators.
			operators.push(expression[i]);
		}
		else if (expression[i] == ')')
		{
			// If the current character is a right parenthesis, pop the operators off the stack until we reach a left parenthesis.
			// Then, evaluate the expression using the popped operators and operands.
			while (operators.top() != '(')
			{
				double left = operands.top();
				operands.pop();
				double right = operands.top();
				operands.pop();
				char op = operators.top();
				operators.pop();
				operands.push(op == '+' ? left + right : op == '-' ? left - right
													 : op == '*'   ? left * right
													 : op == '/'   ? left / right
																   : 0);
			}
			// Pop the left parenthesis off the stack.
			operators.pop();
		}
		else
		{
			// If the current character is an operator, pop the operators off the stack until we find an operator with a lower precedence.
			// Then, evaluate the expression using the popped operators and operands.
			while (!operators.empty() && precedence(operators.top()) >= precedence(expression[i]))
			{
				double left = operands.top();
				operands.pop();
				double right = operands.top();
				operands.pop();
				char op = operators.top();
				operators.pop();
				operands.push(op == '+' ? left + right : op == '-' ? left - right
													 : op == '*'   ? left * right
													 : op == '/'   ? left / right
																   : 0);
			}
			// Push the current operator onto the stack.
			operators.push(expression[i]);
		}
	}

	// If there are any operators left on the stack, pop them off and evaluate them.
	while (!operators.empty())
	{
		double left = operands.top();
		operands.pop();
		double right = operands.top();
		operands.pop();
		char op = operators.top();
		operators.pop();
		operands.push(op == '+' ? left + right : op == '-' ? left - right
											 : op == '*'   ? left * right
											 : op == '/'   ? left / right
														   : 0);
	}

	// The result of the expression is the only operand left on the stack.
	return operands.top();
}
int main()
{
	string s;
	cin >> s;
	cout << calculate(s) << endl;
}
