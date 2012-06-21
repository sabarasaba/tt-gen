#pragma once
#include "ValidatorRule.h"
#include "Error.h"
#include <string>
#include <iostream>
#include <vector>

using namespace std;
using std::string;

/**
 *  Expression. Allow to validate an expression with all the validation rules on the ValidatorRule vector, and give us
		simple property for getting the errors ocurred, if any. It also provides a few methods for printing
		the sub-expressions of the expression and for printing the erros on screen.
 */
class Expression
{
private:
	/* Expressions Container. */
	vector<string> ExpressionsContainer;

	/* Contains the main expression. */
	string expression;

	/* Contains the rules for the expression. */
	vector<ValidatorRule *> rules;

	/* Contains the errors of the expression, if any. */
	vector<Error> errors;

	/* Amount of expressions. */
	int IndexOfExpressions();

	/* Add rules for the expression. */
	void AddRules();

public:
	/**
    * Default constructor.
    */
	Expression();

	/**
    * Detailled Constructor.
    */
	Expression(string Expression);

	/**
	* Validate Expression, if there's an error the messages are inserted on the error vector.
	*/
	bool Valid();

	/**
	* Print expressions on screen.
	*/
	void PrintExpressions();

	/**
	* Print errors on screen, if any.
	*/
	void PrintErrors();

	/**
	* Resolve expressions.
	*/
	void ResolveExpressions();

	/**
	* Return a substring from str.
	*/
	static string subString(string str, int From, int To);

	/**
	* Get the errors of the expression, if any.
	*/
	vector<Error> GetErrors() { return this->errors; }

	/**
	* Get the expressions vector.
	*/
	vector<string> GetExpressions() { return this->ExpressionsContainer; }

	/**
	* Destructor.
	*/
	~Expression();
};
