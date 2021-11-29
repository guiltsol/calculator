#pragma once
#include <iostream>
#include <string>
#include <cmath>
#include <sstream>
#include "TStack.h"

using namespace std;

class TCalculator {
	
	string expr;
	string postfix;
	TStack<char> st_char;
	TStack<double> st_d;

	
	int prior(char op) {
		switch (op) {
			
		case '(': return 0;
		case '+': return 1;
		case '-': return 1;
		case '*': return 2;
		case '/': return 2;
		case '^': return 3;
		}
		return 0;
	}

public:

	TCalculator() {
	}

	~TCalculator() {
	}

	TCalculator(const TCalculator& other) {
		expr = other.expr;
		postfix = other.postfix;
	}

	TCalculator& operator=(const TCalculator& other) {
		expr = other.expr;
		postfix = other.postfix;
		return *this;
	}

	void SetExpr(string _expr) {
		expr = _expr;
	}

	string GetExpr() {
		return expr;
	}

	string GetPostfix() {
		return postfix;
	}

	
	bool CheckExpr() {
		for (int i = 0; i < expr.length(); i++)
		{
			if (expr[i] == '(')
				st_char.Push(expr[i]);
			else if (expr[i] == ')')
			{
				if (st_char.IsEmpty()) return false;
				else st_char.Pop();
			}
		}
		return st_char.IsEmpty();
	}

	void PreparePostfix() {
		
		string infix = "(" + expr + ")";
		
		postfix = "";
		st_char.Clear();

		for (int i = 0; i < infix.size(); i++)
		{
			
			if (isdigit(infix[i]))
			{
				size_t idx;
				double tmp = stod(&infix[i], &idx);

				ostringstream ss;
				ss << tmp;

				postfix += ss.str();
				postfix += " ";

				
				i += idx - 1;
			}
			
			else if (infix[i] == '(')
			{
				st_char.Push(infix[i]);
			}
			
			else if (infix[i] == ')')
			{
				while (st_char.Top() != '(')
				{
					postfix += st_char.Pop();
					postfix += " ";
				}
				
				st_char.Pop();
			}
			else if ((infix[i] == '+') || (infix[i] == '-') || (infix[i] == '*') || (infix[i] == '/') || (infix[i] == '^'))
			{
				while (prior(infix[i]) <= prior(st_char.Top()))
				{
					postfix += st_char.Pop();
					postfix += " ";
				}
				st_char.Push(infix[i]);
			}
		}
		
		if (!postfix.empty())
			postfix.pop_back();
	}

	
	double CalcPostfix() {
		if (postfix.empty()) throw "Empty";
		
		for (int i = 0; i < postfix.length(); i++)
		{
			if (postfix[i] >= '0' && postfix[i] <= '9') {

				size_t idx;
				double tmp = stod(&postfix[i], &idx);
				st_d.Push(tmp);
				
				i += idx - 1;
			}
			
			else if (postfix[i] == '+' || postfix[i] == '-' ||
				postfix[i] == '*' || postfix[i] == '/' || postfix[i] == '^') {
				double second;
				double first;

				
				if (st_d.IsNotEmpty()) {
					second = st_d.Pop();
				}
				else throw "Exception: Too much operations: column "
					+ to_string(i + 1) + " of the postfix string";

				
				if (st_d.IsNotEmpty()) {
					first = st_d.Pop();
				}
				else throw "Exception: Too much operations: column "
					+ to_string(i + 1) + " of the postfix string";


				switch (postfix[i]) {
				case '+':
					st_d.Push(first + second);
					break;
				case '-':
					st_d.Push(first - second);
					break;
				case '*':
					st_d.Push(first * second);
					break;
				case '/':
					st_d.Push(first / second);
					break;
				case '^':
					st_d.Push(pow(first, second));
					break;
				}
			}
		}

		if (st_d.IsNotEmpty()) {
			double result = st_d.Pop();
			
			if (st_d.IsNotEmpty()) {
				throw "Exception: Too many operands in the string";
			}
			return result;
		}
		
		else {
			throw "Exception: No operands in the string";
		}
	}

	
	double Calc()
	{
		string infix = "(" + expr + ")";

		st_char.Clear();
		st_d.Clear();

		for (int i = 0; i < infix.length(); i++)
		{
			
			if (infix[i] == '(')
			{
				st_char.Push(infix[i]);
			}
			
			else if (isdigit(infix[i]))
			{
				size_t idx;
				double tmp = stod(&infix[i], &idx);
				st_d.Push(tmp);
				
				i += idx - 1;
			}
			
			else if ((infix[i] == '+') || (infix[i] == '-') || (infix[i] == '*') || (infix[i] == '/') || (infix[i] == '^'))
			{
				
				while (prior(infix[i]) <= prior(st_char.Top()))
				{
					if (st_d.IsEmpty())
						throw "Exception: Too much operations";
					double second = st_d.Pop();

					if (st_d.IsEmpty())
						throw "Exception: Too much operations";
					double first = st_d.Pop();
					
					char op = st_char.Pop();

					switch (op)
					{
					case '+':
						st_d.Push(first + second);
						break;
					case '-':
						st_d.Push(first - second);
						break;
					case '*':
						st_d.Push(first * second);
						break;
					case '/':
						st_d.Push(first / second);
						break;
					case '^':
						st_d.Push(pow(first, second));
						break;
					}
				}
				st_char.Push(infix[i]);
			}
			
			else if (infix[i] == ')')
			{
				while (st_char.Top() != '(')
				{
					if (st_d.IsEmpty()) throw "Exception: Too much operations";
					double second = st_d.Pop();

					if (st_d.IsEmpty()) throw "Exception: Too much operations";
					double first = st_d.Pop();

					char op = st_char.Pop();

					switch (op)
					{
					case '+':
						st_d.Push(first + second);
						break;
					case '-':
						st_d.Push(first - second);
						break;
					case '*':
						st_d.Push(first * second);
						break;
					case '/':
						st_d.Push(first / second);
						break;
					case '^':
						st_d.Push(pow(first, second));
						break;
					}
				}
				
				st_char.Pop();
			}
		}

		if(st_d.IsEmpty()) throw "Exception: No operands in the string";
		double result = st_d.Pop();

		
		if (st_d.IsNotEmpty()) throw "Exception: Too many operands in the string";

		return result;
	}
};