#pragma once
#include "TrueTable.h"
#include "prOr.h"
#include "prAnd.h"
#include "prXor.h"
#include "prConditional.h"
#include "prPierce.h"
#include "prSheffer.h"
#include "OperatorList.h"
#include "variable.h"
#include "Expression.h"
#include <vector>
#include <list>
#include <string>
#include <iostream>
#include <cmath>

using namespace std;
using std::string;

TrueTable::TrueTable(string Expression, vector<string> _ExpressionsContainer)
{
	this->ExpressionsContainer = _ExpressionsContainer;
	this->expression = Expression;

	vector<char> Vars = this->getVariables();

	this->matrix = this->createMatrix(this->getIndexOfRows() + 1, this->getIndexOfColumns());

	// Add Variables to first 'row'
	for (int x = 0; x < Vars.size(); x++)
	{
		string a = "";
		a += Vars.at(x);
		this->matrix[0][x] = a;
	}

	// Add Expressions to first 'row'
	for (int x = 0; x < this->ExpressionsContainer.size(); x++)
	{
		this->matrix[0][Vars.size() + x] = this->ExpressionsContainer.at(x);
	}

	// Add 'true values' to variables
	int factor = 2;
	int index = 0;
	int z = 0;
	char trueValue = '1';

	for (int x = 1; x < Vars.size() + 1; x++)
	{
		index = this->getIndexOfRows() / factor;
		trueValue = '1';
		z = 0;

		for (int y = 1; y < this->getIndexOfRows() + 1; y++)
		{
			z++;
			this->matrix[y][x-1] = trueValue;

			if (z == index)
			{
				z = 0;
				if (trueValue == '1')
					trueValue = '0';
				else
					trueValue = '1';
			}
		}

		factor *= 2;
	}

	Vars.~vector();
}

void TrueTable::DoLogic()
{
	int c = this->getVariables().size();
	bool A,B;
	char op;
	int colA, colB;

	for (int index = 0; index < this->ExpressionsContainer.size(); index++)
	{
		A = B = false;

		// op contains the char operator
		op = this->ExpressionsContainer.at(index)[this->getNexusOperator(this->ExpressionsContainer.at(index))];
		// colA contains the column of the table wich contains the expresion on the 'A' side
		colA = findExpressionA(this->ExpressionsContainer.at(index), this->getNexusOperator(this->ExpressionsContainer.at(index)));
		// colB contains the column of the table wich contains the expresion on the 'B' side
		colB = findExpressionB(this->ExpressionsContainer.at(index), this->getNexusOperator(this->ExpressionsContainer.at(index)));

		for (int x = 1; x < this->getIndexOfRows() + 1; x++)
		{
			if (this->matrix[x][colA] == "1")
					A = true;
				else
					A = false;
				if (this->matrix[x][colB] == "1")
					B = true;
				else
					B = false;

			switch(op)
			{
				case '|': // Or operator
					this->matrix[x][this->getIndexOfVariables() + index] = prOr::Evaluate(A,B);
				break;
				case '&': // And operator
					this->matrix[x][this->getIndexOfVariables() + index] = prAnd::Evaluate(A,B);
				break;
				case '%': // XOR operator
					this->matrix[x][this->getIndexOfVariables() + index] = prXor::Evaluate(A,B);
				break;
				case '>': // Implication operator
					this->matrix[x][this->getIndexOfVariables() + index] = prConditional::Evaluate(A,B);
				break;
				case '#': // Pierce operator
					this->matrix[x][this->getIndexOfVariables() + index] = prPierce::Evaluate(A,B);
				break;
				case '@': // Sheffer opereator
					this->matrix[x][this->getIndexOfVariables() + index] = prSheffer::Evaluate(A,B);
				break;
			}
		}
	}
}

string** TrueTable::createMatrix(int rows, int cols)
{
   string** vct = new string*[rows];

   for (int i = 0; i < rows; i++)
      vct[i] = new string[cols];

   return vct;
}

int TrueTable::findExpressionA(string proposition, int nexusOperator)
{
	string expression = Expression::subString(proposition, 1, nexusOperator - 1);

	for (int x = 0; x < this->getIndexOfColumns(); x++)
	{
		if (this->matrix[0][x] == expression)
			return x;
	}

	return -1;
}

int TrueTable::findExpressionB(string proposition, int nexusOperator)
{
	string expression = Expression::subString(proposition, nexusOperator + 1, proposition.size() - 2);

	for (int x = 0; x < this->getIndexOfColumns(); x++)
	{
		if (this->matrix[0][x] == expression)
			return x;
	}

	return -1;
}

int TrueTable::getNexusOperator(string proposition)
{
	int result = -1;

	// Replace all the expressions that contains only variables with blanks
	int count = 0;
	for (vector<string>::iterator i = this->ExpressionsContainer.begin(); i != this->ExpressionsContainer.end(); i++)
	{
		if (i->compare(proposition) != 0)
		{
			if (proposition.find(*i) != -1)
			{
				// Create a string with the same size of the founded expression
				string rep = "";
				for (int x = 0; x < i->size(); x++) { rep += "_"; }

				proposition.replace(proposition.find(*i), i->size(), rep);
			}
		}
	}

	for (list<char>::iterator i = OperatorList::instance()->getOperators().begin(); i != OperatorList::instance()->getOperators().end(); i++)
	{
		result = proposition.find(*i);

		if (result != -1)
			return result;
	}

	return -1;
}


void TrueTable::removeVars(string *proposition)
{
	vector<char> vars = this->getVariables();

	for (vector<char>::iterator i = vars.begin(); i != vars.end(); i++)
	{
		if (proposition->find(*i) != -1)
			proposition->replace(proposition->find(*i), sizeof(*i), " ");
	}

	vars.~vector();
}

void TrueTable::PrintTable()
{
	std::cout << " --- " << std::endl;

	for (int y = 0; y < this->getIndexOfRows() + 1; y++)
	{
		for (int x = 0; x < this->getIndexOfColumns(); x++)		
		{
			std::cout << this->matrix[y][x] << " ";
		}

		std::cout << std::endl;
	}
}

bool TrueTable::duplicateInVector(vector<char> Vect, char a)
{
	int count = 0;

	if (Vect.size() > 0)
	{
		while (count < Vect.size() - 1)
		{
			if (Vect.at(count) == a)
				return true;

			count++;
		}
	}

	return false;
}

vector<char> TrueTable::getVariables()
{
	vector<char> VariableVector;

	for (int x = 0; x < this->expression.length() - 1; x++)
	{
		if ((Variable::isUpperCaseVariable(this->expression[x])) && (!duplicateInVector(VariableVector, this->expression[x])))
		{
			VariableVector.insert(VariableVector.end(), this->expression[x]);
		}
	}

	return VariableVector;
}

int TrueTable::getIndexOfVariables()
{
	return this->getVariables().size();
}

int TrueTable::getIndexOfRows()
{	
	return pow(static_cast<double>(2), static_cast<double>(this->getVariables().size()));
}

int TrueTable::getIndexOfColumns()
{
	return (this->getVariables().size() + (this->ExpressionsContainer.size()));
}

TrueTable::~TrueTable(void)
{
	this->ExpressionsContainer.~vector();
	delete this->matrix;
}
