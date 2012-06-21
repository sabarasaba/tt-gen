#include "prAnd.h"

char prAnd::Evaluate(bool A, bool B)
{
	if (A && B)
		return '1';

	return '0';
}
