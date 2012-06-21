#pragma once
#include "variable.h"
#include "Error.h"
#include <string>

using std::string;

Variable::Variable(string Expression)
{
	this->SetExpression(Expression);
}

bool Variable::isUpperCaseVariable(char charsito)
{
	if ((charsito >= 65) && (charsito <= 90))
		return true;
	return false;
}

Error Variable::FindError()
{
	Error *error = new Error();
	bool _error = false;
	int count = 0;

	while ((count < this->GetExpression().length() - 1) && (!_error))
	{
		if ((this->isUpperCaseVariable(this->GetExpression()[count])) && (this->isUpperCaseVariable(this->GetExpression()[count + 1])))
			_error = !_error;

		count++;
	}

	if (_error)
		error = new Error(count, "No puede haber dos variables \"juntas\".");

	return *error;
}

bool Variable::Valid()
{
	bool error = false;
	int count = 0;

	while ((count < this->GetExpression().length() - 1) && (!error))
	{
		if ((this->isUpperCaseVariable(this->GetExpression()[count])) && (this->isUpperCaseVariable(this->GetExpression()[count + 1])))
			error = !error;

		count++;
	}

	if (error)
		return !error;

	return true;
}