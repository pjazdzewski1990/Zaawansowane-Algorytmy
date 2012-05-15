#ifndef _HELPER_h_included_
#define _HELPER_h_included_

#include <iostream>
#include <string>
#include <list>
#include <vector>
#include <sstream>
#include <deque>
#include <map>
#include <math.h>

#include "Large.h"

using namespace std;

//klasa zawierajaca statyczne metody pomocnicze, 
// ktore nie sa zwiazane konkretnie z zadna inna klasa 
class Helper
{
	public:
		//wczytywanei z pliku na potrzeby CRT
		static vector<Large> readFromfile(string filename, long base, long in_base);
};

#endif