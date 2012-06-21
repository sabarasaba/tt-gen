#include "prConditional.h"

char prConditional::Evaluate(bool A, bool B)
{
	if ((A) && (!B))
		return '0';

	return '1';
}