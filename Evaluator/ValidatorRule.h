#pragma once
#include "Error.h"
#include <string>

using namespace std;

/**
* Abstract Class: ValidatorRule. Provides one method to validate an expression, and another to find the error.
*/
class ValidatorRule abstract
{
	private:
		/* The expression. */
		string expression;

	public:
		/**
		* Validate a rule.
		*/
		virtual bool Valid() abstract;

		/**
		* Find the error on the rule.
		*/
		virtual Error FindError() abstract;

		/**
		* Set the expression.
		*/
		void SetExpression(string Expression) { if(!Expression.empty()) this->expression = Expression; }

		/**
		* Get the expression.
		*/
		string GetExpression() { return this->expression; }
};