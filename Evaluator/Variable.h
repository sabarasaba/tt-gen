#pragma once
#include "validatorrule.h"
#include "Error.h"
#include <string>

using std::string;

/**
*	Validator Rule: Variable. Verify that there's not two variables together.
*/
class Variable : public ValidatorRule
{
public:
	/**
	* Default constructor.
	*/
	Variable(string Expression);

	/**
	* Checks if is a Variable.
	*/
	static bool isUpperCaseVariable(char charsito);

	/**
	* Get the error, if any.
	*/
	virtual Error FindError();

	/**
	* Check if there is two variables together.
	*/
	virtual bool Valid();
};
