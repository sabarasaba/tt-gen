#pragma once
#include "validatorrule.h"
#include "OperatorList.h"
#include "Error.h"
#include <string>
#include <list>

using namespace std;
using std::string;

/**
*	Validator Rule: Operator. Verify that all the operators are well implemented.
*/
class Operator : public ValidatorRule
{
private:
	/* Check if the _operator is on the operators list. */
	bool isOperator(list<char> OperatorsList, char _Operator);

public:
	/**
	* Default constructor.
	*/
	Operator(string Expression);

	/**
	* Get the error, if any.
	*/
	virtual Error FindError();

	/**
	* Check if there is two variables together.
	*/
	virtual bool Valid();
};
