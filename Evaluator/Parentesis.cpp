#pragma once
#include "Parentesis.h"
#include "Error.h"
#include <string>
#include <iostream>

using std::string;

Parentesis::Parentesis(string Expression)
{
	this->SetExpression(Expression);
}

int Parentesis::GetMaxIndex()
{
	int aux = 0, pos = 0, count = 0, max = 0;

	while (count < this->GetExpression().length())
	{
		if (this->GetExpression()[count] == '(')
			aux++;
		if (this->GetExpression()[count] == ')')
			aux--;

		if (aux > max)
		{
			aux = max;
			pos = count;
		}

		count++;
	}

	return pos;
}

Error Parentesis::FindError()
{
	int count = 0, iterator = 0;
	int Open = 0, Closed = 0;
	bool _error = false;
	Error *error = new Error();

	while ((iterator < (this->GetExpression().length())) && (!_error))
	{
		if (this->GetExpression()[iterator] == '(')
			Open++;
		if (this->GetExpression()[iterator] == ')')
			Closed--;

		if ((Open - Closed) < 0)
			_error = true;

		iterator++;
	}

	if (Open > Closed)
		error = new Error(this->GetMaxIndex(), "Parentesis erroneo.");

	// Number of line that has an error
	if (_error)
		error = new Error(iterator, "Parentesis erroneo.");

	return *error;
}

bool Parentesis::Valid()
{
	if ((!this->GetExpression().empty()) && (this->parentesisDivision(0, 0, 0)))
		return true;
	return false;
}

bool Parentesis::parentesisDivision(int position, int open, int closed)
{
	if (this->GetExpression()[position] == '(')
	{
		while (this->GetExpression()[position] != ')')
		{
			if (this->GetExpression()[position] == '(')
				open++;

			position ++;
		}
	}

	if (this->GetExpression()[position] == ')')
	{
		while ((position < this->GetExpression().length()) && (this->GetExpression()[position] != '('))
		{
			if (this->GetExpression()[position] == ')')
				closed++;

			position ++;
		}
	}

	if ((open == closed) && (position == this->GetExpression().length()))
		return true;
	if ( (open >= closed) && (position < this->GetExpression().length()))
		return Parentesis::parentesisDivision(position, open, closed);

	return false;
}
