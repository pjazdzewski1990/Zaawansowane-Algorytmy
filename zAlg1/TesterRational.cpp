//#include "stdafx.h"

#include "TesterRational.h"
#include "LargeRational.h"
//to nale¿y wykomentowaæ przed komplicj¹ z gcc
//#include "LargeRational.cpp"
#include "Large.h"

#include <string>
#include <iostream>
#include <time.h>
#include <vector>
#include <cstdlib>

#define TIMES 100

//uruchamiaj wszystkie testy po kolei
void TesterRational::run(){
	cout<< "Rational-start" <<endl;
	test_Lehmar();
	autotest_Lehmar(100000);
	test_Euclid();
	autotest_Euclid(100000);
	test_Steiner();
	autotest_GDC(100000);
	autotest_Steiner(100000);
	test_mul();
	test_add();
	test_GDC();
	test_substract();
	test_divide();
	test_set();
	cout<< "Rational-koniec" <<endl;
}

void TesterRational::autotest_GDC(int len){
	int i;
	Large x[3];
	vector<Large> y;
	srand( (unsigned)time(NULL) );

	for (i = 0; i < TIMES; i++) {
		x[0] = Large::Set(randomString(len), base, in_base);
		x[1] = Large::Set(randomString(len), base, in_base);
		x[2] = Large::Set(randomString(len), base, in_base);
		Large ga = LargeRational::GCD(x,3);
		ga.fix();
		Large gb = LargeRational::GCD(LargeRational::GCD(x[0], x[1]),x[2]);
		gb.fix();
		if (ga != gb) {
			for (int j = 0; j < 3; j++)	cout << x[j].toHex() << " ";
			cout << "A:Error " << ga.toHex() << " != "<< gb.toHex() << endl;  
		}

		y.clear();
		y.push_back(x[0]);
		y.push_back(x[1]);
		y.push_back(x[2]);
		ga = LargeRational::GCD(y);
		ga.fix();
		gb = LargeRational::GCD(LargeRational::GCD(x[0], x[1]), x[2]);
		gb.fix();
		if (ga != gb) {
			for (int j = 0; j < 3; j++)	cout << y[j].toHex() << " ";
			cout << "B:Error " << ga.toHex() << " != "<< gb.toHex() << endl;  
		}
		cout << "." ;
	}
	cout << "k" << endl;
}

void TesterRational::autotest_Steiner(int len){
	int i;
	Large l1;
	Large l2;
	srand( (unsigned)time(NULL) );

	for (i = 0; i < TIMES; i++) {
		l1 = Large::Set(randomString(len), base, in_base);
		l2 = Large::Set(randomString(len), base, in_base);
		Large ga = LargeRational::GCD(l1, l2);
		ga.fix();
		Large gb = LargeRational::Steiner(l1, l2);
		gb.fix();
		if (ga != gb) {
			cout << l1.toString() << " " << l2.toString();
			cout << " auto_Steiner:Error " << ga.toHex() << " != "<< gb.toHex() << endl;  
		}
		cout << "." ;
	}
	cout << "k" << endl;
}

void TesterRational::autotest_Euclid(int len){
	int i;
	Large l1;
	Large l2;
	srand( (unsigned)time(NULL) );

	for (i = 0; i < TIMES; i++) {
		l1 = Large::Set(randomString(len), base, in_base);
		l2 = Large::Set(randomString(len), base, in_base);
		Large ga = LargeRational::GCD(l1, l2);
		ga.fix();
		Large gb = LargeRational::Euclid(l1, l2);
		gb.fix();
		if (ga != gb) {
			cout << l1.toString() << " " << l2.toString();
			cout << " auto_Euclid:Error " << ga.toHex() << " != "<< gb.toHex() << endl;  
		}
		cout << "." ;
	}
	cout << "k" << endl;
}

void TesterRational::autotest_Lehmar(int len){
	int i;
	Large l1;
	Large l2;
	srand( (unsigned)time(NULL) );

	for (i = 0; i < TIMES; i++) {
		l1 = Large::Set(randomString(len), base, in_base);
		l2 = Large::Set(randomString(len), base, in_base);
		Large ga = LargeRational::GCD(l1, l2);
		ga.fix();
		Large gb = LargeRational::Lehmar2(l1, l2, 2);
		gb.fix();
		if (ga != gb) {
			cout << l1.toString() << " " << l2.toString();
			cout << " auto_Lehmar:Error " << ga.toHex() << " != "<< gb.toHex() << endl;  
		}
		cout << "." ;
	}
	cout << "k" << endl;
}

void TesterRational::test_mul(){
	//test1
	LargeRational test1 = LargeRational::Set("0_100", base, in_base);
	LargeRational test2 = LargeRational::Set("1_2001",base,in_base);
	LargeRational result = LargeRational::Set("0_1",base,in_base);
	if (!(test1*test2 == result)){
		cout << "Test_Mul_Rational1: " << test1.toString() << " " << test2.toString() << " " << result.toString() << endl;
	}
	//test2
	test1 = LargeRational::Set("21341_1200", base, in_base);
	test2 = LargeRational::Set("0_221",base,in_base);
	result = LargeRational::Set("0_1",base,in_base);
	if (!(test1*test2 == result)){
		cout << "Test_Mul_Rational2: " << test1.toString() << " " << test2.toString() << " " << result.toString() << endl;
	}
	//test3
	test1 = LargeRational::Set("122_321", base, in_base);
	test2 = LargeRational::Set("15_221",base,in_base);
	result = LargeRational::Set("196_71af",base,in_base);
	if (!(test1 * test2 == result)){
		cout << "Test_Mul_Rational3: " << test1.toString() << " " << test2.toString() << " " << result.toString() << endl;
	}
	//test4
	test1 = LargeRational::Set("4af_ccc", base, in_base);
	test2 = LargeRational::Set("109_139",base,in_base);
	result = LargeRational::Set("4d927_fa56c",base,in_base);
	if (!(test1 * test2 == result)){
		cout << "Test_Mul_Rational4: " << test1.toString() << " " << test2.toString() << " " << result.toString() << endl;
	}
	//test5
	test1 = LargeRational::Set("4af4af_abc", base, in_base);
	test2 = LargeRational::Set("111_122",base,in_base);
	result = LargeRational::Set("1aa4fa35_40da8",base,in_base);
	if (!(test1 * test2 == result)){
		cout << "Test_Mul_Rational5: " << test1.toString() << " " << test2.toString() << " " << result.toString() << endl;
	}
	//test6
	test1 = LargeRational::Set("1_abcdef", base, in_base);
	test2 = LargeRational::Set("1_223322",base,in_base);
	result = LargeRational::Set("1_16f3aa95f6be",base,in_base);
	if (!(test1 * test2 == result)){
		cout << "Test_Mul_Rational6: " << test1.toString() << " " << test2.toString() << " " << result.toString() << endl;
	}
	//test7
	test1 = LargeRational::Set("0_cdef", base, in_base);
	test2 = LargeRational::Set("1_3322",base,in_base);
	result = LargeRational::Set("0_2921f6be",base,in_base);//w tym przypadku mianownik jest zupe³nie dowolny bo 0/a==0/b
	if (!(test1 * test2 == result)){
		cout << "Test_Mul_Rational7: " << test1.toString() << " " << test2.toString() << " " << result.toString() << endl;
	}
}

void TesterRational::test_add(){
	//test1
	LargeRational test1 = LargeRational::Set("123_1", base, in_base);
	LargeRational test2 = LargeRational::Set("123_1",base,in_base);
	LargeRational result = LargeRational::Set("246_1",base,in_base);
	if (!(test1.add(test2) == result)){
		cout << "Test_Add_Rational1: " << test1.toString() << " " << test2.toString() << " " << result.toString() << endl;
	}
	//test2
	test1 = LargeRational::Set("1_321", base, in_base);
	test2 = LargeRational::Set("1_321",base,in_base);
	result = LargeRational::Set("2_321",base,in_base);
	if (!(test1.add(test2) == result)){
		cout << "Test_Add_Rational2: " << test1.toString() << " " << test2.toString() << " " << result.toString() << endl;
	}
	//test3
	test1 = LargeRational::Set("7_42", base, in_base);
	test2 = LargeRational::Set("11_c",base,in_base);
	result = LargeRational::Set("43_2c",base,in_base);
	if (!(test1.add(test2) == result)){
		cout << "Test_Add_Rational3: " << test1.toString() << " " << test2.toString() << " " << result.toString() << endl;
	}
	//test4
	test1 = LargeRational::Set("123_1", base, in_base);
	test2 = LargeRational::Set("1_123",base,in_base);
	result = LargeRational::Set("14aca_123",base,in_base);
	if (!(test1.add(test2) == result)){
		cout << "Test_Add_Rational4: " << test1.toString() << " " << test2.toString() << " " << result.toString() << endl;
	}
	//test5
	test1 = LargeRational::Set("23_521", base, in_base);
	test2 = LargeRational::Set("401_500",base,in_base);
	result = LargeRational::Set("43e6d_52100",base,in_base);
	if (!(test1+test2 == result)){
		cout << "Test_Add_Rational5: " << test1.toString() << " " << test2.toString() << " " << result.toString() << endl;
	}
	//test6
	test1 = LargeRational::Set("0_100", base, in_base);
	test2 = LargeRational::Set("52_456",base,in_base);
	result = LargeRational::Set("29_22b",base,in_base);
	if (!(test1+test2 == result)){
		cout << "Test_Add_Rational6: " << test1.toString() << " " << test2.toString() << " " << result.toString() << endl;
	}
	//test7
	test1 = LargeRational::Set("4d2_1964", base, in_base);
	test2 = LargeRational::Set("3fb_26aa",base,in_base);
	result = LargeRational::Set("23ee10_7ab68d",base,in_base);
	if (!(test1+test2 == result)){
		cout << "Test_Add_Rational7: " << test1.toString() << " " << test2.toString() << " " << result.toString() << endl;
	}
	//test8
	test1 = LargeRational::Set("3e9_1068", base, in_base);
	test2 = LargeRational::Set("1151_457",base,in_base);
	result = LargeRational::Set("3e8f3_ecb8",base,in_base);
	if (!(test1+test2 == result)){
		cout << "Test_Add_Rational8: " << test1.toString() << " " << test2.toString() << " " << result.toString() << endl;
	}
}

void TesterRational::test_GDC(){
	//test1
	Large test1 = Large::Set("123", base, in_base);
	Large test2 = Large::Set("123",base,in_base);
	Large result =Large::Set("123",base,in_base);
	if (!(LargeRational::GCD(test1, test2) == result)){
		cout << "Test_GDC_Rational1: " << test1.toString() << " " << test2.toString() << " " << result.toString() << endl;
	}
	//test2
	test1 = Large::Set("80", base, in_base);
	test2 = Large::Set("40",base,in_base);
	result =Large::Set("40",base,in_base);
	if (!(LargeRational::GCD(test1, test2) == result)){
		cout << "Test_GDC_Rational2: " << test1.toString() << " " << test2.toString() << " " << result.toString() << endl;
	}
	//test3
	test1 = Large::Set("1000", base, in_base);
	test2 = Large::Set("125",base,in_base);
	result =Large::Set("1",base,in_base);
	if (!(LargeRational::GCD(test1, test2) == result)){
		cout << "Test_GDC_Rational3: " << test1.toString() << " " << test2.toString() << " " << result.toString() << endl;
	}
	//test4
	test1 = Large::Set("4321", base, in_base);
	test2 = Large::Set("1234",base,in_base);
	result = Large::Set("5",base,in_base);
	if (!(LargeRational::GCD(test1, test2) == result)){
		cout << "Test_GDC_Rational4: " << test1.toString() << " " << test2.toString() << " " << result.toString() << endl;
	}
	//test5
	test1 = Large::Set("123321", base, in_base);
	test2 = Large::Set("0a0",base,in_base);
	result = Large::Set("1",base,in_base);
	if (!(LargeRational::GCD(test1, test2) == result)){
		cout << "Test_GDC_Rational5: " << test1.toString() << " " << test2.toString() << " " << result.toString() << endl;
	}
	//test6
	test1 = Large::Set("123321", base, in_base);
	test2 = Large::Set("0a0",base,in_base);
	result = Large::Set("1",base,in_base);
	if (!(LargeRational::GCD(test1, test2) == result)){
		cout << "Test_GDC_Rational6: " << test1.toString() << " " << test2.toString() << " " << result.toString() << endl;
	}
	//test7
	test1 = Large::Set("10", base, in_base);
	test2 = Large::Set("ffbbaa",base,in_base);
	result = Large::Set("2",base,in_base);
	if (!(LargeRational::GCD(test1, test2) == result)){
		cout << "Test_GDC_Rational7: " << test1.toString() << " " << test2.toString() << " " << result.toString() << endl;
	}
	//test8
	test1 = Large::Set("1", base, in_base);
	test2 = Large::Set("ffad213",base,in_base);
	result = Large::Set("1",base,in_base);
	if (!(LargeRational::GCD(test1, test2) == result)){
		cout << "Test_GDC_Rational8: " << test1.toString() << " " << test2.toString() << " " << result.toString() << endl;
	}
	//test9
	test1 = Large::Set("1123521", base, in_base);
	test2 = Large::Set("1",base,in_base);
	result = Large::Set("1",base,in_base);
	if (!(LargeRational::GCD(test1, test2) == result)){
		cout << "Test_GDC_Rational9: " << test1.toString() << " " << test2.toString() << " " << result.toString() << endl;
	}
	//test10
	test1 = Large::Set("11", base, in_base);
	test2 = Large::Set("1121",base,in_base);
	result = Large::Set("1",base,in_base);
	if (!(LargeRational::GCD(test1, test2) == result)){
		cout << "Test_GDC_Rational10: " << test1.toString() << " " << test2.toString() << " " << result.toString() << endl;
	}
	//test11
	test1 = Large::Set("a234", base, in_base);
	test2 = Large::Set("234b",base,in_base);
	result = Large::Set("1",base,in_base);
	if (!(LargeRational::GCD(test1, test2) == result)){
		cout << "Test_GDC_Rational11: " << test1.toString() << " " << test2.toString() << " " << result.toString() << endl;
	}
	//test12
	test1 = Large::Set("a234", base, in_base);
	test2 = Large::Set("b88cd404",base,in_base);
	result = Large::Set("a234",base,in_base);
	if (!(LargeRational::GCD(test1, test2) == result)){
		cout << "Test_GDC_Rational12: " << test1.toString() << " " << test2.toString() << " " << result.toString() << endl;
	}
}

void TesterRational::test_Steiner(){
	//test1
	Large test1 = Large::Set("123", base, in_base);
	Large test2 = Large::Set("123",base,in_base);
	Large result =Large::Set("123",base,in_base);
	if (!(LargeRational::Steiner(test1, test2) == result)){
		cout << "Test_Steiner_Rational1: " << test1.toString() << " " << test2.toString() << " " << result.toString() << endl;
	}
	//test2
	test1 = Large::Set("80", base, in_base);
	test2 = Large::Set("40",base,in_base);
	result =Large::Set("40",base,in_base);
	if (!(LargeRational::Steiner(test1, test2) == result)){
		cout << "Test_Steiner_Rational2: " << test1.toString() << " " << test2.toString() << " " << result.toString() << endl;
	}
	//test3
	test1 = Large::Set("1000", base, in_base);
	test2 = Large::Set("125",base,in_base);
	result =Large::Set("1",base,in_base);
	if (!(LargeRational::Steiner(test1, test2) == result)){
		cout << "Test_Steiner_Rational3: " << test1.toString() << " " << test2.toString() << " " << result.toString() << endl;
	}
	//test4
	test1 = Large::Set("4321", base, in_base);
	test2 = Large::Set("1234",base,in_base);
	result = Large::Set("5",base,in_base);
	if (!(LargeRational::Steiner(test1, test2) == result)){
		cout << "Test_Steiner_Rational4: " << test1.toString() << " " << test2.toString() << " " << result.toString() << endl;
	}
	//test5
	test1 = Large::Set("123321", base, in_base);
	test2 = Large::Set("0a0",base,in_base);
	result = Large::Set("1",base,in_base);
	if (!(LargeRational::Steiner(test1, test2) == result)){
		cout << "Test_Steiner_Rational5: " << test1.toString() << " " << test2.toString() << " " << result.toString() << endl;
	}
	//test6
	test1 = Large::Set("123321", base, in_base);
	test2 = Large::Set("0a0",base,in_base);
	result = Large::Set("1",base,in_base);
	if (!(LargeRational::Steiner(test1, test2) == result)){
		cout << "Test_Steiner_Rational6: " << test1.toString() << " " << test2.toString() << " " << result.toString() << endl;
	}
	//test7
	test1 = Large::Set("10", base, in_base);
	test2 = Large::Set("ffbbaa",base,in_base);
	result = Large::Set("2",base,in_base);
	if (!(LargeRational::Steiner(test1, test2) == result)){
		cout << "Test_Steiner_Rational7: " << test1.toString() << " " << test2.toString() << " " << result.toString() << endl;
	}
	//test8
	test1 = Large::Set("1", base, in_base);
	test2 = Large::Set("ffad213",base,in_base);
	result = Large::Set("1",base,in_base);
	if (!(LargeRational::Steiner(test1, test2) == result)){
		cout << "Test_Steiner_Rational8: " << test1.toString() << " " << test2.toString() << " " << result.toString() << endl;
	}
	//test9
	test1 = Large::Set("1123521", base, in_base);
	test2 = Large::Set("1",base,in_base);
	result = Large::Set("1",base,in_base);
	if (!(LargeRational::Steiner(test1, test2) == result)){
		cout << "Test_Steiner_Rational9: " << test1.toString() << " " << test2.toString() << " " << result.toString() << endl;
	}
	//test10
	test1 = Large::Set("11", base, in_base);
	test2 = Large::Set("1121",base,in_base);
	result = Large::Set("1",base,in_base);
	if (!(LargeRational::Steiner(test1, test2) == result)){
		cout << "Test_Steiner_Rational10: " << test1.toString() << " " << test2.toString() << " " << result.toString() << endl;
	}
	//test11
	test1 = Large::Set("a234", base, in_base);
	test2 = Large::Set("234b",base,in_base);
	result = Large::Set("1",base,in_base);
	if (!(LargeRational::Steiner(test1, test2) == result)){
		cout << "Test_Steiner_Rational11: " << test1.toString() << " " << test2.toString() << " " << result.toString() << endl;
	}
	//test12
	test1 = Large::Set("a234", base, in_base);
	test2 = Large::Set("b88cd404",base,in_base);
	result = Large::Set("a234",base,in_base);
	if (!(LargeRational::Steiner(test1, test2) == result)){
		cout << "Test_Steiner_Rational12: " << test1.toString() << " " << test2.toString() << " " << result.toString() << endl;
	}
}

void TesterRational::test_Euclid(){
	//test1
	Large test1 = Large::Set("123", base, in_base);
	Large test2 = Large::Set("123",base,in_base);
	Large result =Large::Set("123",base,in_base);
	if (!(LargeRational::Euclid(test1, test2) == result)){
		cout << "Test_Euclid_Rational1: " << test1.toString() << " " << test2.toString() << " " << result.toString() << endl;
	}
	//test2
	test1 = Large::Set("80", base, in_base);
	test2 = Large::Set("40",base,in_base);
	result =Large::Set("40",base,in_base);
	if (!(LargeRational::Euclid(test1, test2) == result)){
		cout << "Test_Euclid_Rational2: " << test1.toString() << " " << test2.toString() << " " << result.toString() << endl;
	}
	//test3
	test1 = Large::Set("1000", base, in_base);
	test2 = Large::Set("125",base,in_base);
	result =Large::Set("1",base,in_base);
	if (!(LargeRational::Euclid(test1, test2) == result)){
		cout << "Test_Euclid_Rational3: " << test1.toString() << " " << test2.toString() << " " << result.toString() << endl;
	}
	//test4
	test1 = Large::Set("4321", base, in_base);
	test2 = Large::Set("1234",base,in_base);
	result = Large::Set("5",base,in_base);
	if (!(LargeRational::Euclid(test1, test2) == result)){
		cout << "Test_Euclid_Rational4: " << test1.toString() << " " << test2.toString() << " " << result.toString() << endl;
	}
	//test5
	test1 = Large::Set("123321", base, in_base);
	test2 = Large::Set("0a0",base,in_base);
	result = Large::Set("1",base,in_base);
	if (!(LargeRational::Euclid(test1, test2) == result)){
		cout << "Test_Euclid_Rational5: " << test1.toString() << " " << test2.toString() << " " << result.toString() << endl;
	}
	//test6
	test1 = Large::Set("123321", base, in_base);
	test2 = Large::Set("0a0",base,in_base);
	result = Large::Set("1",base,in_base);
	if (!(LargeRational::Euclid(test1, test2) == result)){
		cout << "Test_Euclid_Rational6: " << test1.toString() << " " << test2.toString() << " " << result.toString() << endl;
	}
	//test7
	test1 = Large::Set("10", base, in_base);
	test2 = Large::Set("ffbbaa",base,in_base);
	result = Large::Set("2",base,in_base);
	if (!(LargeRational::Euclid(test1, test2) == result)){
		cout << "Test_Euclid_Rational7: " << test1.toString() << " " << test2.toString() << " " << result.toString() << endl;
	}
	//test8
	test1 = Large::Set("1", base, in_base);
	test2 = Large::Set("ffad213",base,in_base);
	result = Large::Set("1",base,in_base);
	if (!(LargeRational::Euclid(test1, test2) == result)){
		cout << "Test_Euclid_Rational8: " << test1.toString() << " " << test2.toString() << " " << result.toString() << endl;
	}
	//test9
	test1 = Large::Set("1123521", base, in_base);
	test2 = Large::Set("1",base,in_base);
	result = Large::Set("1",base,in_base);
	if (!(LargeRational::Euclid(test1, test2) == result)){
		cout << "Test_Euclid_Rational9: " << test1.toString() << " " << test2.toString() << " " << result.toString() << endl;
	}
	//test10
	test1 = Large::Set("11", base, in_base);
	test2 = Large::Set("1121",base,in_base);
	result = Large::Set("1",base,in_base);
	if (!(LargeRational::Euclid(test1, test2) == result)){
		cout << "Test_Euclid_Rational10: " << test1.toString() << " " << test2.toString() << " " << result.toString() << endl;
	}
	//test11
	test1 = Large::Set("a234", base, in_base);
	test2 = Large::Set("234b",base,in_base);
	result = Large::Set("1",base,in_base);
	if (!(LargeRational::Euclid(test1, test2) == result)){
		cout << "Test_Euclid_Rational11: " << test1.toString() << " " << test2.toString() << " " << result.toString() << endl;
	}
	//test12
	test1 = Large::Set("a234", base, in_base);
	test2 = Large::Set("b88cd404",base,in_base);
	result = Large::Set("a234",base,in_base);
	if (!(LargeRational::Euclid(test1, test2) == result)){
		cout << "Test_Euclid_Rational12: " << test1.toString() << " " << test2.toString() << " " << result.toString() << endl;
	}
}

void TesterRational::test_Lehmar(){
	//test0
	Large test1 = Large::Set("19ec6dc", base, in_base);
	Large test2 = Large::Set("989680",base,in_base);
	Large result =Large::Set("4",base,in_base);
	if (!(LargeRational::Lehmar2(test1, test2, 2) == result)){
		cout << "Test_Lehmar_Rational0: " << test1.toString() << " " << test2.toString() << " " << result.toString() << endl;
	}
	//test1
	test1 = Large::Set("123", base, in_base);
	test2 = Large::Set("123",base,in_base);
	result =Large::Set("123",base,in_base);
	if (!(LargeRational::Lehmar2(test1, test2, 2) == result)){
		cout << "Test_Lehmar_Rational1: " << test1.toString() << " " << test2.toString() << " " << result.toString() << endl;
	}
	//test2
	test1 = Large::Set("80", base, in_base);
	test2 = Large::Set("40",base,in_base);
	result =Large::Set("40",base,in_base);
	if (!(LargeRational::Lehmar2(test1, test2, 2) == result)){
		cout << "Test_Lehmar_Rational2: " << test1.toString() << " " << test2.toString() << " " << result.toString() << endl;
	}
	//test3
	test1 = Large::Set("1000", base, in_base);
	test2 = Large::Set("125",base,in_base);
	result =Large::Set("1",base,in_base);
	if (!(LargeRational::Lehmar2(test1, test2, 2) == result)){
		cout << "Test_Lehmar_Rational3: " << test1.toString() << " " << test2.toString() << " " << result.toString() << endl;
	}
	//test4
	test1 = Large::Set("4321", base, in_base);
	test2 = Large::Set("1234",base,in_base);
	result = Large::Set("5",base,in_base);
	if (!(LargeRational::Lehmar2(test1, test2, 2) == result)){
		cout << "Test_Lehmar_Rational4: " << test1.toString() << " " << test2.toString() << " " << result.toString() << endl;
	}
	//test5
	test1 = Large::Set("123321", base, in_base);
	test2 = Large::Set("0a0",base,in_base);
	result = Large::Set("1",base,in_base);
	if (!(LargeRational::Lehmar2(test1, test2, 2) == result)){
		cout << "Test_Lehmar_Rational5: " << test1.toString() << " " << test2.toString() << " " << result.toString() << endl;
	}
	//test6
	test1 = Large::Set("123321", base, in_base);
	test2 = Large::Set("0a0",base,in_base);
	result = Large::Set("1",base,in_base);
	if (!(LargeRational::Lehmar2(test1, test2, 2) == result)){
		cout << "Test_Lehmar_Rational6: " << test1.toString() << " " << test2.toString() << " " << result.toString() << endl;
	}
	//test7
	test1 = Large::Set("10", base, in_base);
	test2 = Large::Set("ffbbaa",base,in_base);
	result = Large::Set("2",base,in_base);
	if (!(LargeRational::Lehmar2(test1, test2, 2) == result)){
		cout << "Test_Lehmar_Rational7: " << test1.toString() << " " << test2.toString() << " " << result.toString() << endl;
	}
	//test8
	test1 = Large::Set("1", base, in_base);
	test2 = Large::Set("ffad213",base,in_base);
	result = Large::Set("1",base,in_base);
	if (!(LargeRational::Lehmar2(test1, test2, 2) == result)){
		cout << "Test_Lehmar_Rational8: " << test1.toString() << " " << test2.toString() << " " << result.toString() << endl;
	}
	//test9
	test1 = Large::Set("1123521", base, in_base);
	test2 = Large::Set("1",base,in_base);
	result = Large::Set("1",base,in_base);
	if (!(LargeRational::Lehmar2(test1, test2, 2) == result)){
		cout << "Test_Lehmar_Rational9: " << test1.toString() << " " << test2.toString() << " " << result.toString() << endl;
	}
	//test10
	test1 = Large::Set("11", base, in_base);
	test2 = Large::Set("1121",base,in_base);
	result = Large::Set("1",base,in_base);
	if (!(LargeRational::Lehmar2(test1, test2, 2) == result)){
		cout << "Test_Lehmar_Rational10: " << test1.toString() << " " << test2.toString() << " " << result.toString() << endl;
	}
	//test11
	test1 = Large::Set("a234", base, in_base);
	test2 = Large::Set("234b",base,in_base);
	result = Large::Set("1",base,in_base);
	if (!(LargeRational::Lehmar2(test1, test2, 2) == result)){
		cout << "Test_Lehmar_Rational11: " << test1.toString() << " " << test2.toString() << " " << result.toString() << endl;
	}
	//test12
	test1 = Large::Set("a234", base, in_base);
	test2 = Large::Set("b88cd404",base,in_base);
	result = Large::Set("a234",base,in_base);
	if (!(LargeRational::Lehmar2(test1, test2, 2) == result)){
		cout << "Test_Lehmar_Rational12: " << test1.toString() << " " << test2.toString() << " " << result.toString() << endl;
	}
	//test13
	test1 = Large::Set("40072", base, in_base);
	test2 = Large::Set("a3e",base,in_base);
	result = Large::Set("2",base,in_base);
	if (!(LargeRational::Lehmar2(test1, test2, 2) == result)){
		cout << "Test_Lehmar_Rational13: " << test1.toString() << " " << test2.toString() << " " << result.toString() << endl;
	}
}

void TesterRational::test_substract(){
	//test1
	LargeRational test1 = LargeRational::Set("123_123", base, in_base);
	LargeRational test2 = LargeRational::Set("23_123",base,in_base);
	LargeRational result = LargeRational(Large::Set("12300",base,in_base), Large::Set("14ac9",base,in_base));
	if (!(test1.substract(test2) == result)){
		cout << "Test_Substract_Rational1: " << test1.toString() << " " << test2.toString() << " " << result.toString() << endl;
	}
	//test2
	test1 = LargeRational::Set("2000_5000", base, in_base);
	test2 = LargeRational::Set("5_10",base,in_base);
	result = LargeRational(Large::Set("7000",base,in_base), Large::Set("50000",base,in_base));
	if (!(test1.substract(test2) == result)){
		cout << "Test_Substract_Rational2: " << test1.toString() << " " << test2.toString() << " " << result.toString() << endl;
	}
	//test3
	test1 = LargeRational::Set("1_10", base, in_base);
	test2 = LargeRational::Set("1_100",base,in_base);
	result = LargeRational(Large::Set("f0",base,in_base), Large::Set("1000",base,in_base));
	if (!(test1.substract(test2) == result)){
		cout << "Test_Substract_Rational3: " << test1.toString() << " " << test2.toString() << " " << result.toString() << endl;
	}
	//test4
	test1 = LargeRational::Set("100_100", base, in_base);
	test2 = LargeRational::Set("50_100",base,in_base);
	result = LargeRational(Large::Set("b000",base,in_base), Large::Set("10000",base,in_base));
	if (!(test1.substract(test2) == result)){
		cout << "Test_Substract_Rational4: " << test1.toString() << " " << test2.toString() << " " << result.toString() << endl;
	}
	//test5
	test1 = LargeRational::Set("10_10", base, in_base);
	test2 = LargeRational::Set("10_10",base,in_base);
	result = LargeRational(Large::Set("0",base,in_base), Large::Set("100",base,in_base));
	if (!(test1.substract(test2) == result)){
		cout << "Test_Substract_Rational5: " << test1.toString() << " " << test2.toString() << " " << result.toString() << endl;
	}
}

void TesterRational::test_divide(){
	//test1
	LargeRational test1 = LargeRational::Set("123_123", base, in_base);
	LargeRational test2 = LargeRational(Large::Set("123",base,in_base), Large::Set("123",base,in_base));
	LargeRational result = LargeRational(Large::Set("14ac9",base,in_base), Large::Set("14ac9",base,in_base));
	if (!(test1.divide(test2) == result)){
		cout << "Test_Divide_Rational1: " << test1.toString() << " " << test2.toString() << " " << result.toString() << endl;
	}
	//test2
	test1 = LargeRational::Set("12_34", base, in_base);
	test2 = LargeRational(Large::Set("56",base,in_base),Large::Set("78",base,in_base));
	result = LargeRational(Large::Set("870",base,in_base), Large::Set("1178",base,in_base));
	if (!(test1.divide(test2) == result)){
		cout << "Test_Divide_Rational2: " << test1.toString() << " " << test2.toString() << " " << result.toString() << endl;
	}
	//test3
	test1 = LargeRational::Set("_34", base, in_base);
	test2 = LargeRational(Large::Set("12",base,in_base), Large::Set("12_34",base,in_base));
	result = LargeRational(Large::Set("0",base,in_base), Large::Set("3a8",base,in_base));
	if (!(test1.divide(test2) == result)){
		cout << "Test_Divide_Rational3: " << test1.toString() << " " << test2.toString() << " " << result.toString() << endl;
	}
	//test4
	test1 = LargeRational::Set("12_", base, in_base);
	test2 = LargeRational::Set("22_33",base,in_base);
	result = LargeRational(Large::Set("396",base,in_base), Large::Set("22",base,in_base));
	if (!(test1.divide(test2) == result)){
		cout << "Test_Divide_Rational4: " << test1.toString() << " " << test2.toString() << " " << result.toString() << endl;
	}
	//test5
	test1 = LargeRational::Set("123456_123", base, in_base);
	test2 = LargeRational::Set("321_654321",base,in_base);
	result = LargeRational(Large::Set("7336bf94116",base,in_base), Large::Set("38e83",base,in_base));
	if (!(test1.divide(test2) == result)){
		cout << "Test_Divide_Rational5: " << test1.toString() << " " << test2.toString() << " " << result.toString() << endl;
	}
	//test6
	test1 = LargeRational::Set("1357_12", base, in_base);
	test2 = LargeRational::Set("321321_654",base,in_base);
	result = LargeRational(Large::Set("7a628c",base,in_base), Large::Set("3855852",base,in_base));
	if (!(test1.divide(test2) == result)){
		cout << "Test_Divide_Rational6: " << test1.toString() << " " << test2.toString() << " " << result.toString() << endl;
	}
}

void TesterRational::test_set(){
	//test1
	LargeRational test1 = LargeRational::Set("123", base, in_base);
	LargeRational test2 = LargeRational(Large::Set("123",base,in_base));
	if (!(test1 == test2)){
		cout << "Test_Set_Rational1: " << test1.toString() << " " << test2.toString() << endl;
	}
	//test2
	test1 = LargeRational::Set("123_12", base, in_base);
	Large licznik = Large::Set("123",base,in_base); 
	Large mianownik = Large::Set("12",base,in_base); 
	test2 = LargeRational(licznik, mianownik);
	if (!(test1 == test2)){
		cout << "Test_Set_Rational2: " << test1.toString() << " " << test2.toString() << endl;
	}
	//test2
	test1 = LargeRational::Set("00123_0012", base, in_base);
	licznik = Large::Set("00123",base,in_base); 
	mianownik = Large::Set("0012",base,in_base); 
	test2 = LargeRational(licznik, mianownik);
	if (!(test1 == test2)){
		cout << "Test_Set_Rational3: " << test1.toString() << " " << test2.toString() << endl;
	}
	//test3
	test1 = LargeRational::Set("0012300_001200", base, in_base);
	licznik = Large::Set("0012300",base,in_base); 
	mianownik = Large::Set("001200",base,in_base); 
	test2 = LargeRational(licznik, mianownik);
	if (!(test1 == test2)){
		cout << "Test_Set_Rational3: " << test1.toString() << " " << test2.toString() << endl;
	}
	//test4
	test1 = LargeRational::Set("_1", base, in_base);
	licznik = Large::Set("0",base,in_base); 
	mianownik = Large::Set("1",base,in_base); 
	test2 = LargeRational(licznik, mianownik);
	if (!(test1 == test2)){
		cout << "Test_Set_Rational4: " << test1.toString() << " " << test2.toString() << endl;
	}
	//test5
	test1 = LargeRational::Set("-112345_112345", base, in_base);
	licznik = Large::Set("-112345",base,in_base); 
	mianownik = Large::Set("112345",base,in_base); 
	test2 = LargeRational(licznik, mianownik);
	if (!(test1 == test2)){
		cout << "Test_Set_Rational5: " << test1.toString() << " " << test2.toString() << endl;
	}
}

string TesterRational::randomString(int max_length){
	long number = rand();
	number = abs(number%max_length);
	number++;
	string res = "";
	while(number>0){
		res.append(1,number%10+'0');
		number/=10;
	}
	return res;
}