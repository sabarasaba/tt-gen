#pragma once
#include "Expression.h"
#include "Parentesis.h"
#include "Operator.h"
#include "Variable.h"
#include "ValidatorRule.h"
#include "Error.h"
#include <string>
#include <vector>
#include <list>
#include <iostream>

using std::string;
using namespace std;

void Expression::AddRules()
{
	this->rules.insert(this->rules.end(), new Parentesis(this->expression));
	this->rules.insert(this->rules.end(), new Variable(this->expression));
	this->rules.insert(this->rules.end(), new Operator(this->expression));
}

Expression::Expression()
{
	this->expression = "";
	this->ExpressionsContainer.clear();
	this->rules.clear();
	this->errors.clear();
	this->AddRules();
}

Expression::Expression(string Expression)
{
	this->expression = Expression;
	this->ExpressionsContainer.clear();
	this->rules.clear();
	this->errors.clear();
	this->AddRules();

	this->ResolveExpressions();
}


/*
	Validates the expression with all the given rules of validation.

	This method iterate trough all the rules on the rules container and validating them.
	If someone througs an error, the we must add the error in an error container and continues
	validating the other rules, if any.
*/
bool Expression::Valid()
{
	this->errors.clear();
	int IndexOfErrors = 0;
	
	for (vector<ValidatorRule*>::iterator i = this->rules.begin(); i != this->rules.end(); i++)
	{
		if (!const_cast<ValidatorRule*>(*i)->Valid())
		{
			this->errors.insert(errors.end(), const_cast<ValidatorRule*>(*i)->FindError());
			IndexOfErrors++;
		}
	}

	return (IndexOfErrors == 0);
}


int Expression::IndexOfExpressions()
{
	int index = 0;
	for (int count = 0; count < this->expression.length(); count ++)
		if (this->expression[count] == '(')
			index ++;

	return index;
}

void Expression::PrintExpressions()
{
	std::cout << " --- " << std::endl;

	for (int x = 0; x < this->ExpressionsContainer.size(); x++)
	{
		std::cout << this->ExpressionsContainer.at(x) << std::endl;
	}
}

void Expression::PrintErrors()
{
	std::cout << " --- " << std::endl;

	for (int x = 0; x < this->errors.size(); x++)
	{
		std::cout << "Error: En caracter " << this->errors.at(x).GetLineNumber() << ". " << this->errors.at(x).GetErrorMessage() << std::endl;
	}
}

string Expression::subString(string str, int From, int To)
{
	string result = "";

	for (int x = From; x <= To; x++)
	{
		result += str[x];
	}

	return result;
}

void Expression::ResolveExpressions()
{
	vector<int> OpensVector;
	int count = 0;

	while (this->ExpressionsContainer.size() < this->IndexOfExpressions())
	{
		if ((this->expression[count] == '(') || (this->expression[count] == ')'))
		{
			if (this->expression[count] == '(')
			{
				while (this->expression[count] != ')') 
				{ 
					if (this->expression[count] == '(')
						OpensVector.insert(OpensVector.end(), count);
					count++;
				}
			}

			if (this->expression[count] == ')')
			{
				int a = OpensVector.size() - 1;

				this->ExpressionsContainer.insert(this->ExpressionsContainer.end(), this->subString(this->expression,OpensVector.at(a), count++));
				OpensVector.erase(OpensVector.end() - 1);
			}
		}
		else
			count++;
	}

	OpensVector.~vector();
}

Expression::~Expression()
{
	this->ExpressionsContainer.~vector();
	this->rules.~vector();
	this->errors.~vector();
}
