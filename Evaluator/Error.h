#pragma once
#include <string>

using std::string;

/**
*	Error Object: will describe some error ocurred and the line number where the error is located.
*/
class Error
{
private:
	int lineNumber;
	string errorMessage;

public:
		/**
		* Default constructor.
		*/
		Error()
		{
			this->lineNumber = -1;
			this->errorMessage = "No error.";
		}

		/**
		* Detailled error constructor.
		*/
		Error(int LineNumber, string ErrorMessage)
		{
			this->lineNumber = LineNumber;
			this->errorMessage = ErrorMessage;
		}

		/**
		* Get error message.
		*/
		string GetErrorMessage() { return this->errorMessage; }

		/**
		* Get line number of error.
		*/
		int GetLineNumber() { return this->lineNumber; }
};