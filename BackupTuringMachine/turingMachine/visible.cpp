#include "visible.h"
#include <string>

using namespace std;

string visible(string value)
{
	const string lambda("\\");
	if (value.empty())
	{
		value = lambda;
	}
	return value;
}