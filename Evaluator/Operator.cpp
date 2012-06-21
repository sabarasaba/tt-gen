#pragma once
#include "Operator.h"
#include "OperatorList.h"
#include "Variable.h"
#include "Error.h"
#include <string>
#include <list>

using namespace std;
using std::string;

Operator::Operator(string Expression)
{
	this->SetExpression(Expression);
}

bool Operator::isOperator(list<char> OperatorsList, char charsito)
{
	bool results = 0;

	for (list<char>::iterator i = OperatorsList.begin(); i != OperatorsList.end(); i++)
	{
		if (*i == charsito)
			results++;
	}

	return (results > 0);
}

Error Operator::FindError()
{
	Error *error = new Error();
	bool flag = true;
	int count = 0;

	while ((count < this->GetExpression().length() - 1) && (flag))
	{
		if ((this->isOperator(OperatorList::instance()->getOperators(), this->GetExpression()[count])) && (this->isOperator(OperatorList::instance()->getOperators(), this->GetExpression()[count + 1])))
		{
			flag = !flag;
			error = new Error(count, "No puede haber dos operadores \"juntos\".");
		}

		if ((this->isOperator(OperatorList::instance()->getSpecialOperators(), this->GetExpression()[count])) && (this->isOperator(OperatorList::instance()->getOperators(), this->GetExpression()[count + 1])))
		{
			flag = !flag;

			// Prepare Error Message
			
			char first = this->GetExpression()[count];
			char last = this->GetExpression()[count + 1];

			string message = "No puede haber un \'";
			message += first;
			message.append("\' antes de un \'");
			message += last;
			message.append("\'.");
			

			error = new Error(count, message);
		}
		
		if ((!this->isOperator(OperatorList::instance()->getOperators(), this->GetExpression()[count])) && (!this->isOperator(OperatorList::instance()->getSpecialOperators(), this->GetExpression()[count])) && (this->GetExpression()[count] != ')') && (this->GetExpression()[count] != '(') && (!Variable::isUpperCaseVariable(this->GetExpression()[count])))
		{
			flag = !flag;
			error = new Error(count, "Operador desconocido.");
		}


		count++;
	}
	

	return *error;
}

bool Operator::Valid()
{
	bool flag = true;
	int count = 0;

	while ((count < this->GetExpression().length() - 1) && (flag))
	{
		if (((this->isOperator(OperatorList::instance()->getOperators(), this->GetExpression()[count])) && (this->isOperator(OperatorList::instance()->getOperators(), this->GetExpression()[count + 1])))
		|| ((this->isOperator(OperatorList::instance()->getSpecialOperators(), this->GetExpression()[count])) && (this->isOperator(OperatorList::instance()->getOperators(), this->GetExpression()[count + 1]))))
			flag = !flag;
		else
			// If is not a valid operator and not a delimiter parentesis
			if ((!this->isOperator(OperatorList::instance()->getOperators(), this->GetExpression()[count])) && (!this->isOperator(OperatorList::instance()->getSpecialOperators(), this->GetExpression()[count])) && (this->GetExpression()[count] != ')') && (this->GetExpression()[count] != '(') && (!Variable::isUpperCaseVariable(this->GetExpression()[count])))
				flag = !flag;

		count++;
	}

	return flag;
}