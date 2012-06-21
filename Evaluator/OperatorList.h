#pragma once
#include <list>

using namespace std;

/**
*	Singleton OperatorList. Provides a single instance with all the allowed operators and special operators.
*/
class OperatorList
{
private:
	/* the instance */
	static OperatorList* _operatorList;

	/* Prevent users from creating a copy of the singleton */
	OperatorList(const OperatorList&);

	/* Prevent users from creating a new 'OperatorList' */
	OperatorList() 
	{
		this->operatorList.clear();
		this->specialOperatorList.clear();
		
		// Add operators
		this->operatorList.insert(this->operatorList.end(), '|'); // OR Operator
		this->operatorList.insert(this->operatorList.end(), '&'); // And Operator
		this->operatorList.insert(this->operatorList.end(), '%'); // Xor Operator
		this->operatorList.insert(this->operatorList.end(), '>'); // Implication Operator
		this->operatorList.insert(this->operatorList.end(), '#'); // Pierce Operator
		this->operatorList.insert(this->operatorList.end(), '@'); // Sheffer Operator

		// Add special operators
		this->specialOperatorList.insert(this->specialOperatorList.end(), '~'); // Not Operator
	}

	list<char> operatorList;
	list<char> specialOperatorList;

public:
	/**
	* Acces point of the singleton.
	*/
	static OperatorList* instance()
	{
		if (!_operatorList)
			_operatorList = new OperatorList();

		return _operatorList;
	}

	/**
	* Property: get the operators list.
	*/
	list<char> getOperators() 
	{
		return this->operatorList;
	}

	/**
	* Property: get the special operators list.
	*/
	list<char> getSpecialOperators() 
	{
		return this->specialOperatorList;
	}

	/**
	* Default destructor.
	*/
	~OperatorList()
	{
		this->operatorList.~list();
		this->specialOperatorList.~list();
	}
};