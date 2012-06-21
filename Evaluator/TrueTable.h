#pragma once
#include "OperatorList.h"
#include <string>
#include <vector>

using std::string;
using namespace std;

/**
*	TrueTable. Allow to resolve a true table, using a expression container and the current expression. It also
	give a property to acces the matrix, but not the one of neo! lmao.
*/
class TrueTable
{
private:
	/* Original expression. */
	string expression;

	/* Expressions Container. */
	vector<string> ExpressionsContainer;

	/* Get vector of variables. */
	vector<char> getVariables();

	/* Get index of variables. */
	int getIndexOfVariables();

	/* Get index of rows, 2^Index_Of_Variables. */
	int getIndexOfRows();

	/* Get index of columns, Index_Of_Variables + Index_Of_Expressions. */
	int getIndexOfColumns();

	/* Return the position on the string, where is placed the 'nexus operator', the operator betwin two propositions. */
	int getNexusOperator(string proposition);

	/* Remove all the variables from a expression. */
	void removeVars(string *proposition);

	/* Return the expression A from a proposition. */
	int findExpressionA(string proposition, int nexusOperator);

	/* Return the expression B from a proposition. */
	int findExpressionB(string proposition, int nexusOperator);

	/* Checks if a single char is on a vector of chars. */
	bool duplicateInVector(vector<char> Vect, char a);

	/* Matrix creator, like the architect !!1 */
	string** createMatrix(int rows, int cols);

	/* The matrix table. */
	string** matrix;

public:
	/**
	* Default constructor.
	*/
	TrueTable(string Expression, vector<string> _ExpressionsContainer);

	/**
	* Complete the propositions.
	*/
	void DoLogic();

	/**
	* Get the original expression.
	*/
	string GetExpression() { return this->expression; }

	/**
	* Print table on screen.
	*/
	void PrintTable();

	/**
	* Desctructor.
	*/
	~TrueTable(void);
};
