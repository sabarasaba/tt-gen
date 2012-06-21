#include "prSheffer.h"

char prSheffer::Evaluate(bool A, bool B)
{
	if (!(A && B))
		return '1';

	return '0';
}