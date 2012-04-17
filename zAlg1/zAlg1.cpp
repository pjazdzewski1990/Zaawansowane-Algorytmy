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

	/*while(true){
		cin>>liczba1>>command>>liczba2;
		l1 = Large::Set(liczba1, base, in_base);
		l2 = Large::Set(liczba2, base, in_base);
		switch(command){
			case '+':
				res = l1 + l2;
				//res = Large::convert(res, 16);
				cout << res.toHex() << endl;
				break;
			case '-':
				res = l1 - l2;
				//res = Large::convert(res, 16);
				cout << res.toHex() << endl;
				break;
			case '*':
				res = l1 * l2;
				//res = Large::convert(res, 16);
				cout << res.toHex() << endl;
				break;
			case '/':
				res = l1 / l2;
				//res = Large::convert(res, 16);
				cout << res.toHex() << endl;
				break;
			case '?':
				cout << Large::comparisonToChar(l1,l2) << endl;
				break;
			case 'q':	//rundka profilera
				Profiler().profile();
				break;
			default:
				cout << "Nie poprawny operator" << endl;
		}
	//}*/
	/*while(true){
		cin>>liczba1>>command>>liczba2;
		u1 = LargeRational::Set(liczba1, base, in_base);
		u2 = LargeRational::Set(liczba2, base, in_base);
		switch(command){
			case '+':
				wynik = u1 + u2;
				//res = Large::convert(res, 16);
				cout << wynik.toHex() << endl;
				break;
			case '*':
				wynik = u1 * u2;
				//res = Large::convert(res, 16);
				cout << wynik.toHex() << endl;
				break;
			default:
				cout << "Nie poprawny operator" << endl;
		}
	}*/

	/*Tester t = Tester();
	t.run();
	TesterRational tt = TesterRational();
	tt.run();*/

	cin>>liczba1>>liczba2;
	l1 = Large::Set(liczba1, base, in_base);
	l2 = Large::Set(liczba2, base, in_base);
	cout << "GCD:" << LargeRational::GCD(l1, l2).toHex() << " Steiner:" << LargeRational::Steiner(l1, l2).toHex();

	return 0;
}

