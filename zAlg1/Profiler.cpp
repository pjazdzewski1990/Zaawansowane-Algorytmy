#include "stdafx.h"

#include "Profiler.h"
#include "Large.h"
#include <string>
#include <iostream>
#include <fstream>
using namespace std;

Profiler::Profiler(){
}

void Profiler::profile(){
	string l1_str;
	string l2_str;

	long multiKara;
	long multiClas;
	long multiDiv;

	long addKara;
	long addClas;
	long addDiv;

	ofstream myfile;
	myfile.open ("report.txt", ios_base::out | ios_base::in);

	do{
		cout << "Podaj 2 liczby odzielone spacja" << endl;
		cin>>l1_str>>l2_str;
		
		Large l1 = Large::Set(l1_str, 100, 16);
		Large l2 = Large::Set(l2_str, 100, 16);

		//testuj Karatsube
		multiplication_count = addition_count = 0;
		Large result = l1.Karatsuba(l2);
		multiKara = multiplication_count;
		addKara = addition_count;

		//testuj klasyczny algorytm
		multiplication_count = addition_count = 0;
		result = l1.ColumnMultplication(l2);
		multiClas = multiplication_count;
		addClas = addition_count;

		//testuj klasyczny algorytm
		multiplication_count = addition_count = 0;
		result = l1/l2;
		multiDiv = multiplication_count;
		addDiv = addition_count;

		//zapisz dane z obecnego obrotu
		myfile << l1_str << " i " << l2_str << endl;
		myfile << "Karatsuba	*" << multiKara << "	+" << addKara ;
		myfile << "\n";
		myfile << "Multi		*" << multiClas << "	+" << addClas;
		myfile << "\n";
		myfile << "Div			*" << multiDiv << "		+" << addDiv;
		myfile << "\n";
		myfile.flush();
	}while(true);

	myfile.close();
}