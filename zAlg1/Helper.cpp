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

#include <boost/algorithm/string.hpp>

#include "Helper.h"
#include "Large.h"

using namespace std;

vector<Large> Helper::readFromfile(string filename, long base, long in_base=16l){
	vector<Large> read = vector<Large>();
	Large num;

	string line = "";
	ifstream myfile (filename);
	if (myfile.is_open()){
		while (myfile.good()){
			getline (myfile,line);		//wczytaj cala linie 
			//podziel wedlug spacji
			vector<std::string> strs;	//wektor ciagow po rozdzieleniu
			boost::split(strs, line, boost::is_any_of(" "));
			if(strs.size()==2){
				//utwórz liczby i zapiszz je w wektorze
				num = Large::Set(strs[0], base, in_base);
				read.push_back(num);
				num = Large::Set(strs[1], base, in_base);
				read.push_back(num);
			}else{
				//pomin linie
			}
		}
		myfile.close(); // po fakcie zamknij plik
	}

	return read;
}