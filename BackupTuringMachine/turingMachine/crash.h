#ifndef CRASH_H
#define CRASH_H

#include <stdexcept>
#include <string>

using namespace std;

class Crash : public runtime_error
{
public:
	Crash(string Reason);

};

#endif