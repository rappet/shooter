#pragma once
#include <iostream>
using namespace std;

#define DEBUG
#ifdef DEBUG
	#define INFO(x) { clog << __FILE__ << "_" << __LINE__ << ": " <<x << endl; }
#else
	#define INFO(x)
#endif
