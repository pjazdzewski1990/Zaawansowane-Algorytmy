#include "stdafx.h"

#include <iostream>
#include <fstream>
#include <string>
#include <list>
#include <vector>
#include <sstream>
#include <deque>
#include <map>
#include <math.h>
#include <iterator>

//#include <boost/algorithm/string.hpp>

#include "Helper.h"
#include "Large.h"

using namespace std;

vector<Large> Helper::readFromfile(char* filename, long base, long in_base=16l){
	vector<Large> read = vector<Large>();
	Large num;

	string line = "";
	ifstream myfile (filename);
	if (myfile.is_open()){
		while (myfile.good()){
			getline (myfile,line);		//wczytaj cala linie 
			//podziel wedlug spacji
			/*vector<std::string> strs;	//wektor ciagow po rozdzieleniu
			boost::split(strs, line, boost::is_any_of(" "));
			if(strs.size()==2){
				//utwórz liczby i zapiszz je w wektorze
				num = Large::Set(strs[0], base, in_base);
				read.push_back(num);
				num = Large::Set(strs[1], base, in_base);
				read.push_back(num);
			}else{
				//pomin linie
			}*/
			vector<string> tokens;
			istringstream iss(line);
			copy(istream_iterator<string>(iss),
				istream_iterator<string>(),
				back_inserter<vector<string> >(tokens));
			if(tokens.size() == 2){
				read.push_back(Large::Set(tokens[0], base, in_base));
				read.push_back(Large::Set(tokens[1], base, in_base));
			}
			tokens.clear();
		}
		myfile.close(); // po fakcie zamknij plik
	}

	return read;
}