#ifndef _LARGE_TEST_h_included_
#define _LARGE_TEST_h_included_

#include "LargeRational.h"
#include "Large.h"

using namespace std;

class Tester{
	private:
		long base;
		long in_base;

	public:
		Tester(){
			base = 100;
			in_base = 16;
		}
		
		//uruchom seri� test�w
		void run();

		//funkcje testuj�ce Large
		// 1 funkcja testuje 1 operacj� na r�nych przypadkach
		void test_add();
		void test_substract();
		void test_multpily();
		void test_divide();
		void test_smaller();
		void test_bigger();
		void test_hex();
		void test_rest();

};

#endif