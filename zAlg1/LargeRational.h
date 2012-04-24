#ifndef _LARGERATIONAL_h_included_
#define _LARGERATIONAL_h_included_

#include "Large.h"
#include <stdio.h>
#include <stdlib.h>

/*
	Klasa do obs³ugi du¿ych liczb wymiernych
*/
class LargeRational {
	private:
		Large licznik;
		Large mianownik;

	public:
		//KONSTRUKTORY
		LargeRational(Large _licznik){
			licznik = _licznik;
			mianownik = Large::Set("1",_licznik.getBase(),10);
		}
		LargeRational(Large _licznik, Large _mianownik){
			licznik = _licznik;
			mianownik = _mianownik;
		}
		LargeRational(const LargeRational& wzor){
			licznik = wzor.licznik;
			mianownik = wzor.mianownik;
		}

		string toString(){
			stringstream ss;

			if(licznik.isNegative()){
				ss << '-';
			}

			ss << licznik.toString();
			ss << "_";
			ss << mianownik.toString();

			ss << "(";
			ss <<  licznik.getBase();
			ss <<  ")";

			return ss.str();
		}
		string toHex();

		//metody fabrykuj¹ce
		static LargeRational Set(long base, Large licznik, Large mianownik){
			Large _licznik = Large::convert(licznik, base);
			Large _mianownik = Large::convert(mianownik, base);
			LargeRational res(_licznik, _mianownik);
			return res;
		}
		static LargeRational Set(string num, int base, int in_base=10){
			int pos = num.find("_");
			string licznik = "0";
			if(pos != 0){
				licznik = num.substr(0, pos);
			}
			string mianownik = "1";
			if(pos != -1 && pos != (signed)num.length()-1){
				mianownik = num.substr(pos+1);
			}
			LargeRational res(Large::Set(licznik, base, in_base), Large::Set(mianownik, base, in_base));
			return res;
		}

		LargeRational add(LargeRational second);
		LargeRational mul(LargeRational second);
		LargeRational simpleMul(LargeRational second);

		/**
			Metoda zwraca najwiêkszy wspólny dzielnik dwoch du¿ych liczb
			Wynik GCD jest zawsze dodatni
		*/
		static Large GCD(Large first, Large second){
			Large s = Large::Set("1", first.getBase(), 10); 
			Large t = Large::Set("0", first.getBase(), 10); 
			Large d = Large(first);

			Large v1 = Large::Set("0", first.getBase(), 10); 
			Large v2 = Large::Set("1", first.getBase(), 10); 
			Large v3 = Large(second);

			Large zero = Large::Set("0", first.getBase(), 10);
			while(!(v3.compare(zero)==0)){
				//zmienna pomocnicza
				d.fix();
				v3.fix();
				Large helper = d/v3;

				//krok 1
				Large test = (helper * v1);
				test.fix();
				Large t1 = s - test;
				Large t2 = t - (helper * v2);
				test = (v3 * helper);
				Large t3 = d - test;

				//krok2
				s = v1;
				t = v2;
				d = v3;

				//krok3
				v1 = t1;
				v2 = t2;
				v3 = t3;
			}
			d.setNegative(false);
			return d;
		}

		/**
			GCD dla wielu liczb
			sposób pierwszy
		*/
		static Large GCD(Large numbers[], long size){
			Large result = numbers[0];

			for(int i=1; i<size; i++){
				result = LargeRational::GCD(result,numbers[i]);
			}

			result.fix();
			return result;
		}
		
		/**
			GCD dla wielu liczb
			sposób drugi
		*/
		static Large GCD(vector<Large> numbers){
			Large min = numbers[0];
			long base = min.getBase();
			Large zero = Large::Set("0", base, 16);

			do{
				min = numbers[0];
				for(int i=0; i<(int)numbers.size(); i++){
					if(min > numbers[i]){
						min = numbers[i];
					}
				}
				
				for(int i=0; i<(int)numbers.size(); i++){
					Large rest(base);
					numbers[i].divide(min , rest);
					if(rest.compareAbsolute(zero) != 0){
						numbers[i] = rest;
					}else{
						numbers.erase(numbers.begin()+i);
						i=-1;
					}
				}

				numbers.push_back(min);
			}while(numbers.size()>1);
			
			min.fix();
			return min;
		}

		/**
			Algorytm Steina wyznaczania GCD
		*/
		static Large Steiner(Large u, Large v){
			Large two = Large::Set("2", u.getBase(), 10); 
			two.setNegative(false);
			Large zero = Large::Set("0", u.getBase(), 10);
			zero.setNegative(false);

			//przesuniêcie
			long k = 0;
			//pierwszy przypadek
			while(u.lastNum()%2==0 &&  v.lastNum()%2==0){
				u = u / two;
				v = v /two;
				k++;
			}

			Large t ;
			if(u.lastNum()%2!=0){
				t = v;
			}else{
				t = u;
			}

			//drugi przypadek
			while(u.lastNum()%2 == 0) {
				u = u / two;
			}
 
			/* trzeci przypadek */
			do {

				while(v.lastNum()%2 == 0){  /* Loop X */
					v = v / two;
				}
				//zamiana
				if (u > v) {
					Large t = v; 
					v = u; 
					u = t;
				}  
				v = v - u;        // odejmowanie
			} while (v.compareAbsolute(zero) != 0);

			//uwzglêdnij przesuniêcie
			Large w = u;
			for(int i=0; i<k; i++){
				w = w*two;
			}
			return w;
		}

		/**
			Algorytm Euklidesa wyznaczania GCD
		*/
		static Large Euclid(Large a, Large b){
		  Large a0 = a;
		  Large b0 = b;

		  Large zero = Large::Set("0", a.getBase());

		  Large p = Large::Set("1", a.getBase());
		  Large q = Large::Set("0", a.getBase());
		  Large r = Large::Set("0", a.getBase());
		  Large s = Large::Set("1", a.getBase());


		  while(b.compareAbsolute(zero)!=0) {
			Large c;
			a.divide(b, c);
			Large quot = a/b;
			a = b;
			b = c;
			Large new_r = p - (quot * r);
			Large new_s = q - (quot * s);
			p = r;
			q = s;
			r = new_r;
			s = new_s;
		  }
			//Wówczas NWD(a0, b0) = p*a0 + q*b0
			return p*a0 + q*b0;
		}

		/**
			Algorytm Lehmara wyznaczania GCD
		*/
		static Large Lehmar2(Large u, Large v, long part){
			//pozbywamy siê poprzedzaj¹cych zer
			u.fix();
			v.fix();

			// KROK L1
			L1:
			//jeœli liczby s¹ krótkie to mo¿emy poprostu obliczy GCD
			if(u.length()<=part || v.length()<=part){
				return LargeRational::GCD(u, v);
			}

			Large one = Large::Set("1", u.getBase());
			one.setNegative(false);
			Large zero = Large::Set("0", u.getBase());
			one.setNegative(false);

			//staramy sie ¿eby u>=v
			if(v>u){
				Large temp = v;
				v = u;
				u = temp;
			}

			//GCD nie moze byæ wiêksze ni¿ mniejsza z liczb,
			// wiêc mo¿na podzieliæ wiêksz¹ przez mniejsz¹
			//u jest wiêksze 
			//po tej operacji w u mamy resztê z u/v
			u.divide(v,u);
			//ew. zamiana
			if(v>u){
				Large temp = v;
				v = u;
				u = temp;
			}

			//przygotuj wartoœci
			Large u$ = Large(u.copy(part), u.getBase()); 
			Large v$ = Large(v.copy(part), v.getBase());
			
			//cout << u.toString() << "->" << u$.toString() << endl;
			//cout << v.toString() << "->" << v$.toString() << endl;

			Large A = one;
			Large B = zero;
			Large C = zero;
			Large D = one;

			Large u_ = u$ + B; 
			Large v_ = u$ + D;
			Large u__ = u$ + A; 
			Large v__ = u$ + C;

			// KROK L2
			Large mianownik = (v$+C);
			if(!(mianownik.compareAbsolute(zero)==0)){
				Large q = (u$+A)/mianownik;
				mianownik = (v$+D);
				while(!(mianownik.compareAbsolute(zero)==0) && q == ((u$+B)/mianownik)){
					// KROK L3
					Large T = A - q*C;
					A = C;
					C = T;
					T = B - q*D;
					B = D;
					D = T;
					T = u$ - q*v$;
					u$ = v$;
					v$ = T;
				}
			}
			// KROK L4
			Large t;
			Large w;
			if(!(v.compareAbsolute(zero) == 0)){
				if(B.compareAbsolute(zero) == 0){ 
					u.divide(v, t);
					u = v;
					v = t;
				}else{
					t = A*u;
					t = t + B*v;
					w = C*u;
					w = w + D*v;
					u = t;
					v = w;
				}
			}
			goto L1;
		}
		/**
			Dzielenie dwóch ulamków na zasadzie mno¿enia z liczb¹ odwrotn¹ 
		*/
		LargeRational divide(LargeRational arg2);

		/*
			Typowe (szkolne) odejmowanie u³amków
		*/
		LargeRational substract(LargeRational arg);

		/*
		Fix dla rzeczywistej
		*/
		void fix();

		//OPERATORY
		bool operator==(long val){
			//obie liczby musz¹ byæ znormalizowane
			//pamiêtamy, ¿e nie mo¿na porównywaæ Large i long
			char buffer [sizeof(long)*8+1];
			//_ltoa_s (val,buffer,10);
			sprintf (buffer, "%ld", val);
			string str = string(buffer);
			Large l = Large::Set(str, licznik.getBase(), 10); 
			
			Large zero = Large::Set("0", licznik.getBase(), 16);
			Large rest = Large(licznik.getBase());

			Large wynik = licznik.divide(mianownik, rest);

			return (licznik/mianownik)==l && rest==zero;
		}
		
		bool operator==(LargeRational second){
			//obie liczby musz¹ byæ znormalizowane
			return ( (licznik==second.licznik) && (mianownik==second.mianownik) ) || 
				( (licznik==second.licznik) && (licznik==Large::Set("0", licznik.getBase(), 10)) );
		}

		LargeRational operator*(Large l){
			LargeRational lr(*this);
			lr.licznik = lr.licznik * l;
			return lr;
		}

		LargeRational operator*(LargeRational l){
			LargeRational lr = LargeRational(mul(l));
			if(licznik.isNegative() != l.licznik.isNegative()){
				lr.licznik.setNegative(true);
				lr.mianownik.setNegative(false);
			}else{
				lr.licznik.setNegative(false);
				lr.mianownik.setNegative(false);
			}
			return lr;
		}
		LargeRational operator+(LargeRational second){
			LargeRational lr = this->add(second);

			//algorytm podany na zajeciach nie zawsze zwraca poprawna wartoœæ
			// patrz test numer 5
			// potrzebna jest jeszcze rêczna korekta
			Large gcd = LargeRational::GCD(lr.licznik, lr.mianownik);			
			Large zero = Large::Set("0", lr.licznik.getBase()); 
			if(!(gcd == zero)){
				lr.licznik = lr.licznik/gcd;
				lr.mianownik = lr.mianownik/gcd;
			}
			
			return lr;
		}


};

#endif