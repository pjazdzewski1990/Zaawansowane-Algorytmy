// zAlg1.cpp : Defines the entry point for the console application.
//
/*
	Program napisany pod Windowsa, by uruchomiæ na sigmie prosze o wykomentowanie poni¿szej linijki 
	"stdafx.h" który jest tworem wybitnie windowsowym
*/
#include "stdafx.h"

#include <cstdlib>
#include <iostream>
#include <string>
#include <list>
#include <vector>
#include <sstream>
#include <deque>
#include <map>

#include "Large.h"
#include "LargeRational.h"

#include "Helper.h"

#include "Profiler.h"
#include "Tester.h"
#include "TesterRational.h"

using namespace std;

int main(int argc, char* argv[])
{
	//zak³adamy ¿e system docelowy jest pierwszym parametrem
	long base = 100;
	if(argc >= 100){
		base = atoi(argv[1]);
	}

	//system w którym podawane bêd¹ liczby z wejœcia
	long in_base = 16;
	//cout << "Podaj baze systemu w ktorym bêdziesz podawa³: ";
	//cin >> in_base;

	string liczba1;
	string liczba2;
	char command;

	Large l1(base);
	Large l2(base);
	Large res(base);

	LargeRational u1(base);
	LargeRational u2(base);
	LargeRational wynik(base);

	vector<Large> vect = Helper::readFromfile("crt.txt", base, 10);
	res = Large::crt(vect);

	Tester t = Tester();
	//t.run();
	TesterRational tt = TesterRational();
	//tt.run();

	/*
	cin>>liczba1>>liczba2;
	l1 = Large::Set(liczba1, base, in_base);
	l2 = Large::Set(liczba2, base, in_base);
	cout << "GCD:" << LargeRational::GCD(l1, l2).toHex() << " Steiner:" << LargeRational::Steiner(l1, l2).toHex();
	*/
	return 0;
}

