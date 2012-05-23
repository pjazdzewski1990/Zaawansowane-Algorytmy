#include "stdafx.h"

#include "Tester.h"
#include "LargeRational.h"
#include "TesterRational.h"

#include <string>
#include <iostream>
#include <time.h>

#define TIMES 10000

//uruchamiaj wszystkie testy po kolei
void Tester::run(){
	cout<< "Test-start" <<endl;

	autotest_crt(1000);
	test_inverse();
	autotest_inverse(100000);
	test_rest();
	test_hex();
	test_divide();
	test_multpily();
	test_bigger();
	test_smaller();
	test_add();
	test_substract();
	
	cout<< "Test-koniec" <<endl;
}

//testuj odwrotnosc modulo
void Tester::autotest_inverse(int len){
	Large one = Large::Set("1", base, in_base);
	Large zero = Large::Set("0", base, in_base);

	TesterRational tr = TesterRational();
	int i;
	Large a;
	Large mod;
	Large inv;
	srand( (unsigned)time(NULL) );

	for (i = 0; i < TIMES; i++) {
		a = Large::Set(tr.randomString(len), base, in_base);
		mod = Large::Set(tr.randomString(len), base, in_base);
		//jeœli a jest wiêksza ni¿ mod to nie ma sensu szukaæ
		if(a > mod){
			i--;
			continue;
		}
		inv = a.inverseMod(mod);

		Large result = Large(); 
		(a * inv).divide(mod, result);
		//wynik jest b³êdny gdy reszta nie jest równa jeden i inv nie jest zerem(znaczy to ze nie ma odwrotnosci)
		if (result.compareAbsolute(one)!=0 && inv.compareAbsolute(zero)!=0) {
			cout << " auto_Inv:Error " << endl;  
			cout << " a " << a.toString() << " inv " << inv.toString()  << " mod " << mod.toString() << endl;;
		}
		cout << "." ;
	}
	cout << "k" << endl;
}

//testuj odwrotnosc modulo
void Tester::test_inverse(){
	//test1
	Large one = Large::Set("1", base, in_base);
	Large zero = Large::Set("0", base, in_base);

	Large test1 = Large::Set("12", base, in_base);
	Large mod = Large::Set("2f", base, in_base);
	Large inv = test1.inverseMod(mod);
	Large result;

	//jeœli istnieje liczba odwrotna(nie jest zerem) i odwrotnoœæ razy liczba mod to jeden,
	// to wynik jest poprawny
	/*(test1 * inv).divide(mod, result);
	if (inv.compareAbsolute(zero)!=0 && result.compareAbsolute(one)!=0){
		cout << "Test_Inverse1: " << test1.toString() << " " << mod.toString() << endl;
	}
	//test2
	test1 = Large::Set("3", base, in_base);
	mod = Large::Set("7", base, in_base);
	inv = test1.inverseMod(mod);
	(test1 * inv).divide(mod, result);
	if (inv.compareAbsolute(zero)!=0 && result.compareAbsolute(one)!=0){
		cout << "Test_Inverse2: " << test1.toString() << " " << mod.toString() << endl;
	}*/
	//test3
	test1 = Large::Set("c", base, in_base);
	mod = Large::Set("11", base, in_base);
	inv = test1.inverseMod(mod);
	(test1 * inv).divide(mod, result);
	if (inv.compareAbsolute(zero)!=0 && result.compareAbsolute(one)!=0){
		cout << "Test_Inverse3: " << test1.toString() << " " << mod.toString() << endl;
	}
	//test4
	test1 = Large::Set("21", base, in_base);
	mod = Large::Set("61", base, in_base);
	inv = test1.inverseMod(mod);
	(test1 * inv).divide(mod, result);
	if (inv.compareAbsolute(zero)!=0 && result.compareAbsolute(one)!=0){
		cout << "Test_Inverse4: " << test1.toString() << " " << mod.toString() << endl;
	}
	//test5
	test1 = Large::Set("b", base, in_base);
	mod = Large::Set("17", base, in_base);
	inv = test1.inverseMod(mod);
	(test1 * inv).divide(mod, result);
	if (inv.compareAbsolute(zero)!=0 && result.compareAbsolute(one)!=0){
		cout << "Test_Inverse5: " << test1.toString() << " " << mod.toString() << endl;
	}
	//test6
	test1 = Large::Set("5", base, in_base);
	mod = Large::Set("13", base, in_base);
	inv = test1.inverseMod(mod);
	(test1 * inv).divide(mod, result);
	if (inv.compareAbsolute(zero)!=0 && result.compareAbsolute(one)!=0){
		cout << "Test_Inverse6: " << test1.toString() << " " << mod.toString() << endl;
	}
	//test7
	test1 = Large::Set("80722", base, in_base);
	mod = Large::Set("41413", base, in_base);
	inv = test1.inverseMod(mod);
	(test1 * inv).divide(mod, result);
	if (inv.compareAbsolute(zero)!=0 && result.compareAbsolute(one)!=0){
		cout << "Test_Inverse7: " << test1.toString() << " " << mod.toString() << endl;
	}
	//test8
	test1 = Large::Set("39782", base, in_base);
	mod = Large::Set("43d35", base, in_base);
	inv = test1.inverseMod(mod);
	Large test = test1.inverseMod(mod);
	(test1 * inv).divide(mod, result);
	if (inv.compareAbsolute(zero)!=0 && result.compareAbsolute(one)!=0){
		cout << "Test_Inverse8: " << test1.toString() << " " << mod.toString() << endl;
	}
	//test9
	test1 = Large::Set("45881", base, in_base);
	mod = Large::Set("152", base, in_base);
	inv = test1.inverseMod(mod);
	test = test1.inverseMod(mod);
	(test1 * inv).divide(mod, result);
	if (inv.compareAbsolute(zero)!=0 && result.compareAbsolute(one)!=0){
		cout << "Test_Inverse9: " << test1.toString() << " " << mod.toString() << endl;
	}
}

//testuj resztê zwracan¹ przez metode divide
void Tester::test_rest(){
	//test0
	Large test1 = Large::Set("1004", base, in_base);
	Large test2 = Large::Set("24c", base, in_base);
	Large rest = Large(base);
	test1.divide(test2, rest);
	Large expected = Large::Set("23c", base, in_base); 
	if (rest != expected){
		cout << "Test_Rest0: " << test1.toString() << " " << test2.toString() << endl;
	}
	//test1
	test1 = Large::Set("1234", base, in_base);
	test2 = Large::Set("23c", base, in_base);
	rest = Large(base);
	test1.divide(test2, rest);
	expected = Large::Set("54", base, in_base); 
	if (rest != expected){
		cout << "Test_Rest1: " << test1.toString() << " " << test2.toString() << endl;
	}
	//test2
	test1 = Large::Set("4321", base, in_base);
	test2 = Large::Set("1234", base, in_base);
	rest = Large(base);
	test1.divide(test2, rest);
	expected = Large::Set("c85", base, in_base); 
	if (rest != expected){
		cout << "Test_Rest2: " << test1.toString() << " " << test2.toString() << endl;
	}
	//test3
	test1 = Large::Set("43210", base, in_base);
	test2 = Large::Set("12", base, in_base);
	rest = Large(base);
	test1.divide(test2, rest);
	expected = Large::Set("a", base, in_base); 
	if (rest != expected){
		cout << "Test_Rest3: " << test1.toString() << " " << test2.toString() << endl;
	}
	//test4
	test1 = Large::Set("456", base, in_base);
	test2 = Large::Set("400", base, in_base);
	rest = Large(base);
	test1.divide(test2, rest);
	expected = Large::Set("56", base, in_base); 
	if (rest != expected){
		cout << "Test_Rest4: " << test1.toString() << " " << test2.toString() << endl;
	}
	//test5
	test1 = Large::Set("356", base, in_base);
	test2 = Large::Set("400", base, in_base);
	rest = Large(base);
	test1.divide(test2, rest);
	expected = Large::Set("356", base, in_base); 
	if (rest != expected){
		cout << "Test_Rest5: " << test1.toString() << " " << test2.toString() << endl;
	}
	//test6
	test1 = Large::Set("3356", base, in_base);
	test2 = Large::Set("512", base, in_base);
	rest = Large(base);
	test1.divide(test2, rest);
	expected = Large::Set("a2", base, in_base); 
	if (rest != expected){
		cout << "Test_Rest6: " << test1.toString() << " " << test2.toString() << endl;
	}
}

//testuj
void Tester::test_hex(){
	//test1
	Large test1 = Large::Set("aaa123", base, in_base);
	if (test1.toHex().compare("aaa123")!=0){
		cout << "Test_Hex1: " << test1.toString() << " " << test1.toHex() << endl;
	}
	//test2
	test1 = Large::Set("123dd123", base, in_base);
	if (test1.toHex().compare("123dd123")!=0){
		cout << "Test_Hex2: " << test1.toString() << " " << test1.toHex() << endl;
	}
	//test3
	test1 = Large::Set("eeeeee", base, in_base);
	if (test1.toHex().compare("eeeeee")!=0){
		cout << "Test_Hex3: " << test1.toString() << " " << test1.toHex() << endl;
	}
	//test4
	test1 = Large::Set("321123", base, in_base);
	if (test1.toHex().compare("321123")!=0){
		cout << "Test_Hex3: " << test1.toString() << " " << test1.toHex() << endl;
	}
	//test5
	test1 = Large::Set("123456123", base, in_base);
	if (test1.toHex().compare("123456123")!=0){
		cout << "Test_Hex4: " << test1.toString() << " " << test1.toHex() << endl;
	}
	//test6
	test1 = Large::Set("0555", base, in_base);
	if (test1.toHex().compare("555")!=0){
		cout << "Test_Hex5: " << test1.toString() << " " << test1.toHex() << endl;
	}
	//test7
	test1 = Large::Set("-321123", base, in_base);
	if (test1.toHex().compare("-321123")!=0){
		cout << "Test_Hex6: " << test1.toString() << " " << test1.toHex() << endl;
	}
	//test8
	test1 = Large::Set("-123456123", base, in_base);
	if (test1.toHex().compare("-123456123")!=0){
		cout << "Test_Hex7: " << test1.toString() << " " << test1.toHex() << endl;
	}
	//test9
	test1 = Large::Set("-0555", base, in_base);
	if (test1.toHex().compare("-555")!=0){
		cout << "Test_Hex8: " << test1.toString() << " " << test1.toHex() << endl;
	}
	//test10
	test1 = Large::Set("-abcdefa", base, in_base);
	if (test1.toHex().compare("-abcdefa")!=0){
		cout << "Test_Hex9: " << test1.toString() << " " << test1.toHex() << endl;
	}
	test1 = Large::Set("00000000003", base, in_base);
	if (test1.toHex().compare("3")!=0){
		cout << "Test_Hex10: " << test1.toString() << " " << test1.toHex() << endl;
	}
}

//testuj dodawanie a+b
void Tester::test_add(){
	//test1
	Large test1 = Large::Set("123", base, in_base);
	Large test2 = Large::Set("123456", base, in_base);
	if ((test1+test2) != Large::Set("123579", base, in_base)){
		cout << "Test_Add1: " << test1.toString() << " " << test2.toString() << endl;
	}
	//test2
	test1 = Large::Set("-1234", base, in_base);
	test2 = Large::Set("12345", base, in_base);
	if ((test1+test2) != Large::Set("11111", base, in_base)){
		cout << "Test_Add2: " << test1.toString() << " " << test2.toString() << endl;
	}
	//test3
	test1 = Large::Set("-1234", base, in_base);
	test2 = Large::Set("-223", base, in_base);
	if ((test1+test2) != Large::Set("-1457", base, in_base)){
		cout << "Test_Add3: " << test1.toString() << " " << test2.toString() << endl;
	}
	//test4
	test1 = Large::Set("1234", base, in_base);
	test2 = Large::Set("-2345", base, in_base);
	if ((test1+test2) != Large::Set("-1111", base, in_base)){
		cout << "Test_Add4: " << test1.toString() << " " << test2.toString() << endl;
	}
	//test5
	test1 = Large::Set("-400", base, in_base);
	test2 = Large::Set("300", base, in_base);
	if ((test1+test2) != Large::Set("-100", base, in_base)){
		cout << "Test_Add5: " << test1.toString() << " " << test2.toString() << endl;
	}
	//test6
	test1 = Large::Set("4000", base, in_base);
	test2 = Large::Set("3000", base, in_base);
	if ((test1+test2) != Large::Set("7000", base, in_base)){
		cout << "Test_Add6: " << test1.toString() << " " << test2.toString() << endl;
	}
	//test7
	test1 = Large::Set("abcd", base, in_base);
	test2 = Large::Set("dcba", base, in_base);
	if ((test1+test2) != Large::Set("18887", base, in_base)){
		cout << "Test_Add7: " << test1.toString() << " " << test2.toString() << endl;
	}
}
	
//testuj odejmowanie a-b
void Tester::test_substract(){
	//test1
	Large test1 = Large::Set("123456", base, in_base);
	Large test2 = Large::Set("12345", base, in_base);
	if ((test1-test2) != Large::Set("111111", base, in_base)){
		cout << "Test_Sub1: " << test1.toString() << " " << test2.toString() << endl;
	}
	//test2
	test1 = Large::Set("12340", base, in_base);
	test2 = Large::Set("12345", base, in_base);
	if ((test1-test2) != Large::Set("-5", base, in_base)){
		cout << "Test_Sub2: " << test1.toString() << " " << test2.toString() << endl;
	}
	//test3
	test1 = Large::Set("-1204", base, in_base);
	test2 = Large::Set("401", base, in_base);
	if ((test1-test2) != Large::Set("-1605", base, in_base)){
		cout << "Test_Sub3: " << test1.toString() << " " << test2.toString() << endl;
	}
	//test4
	test1 = Large::Set("2200", base, in_base);
	test2 = Large::Set("-101", base, in_base);
	if ((test1-test2) != Large::Set("2301", base, in_base)){
		cout << "Test_Sub4: " << test1.toString() << " " << test2.toString() << endl;
	}
	//test5
	test1 = Large::Set("-100", base, in_base);
	test2 = Large::Set("-201", base, in_base);
	if ((test1-test2) != Large::Set("101", base, in_base)){
		cout << "Test_Sub5: " << test1.toString() << " " << test2.toString() << endl;
	}
	//test6
	test1 = Large::Set("4500", base, in_base);
	test2 = Large::Set("1200", base, in_base);
	if ((test1-test2) != Large::Set("3300", base, in_base)){
		cout << "Test_Sub6: " << test1.toString() << " " << test2.toString() << endl;
	}
	//test7
	test1 = Large::Set("aa00", base, in_base);
	test2 = Large::Set("aabc", base, in_base);
	if ((test1-test2) != Large::Set("-bc", base, in_base)){
		cout << "Test_Sub7: " << test1.toString() << " " << test2.toString() << endl;
	}
	//test8
	test1 = Large::Set("2ad", base, in_base);
	test2 = Large::Set("29f", base, in_base);
	if ((test1-test2) != Large::Set("e", base, in_base)){
		cout << "Test_Sub8: " << test1.toString() << " " << test2.toString() << endl;
	}
	//test9
	test1 = Large::Set("0001233", base, in_base);
	test2 = Large::Set("567", base, in_base);
	if ((test1-test2) != Large::Set("ccc", base, in_base)){
		cout << "Test_Sub9: " << test1.toString() << " " << test2.toString() << endl;
	}
}
	
//test a*b
void Tester::test_multpily(){
	//test1
	Large test1 = Large::Set("123", base, in_base);
	Large test2 = Large::Set("123456", base, in_base);
	if ((test1*test2) != Large::Set("14b17dc2", base, in_base)){
		cout << "Test_Mul1: " << test1.toString() << " " << test2.toString() << endl;
	}
	//test2
	test1 = Large::Set("-123456", base, in_base);
	test2 = Large::Set("123456", base, in_base);
	if ((test1*test2) != Large::Set("-14b66cb0ce4", base, in_base)){
		cout << "Test_Mul2: " << test1.toString() << " " << test2.toString() << endl;
	}
	//test3
	test1 = Large::Set("456", base, in_base);
	test2 = Large::Set("-1456", base, in_base);
	if ((test1*test2) != Large::Set("-582ce4", base, in_base)){
		cout << "Test_Mul3: " << test1.toString() << " " << test2.toString() << endl;
	}
	//test4
	test1 = Large::Set("-321", base, in_base);
	test2 = Large::Set("-123", base, in_base);
	if ((test1*test2) != Large::Set("38e83", base, in_base)){
		cout << "Test_Mul4: " << test1.toString() << " " << test2.toString() << endl;
	}
	//test5
	test1 = Large::Set("2222", base, in_base);
	test2 = Large::Set("555", base, in_base);
	if ((test1*test2) != Large::Set("b5ff4a", base, in_base)){
		cout << "Test_Mul5: " << test1.toString() << " " << test2.toString() << endl;
	}
	//test6
	test1 = Large::Set("-135", base, in_base);
	test2 = Large::Set("531", base, in_base);
	if ((test1*test2) != Large::Set("-64425", base, in_base)){
		cout << "Test_Mul6: " << test1.toString() << " " << test2.toString() << endl;
	}
	//test7
	test1 = Large::Set("-000a000", base, in_base);
	test2 = Large::Set("-000a000", base, in_base);
	if ((test1*test2) != Large::Set("64000000", base, in_base)){
		cout << "Test_Mul7: " << test1.toString() << " " << test2.toString() << endl;
	}
	//test8
	test1 = Large::Set("0", base, in_base);
	test2 = Large::Set("111", base, in_base);
	if ((test1*test2) != Large::Set("0", base, in_base)){
		cout << "Test_Mul8: " << test1.toString() << " " << test2.toString() << endl;
	}
	//test9
	test1 = Large::Set("155436", base, in_base);
	test2 = Large::Set("0", base, in_base);
	if ((test1*test2) != Large::Set("0", base, in_base)){
		cout << "Test_Mul9: " << test1.toString() << " " << test2.toString() << endl;
	}
	//test10
	test1 = Large::Set("5", base, in_base);
	test2 = Large::Set("2ad", base, in_base);
	if ((test1*test2) != Large::Set("d61", base, in_base)){
		cout << "Test_Mul9: " << test1.toString() << " " << test2.toString() << endl;
	}
}

//testujemy dzielenie a/b - wartoœæ calkowita (nie reszta)
void Tester::test_divide(){
	//test0
	Large test1 = Large::Set("1004", 10, in_base);
	Large test2 = Large::Set("24c", 10, in_base);
	if ((test1/test2) != Large::Set("6", 10, in_base)){
		cout << "Test_Div0: " << test1.toString() << " " << test2.toString() << endl;
	}
	//test1
	test1 = Large::Set("123456", base, in_base);
	test2 = Large::Set("123", base, in_base);
	if ((test1/test2) != Large::Set("1003", base, in_base)){
		cout << "Test_Div1: " << test1.toString() << " " << test2.toString() << endl;
	}
	//test2
	test1 = Large::Set("123", base, in_base);
	test2 = Large::Set("123", base, in_base);
	if ((test1/test2) != Large::Set("1", base, in_base)){
		cout << "Test_Div2: " << test1.toString() << " " << test2.toString() << endl;
	}
	//test3
	test1 = Large::Set("-2213", base, in_base);
	test2 = Large::Set("120", base, in_base);
	Large left = test1/test2;
	Large right = Large::Set("-1e", base, in_base);
	if (left != right){
		cout << "Test_Div3: " << test1.toString() << " " << test2.toString() << endl;
	}
	//test4
	test1 = Large::Set("5555", base, in_base);
	test2 = Large::Set("-321", base, in_base);
	left = test1/test2;
	right = Large::Set("-1b", base, in_base);
	if (left != right){
		cout << "Test_Div4: " << test1.toString() << " " << test2.toString() << endl;
	}
	//test5
	test1 = Large::Set("-56789", base, in_base);
	test2 = Large::Set("-999", base, in_base);
	left = test1/test2;
	right = Large::Set("90", base, in_base);
	if (left != right){
		cout << "Test_Div5: " << test1.toString() << " " << test2.toString() << endl;
	}
	//test6
	test1 = Large::Set("04343", base, in_base);
	test2 = Large::Set("-012", base, in_base);
	left = test1/test2;
	right = Large::Set("-3bc", base, in_base);
	if (left != right){
		cout << "Test_Div6: " << test1.toString() << " " << test2.toString() << endl;
	}
	//test7
	test1 = Large::Set("61000", base, in_base);
	test2 = Large::Set("1000", base, in_base);
	left = test1/test2;
	right = Large::Set("61", base, in_base);
	if (left != right){
		cout << "Test_Div7: " << test1.toString() << " " << test2.toString() << endl;
	}
	//test8
	test1 = Large::Set("abcd", base, in_base);
	test2 = Large::Set("ab", base, in_base);
	left = test1/test2;
	right = Large::Set("101", base, in_base);
	if (left != right){
		cout << "Test_Div7: " << test1.toString() << " " << test2.toString() << endl;
	}
	//test9
	test1 = Large::Set("12341", base, in_base);
	test2 = Large::Set("1", base, in_base);
	left = test1/test2;
	right = Large::Set("12341", base, in_base);
	if (left != right){
		cout << "Test_Div9: " << test1.toString() << " " << test2.toString() << endl;
	}
	//test10
	test1 = Large::Set("123412", base, in_base);
	test2 = Large::Set("22", base, in_base);
	left = test1/test2;
	right = Large::Set("890f", base, in_base);
	if (left != right){
		cout << "Test_Div10: " << test1.toString() << " " << test2.toString() << endl;
	}
	//test11
	test1 = Large::Set("aaeebb", base, in_base);
	test2 = Large::Set("22", base, in_base);
	left = test1/test2;
	right = Large::Set("50705", base, in_base);
	if (left != right){
		cout << "Test_Div11: " << test1.toString() << " " << test2.toString() << endl;
	}
	//test12
	test1 = Large::Set("000bb000", base, in_base);
	test2 = Large::Set("-22", base, in_base);
	left = test1/test2;
	right = Large::Set("-5800", base, in_base);
	if (left != right){
		cout << "Test_Div12: " << test1.toString() << " " << test2.toString() << endl;
	}
	//test13
	test1 = Large::Set("127", base, in_base);
	test2 = Large::Set("113", base, in_base);
	left = test1/test2;
	right = Large::Set("1", base, in_base);
	if (left != right){
		cout << "Test_Div13: " << test1.toString() << " " << test2.toString() << endl;
	}
	//test14
	test1 = Large::Set("12d1117", base, in_base);
	test2 = Large::Set("4d", base, in_base);
	left = test1/test2;
	right = Large::Set("3e8f3", base, in_base);
	if (left != right){
		cout << "Test_Div14: " << test1.toString() << " " << test2.toString() << endl;
	}
	//test 15
	test1 = Large::Set("473358", base, in_base);
	test2 = Large::Set("4d", base, in_base);
	if ((test1/test2) != Large::Set("ecb8", base, in_base)){
		cout << "Test_Div15: " << test1.toString() << " " << test2.toString() << endl;
	}
	//test 16
	test1 = Large::Set("221", base, in_base);
	test2 = Large::Set("5", base, in_base);
	if ((test1/test2) != Large::Set("6d", base, in_base)){
		cout << "Test_Div16: " << test1.toString() << " " << test2.toString() << endl;
	}
}

//czy pierwszy element jest mniejszy od drugiego
void Tester::test_smaller(){
	//test1
	Large test1 = Large::Set("123", base, in_base);
	Large test2 = Large::Set("123456", base, in_base);
	if (!(test1<test2)){
		cout << "Test_Smaller1: " << test1.toString() << " " << test2.toString() << endl;
	}
	//test2
	test1 = Large::Set("-123555", base, in_base);
	test2 = Large::Set("123456", base, in_base);
	if (!(test1<test2)){
		cout << "Test_Smaller2: " << test1.toString() << " " << test2.toString() << endl;
	}
	//test3
	test1 = Large::Set("00000001", base, in_base);
	test2 = Large::Set("123456", base, in_base);
	if (!(test1<test2)){
		cout << "Test_Smaller3: " << test1.toString() << " " << test2.toString() << endl;
	}
	//test4
	test1 = Large::Set("-123456", base, in_base);
	test2 = Large::Set("123456", base, in_base);
	if (!(test1<test2)){
		cout << "Test_Smaller4: " << test1.toString() << " " << test2.toString() << endl;
	}
	//test5
	test1 = Large::Set("-1234", base, in_base);
	test2 = Large::Set("-1000", base, in_base);
	if (!(test1<test2)){
		cout << "Test_Smaller5: " << test1.toString() << " " << test2.toString() << endl;
	}
}

//czy pierwszy element jest wiêkszy od drugiego 
void Tester::test_bigger(){
	//test1
	Large test1 = Large::Set("123457", base, in_base);
	Large test2 = Large::Set("123456", base, in_base);
	if (!(test1>test2)){
		cout << "Test_Bigger1: " << test1.toString() << " " << test2.toString() << endl;
	}
	//test2
	test1 = Large::Set("12", base, in_base);
	test2 = Large::Set("10", base, in_base);
	if (!(test1>test2)){
		cout << "Test_Bigger2: " << test1.toString() << " " << test2.toString() << endl;
	}
	//test3
	test1 = Large::Set("011", base, in_base);
	test2 = Large::Set("1", base, in_base);
	if (!(test1>test2)){
		cout << "Test_Bigger3: " << test1.toString() << " " << test2.toString() << endl;
	}
	//test4
	test1 = Large::Set("11", base, in_base);
	test2 = Large::Set("-11", base, in_base);
	if (!(test1>test2)){
		cout << "Test_Bigger4: " << test1.toString() << " " << test2.toString() << endl;
	}
	//test5
	test1 = Large::Set("11", base, in_base);
	test2 = Large::Set("-22", base, in_base);
	if (!(test1>test2)){
		cout << "Test_Bigger5: " << test1.toString() << " " << test2.toString() << endl;
	}
}

void Tester::autotest_crt(int len){
	TesterRational tr = TesterRational();
	Large a;
	Large a_m;
	Large b;
	Large b_m;
	Large c;
	Large c_m;

	vector<Large> vect = vector<Large>();

	Large result(base);

	for(int i=0; i<TIMES; i++){
		a = Large::Set(tr.randomString(len/2), base, in_base);
		a_m = Large::Set(tr.randomString(len), base, in_base);

		b = Large::Set(tr.randomString(len/2), base, in_base);
		b_m = Large::Set(tr.randomString(len), base, in_base);
		while(!Large::coPrime(a_m, b_m)){
			b_m = Large::Set(tr.randomString(len), base, in_base);
		}
		c = Large::Set(tr.randomString(len/2), base, in_base);
		c_m = Large::Set(tr.randomString(len), base, in_base);
		while(!Large::coPrime(b_m, c_m) || !Large::coPrime(a_m, c_m)){
			c_m = Large::Set(tr.randomString(len), base, in_base);
		}
		
		vect.push_back(a);
		vect.push_back(a_m);
		vect.push_back(b);
		vect.push_back(b_m);
		vect.push_back(c);
		vect.push_back(c_m);

		result = Large::crt(vect);

		if(result.mod(a_m) != a){
			cout << "AutoTest CRT: Error przy a= " << a.toString() << " mod "
				<< a_m.toString() << " wynik " << result.toString() << endl;
		}

		if(result.mod(b_m) != b){
			cout << "AutoTest CRT: Error przy b= " << b.toString() << " mod " 
				<< b_m.toString() << " wynik " << result.toString() << endl;
		}

		if(result.mod(c_m) != c){
			cout << "AutoTest CRT: Error przy c= " << c.toString() << " mod " 
				<< c_m.toString() << " wynik " << result.toString() << endl;
			break;
		}

		cout << "." ;
	}
}

