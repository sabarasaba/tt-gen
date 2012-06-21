#pragma once
#include "ValidatorRule.h"
#include "Error.h"
#include <string>

using std::string;

/**
*	Validator Rule: Parentesis. Verify that all parentesis are well used.
*/
class Parentesis : public ValidatorRule
{
private:
	/*
	   position = From where starts to analize the expression.
	   open =>  Amount of open parentesis.
	   closed =>  Amount of closed parentesis. 
	*/
	bool parentesisDivision(int position, int open, int closed);

	/* Return position of maximum abs of parentesis. */
	int GetMaxIndex();

public:
	/**
	* Default constructor.
	*/
	Parentesis(string Expression);

	/**
	* Get the error, if any.
	*/
    virtual Error FindError();

	/**
	* Check if all the parentesis are well used.
	*/
	virtual bool Valid();
};
