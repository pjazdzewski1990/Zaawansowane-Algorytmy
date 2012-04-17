#ifndef _LARGE_h_included_
#define _LARGE_h_included_

#include <iostream>
#include <string>
#include <list>
#include <vector>
#include <sstream>
#include <deque>
#include <map>
#include <math.h>

using namespace std;

extern long multiplication_count;
extern long addition_count;

class Large
{
	private:
		//lista przechowuj¹ca kolejne cyfry liczby 
		// zapisanej w systemie o bazie base
		// liczby "od lewej"(ma³e indeksy) maj¹ najwiêksz¹ potêgê
		vector<long> lista;

		//wewnêtrzna podstawa systemu
		long base;

		//czy liczba jest ujemna 
		bool negative;

		static int charToLong(char c){
			return c-48;
		}

		//mapa zawieraj¹ca przejœcia z litery(char) w long
		// np. '1'->1 , 'a'->10, 'Z'->coœ..
		// chyba nie ma potrzeby definiowaæ dalej ni¿ do Z
		// konieczne przy systemach o podstawach wiêkszych ni¿ 10
		map<char,int> dict;

		//uzupe³nij s³ownik dict wartoœciami
		void prepareDictVals(){
			int num =0;
			//0-1
			for(int i='0';i<='9';i++){
				dict[i] = num;
				num++;
			}
			//litery a-z 
			// wartoœci 10-36
			for(int i='a';i<='z'; i++){
				dict[i] = num;
				num++;
			}
			//litery a-z 
			// wartoœci 10-36
			for(int i='A';i<='Z'; i++){
				dict[i] = num;
				num++;
			}
		}

		vector<long> copyUpper(Large& large){
			vector<long> ret;
			
			//uzupelnij liczbe large zerami od lewej
			// a¿ d³ugoœæ liczby bêdzie poteg¹ 2 
			//fillToPower(large);

			for(unsigned i=0; i<large.lista.size()/2; i++){
				ret.push_back(large.lista[i]);
			}

			return ret;
		}

		vector<long> copyLower(Large& large){
			vector<long> ret;
			
			//uzupelnij liczbe large zerami od lewej
			// a¿ d³ugoœæ liczby bêdzie poteg¹ 2 
			fillToPower(large);

			for(unsigned i=large.lista.size()/2; i<large.lista.size(); i++){
				ret.push_back(large.lista[i]);
			}

			return ret;
		}

		//TODO: nie uzywana
		bool isPowerOf2(long l){
			while(true){
				if(l%2 != 0){
					if(l != 1){
						return false;
					}else{
						return true;
					}
				}else{
					l = l/2;
				}
			}
		}

		//TODO: czy da siê to zrobiæ lepiej?
		//TODO: chyba ju¿ nie potrzebne
		void fillToPower(Large& large){
			while(!isPowerOf2(large.lista.size()) ){
				large.lista.insert(large.lista.begin(), 0);
				//large.lista.push_front(0);
			}
		}

		void fillWithZeros(Large& l1, Large& l2){
			while(l1.lista.size() != l2.lista.size()){
				if(l1.lista.size() < l2.lista.size()){
					l1.lista.insert(l1.lista.begin(), 0);
					//l1.lista.push_front(0);
				}else{
					l2.lista.insert(l2.lista.begin(), 0);
					//l2.lista.push_front(0);
				}
			}

			if(l1.lista.size() % 2 == 1){
				l1.lista.insert(l1.lista.begin(), 0);
				//l1.lista.push_front(0);
				l2.lista.insert(l2.lista.begin(), 0);
				//l2.lista.push_front(0);
			}
			return; 
		}
	
		/*
			W³aœciwa procedura dodawania liczby A do liczby B
			Z tym ¿e A jak i B mog¹ byæ ujemne lub dodatnie
		*/
		Large operate(Large second){
			///A jest wiêksze-równe B 
			if(compareAbsolute(second) <= 0){
				//A jest ujemne
				if(this->isNegative()){
					//B jest ujemne
					if(second.isNegative()){
						///1| (-10) + (-4) = -(10+4)
						Large res = this->simpleAdd(second);
						res.setNegative(true);
						return res;
					}else{//B jest dodatnie
						///2| (-10) + 4 = -(10-4)
						Large res = this->simpleSubtract(second);
						res.setNegative(true);
						return res;
					}
				}else{//A jest dodatnie
					if(second.isNegative()){//B jest ujemne
						//3|10 + (-4) = 10 - 4
						Large res = this->simpleSubtract(second);
						res.setNegative(false);
						return res;
					}else{//B jest dodatnie
						//4| 10 + 4 
						Large res = this->simpleAdd(second);
						return res;
					}
				}
			}else{
			//A jest mniejsze od B	
				if(this->isNegative()){//A jest ujemne
					if(second.isNegative()){//B jest ujemne
						///5| (-4) + (-10) = -(4+10)
						switchSign();
						second.switchSign();
						Large res = this->simpleAdd(second);
						res.setNegative(true);
						return res;
					}else{//B jest dodatnie
						///6| (-4) + 10 = 10-4
						Large res = second.simpleSubtract(*this);
						return res;
					}
				}else{//A jest dodatnie
					if(second.isNegative()){//B jest ujemne
						//7| 4 + (-10) = -(10-4)
						Large res = second.simpleSubtract(*this);
						res.setNegative(true);
						return res;
					}else{
						//8| 4 + 10
						Large res = this->simpleAdd(second);
						return res;
					}
				}
			}
		}

	public:
		//defaultowy konstruktor na potrzeby LargeRational
		Large(){
			Large(16);
		}

		Large(long _base): base(_base) {	
			//uzupe³nij wartoœæ s³ownika, jeœli jest on pusty
			if(dict.size() == 0){
				prepareDictVals();
			}
		}

		//TODO: drugi argument jest bez sensu
		Large(vector<long> numbers, long _base): base(_base) {	
			//uzupe³nij wartoœæ s³ownika, jeœli jest on pusty
			if(dict.size() == 0){
				prepareDictVals();
			}

			//stwórz liczbê na podstawie wartoœci przekazanych
			for(unsigned i=0; i<numbers.size(); i++){
				lista.push_back(numbers[i]);
			}
		}

		/*
			Metoda implementuj¹ca proste odejmowanie, tj.
			zak³adamy, ¿e liczby maj¹ t¹ sam¹ bazê 
			i this jest wiêksze ni¿ second
		*/
		Large simpleSubtract(Large second){

			//na potrzeby profilera
			addition_count++;
			Large res(base);
			
			long left;
			long right;
			long result;
			short borrow = 0;

			int indexA = lista.size()-1;
			int indexB = second.lista.size()-1;

			int max = indexA;
			if(max < indexB){
				max = indexB;
			}

			while(max >= 0){
				//ustaw pierwsza wartoœæ
				if(indexA >= 0){
					left = lista[indexA];
				}else{
					left = 0;
				}
				//ustaw drug¹ wartoœæ
				if(indexB >= 0){
					right = second.lista[indexB];
				}else{
					right = 0;
				}
				//jeœli mamy przeniesienie to odejmij od pierwszej liczby
				if(borrow >= 1){
					left--;
					borrow=0;
				}
				//odejmij 2 liczby
				if(left < right){
					//jeœli lewa jest mniejsza to rób magiê
					borrow++;
					result = (base - right) + left;
				}else{
					result = left - right;
				}

				//dorzuæ cyfrê do wyniku
				res.lista.insert(res.lista.begin(), result);
				//res.lista.push_front(result);
				indexA--;
				indexB--;
				max--;
			}

			//res.fix();
			res.setNegative(false);
			return res;
		}
		
		//metoda tworzy obiekt klasy string z czyteln¹ reprezentacj¹ liczby
		string toString(){
			stringstream ss;

			if(isNegative()){
				ss << '-';
			}

			for(long i=0; i < (long)lista.size(); i++){
				ss << lista[i];
				ss << ",";
			}
			ss << "(";
			ss <<  base;
			ss <<  ")";

			return ss.str();
		}

		//zamieñ liczbê przkazan¹ jako obiekt string
		// i zapisan¹ w systemie o podstawie in_base (domyslnie 10)
		static Large Set(string num, int base, int in_base=10){
			//TODO: in_base moze byæ wiêksza ni¿ docelowa - ERROR
			Large result(base);
			bool neg = false;

			long power = 0;	//ile razy trzeba pomno¿yæ przez 10
			for(long i=num.length()-1; i >= 0; i--){

				//jeœli ten znak to minus
				if(num[i]=='-'){
					neg = true;
					break;
				}

				int a = result.dict[num[i]];	//wspó³czynnik na pozycji "i"
												//brany ze s³ownika, bo mo¿e byæ liter¹
				
				Large partial(base);			//czêsciowy wynik
				partial.lista.push_back(a);		//pocz¹tkowa wartoœæ
				partial.setNegative(false);
				for(int i=0; i<power; i++){
					partial = partial * in_base;//zwiêksz in_base-krotnie
				}

				result = result.simpleAdd(partial);		//zwiêksz ostateczny wynik

				power++;
			}

			result.setNegative(neg);
			return result;
		}

		//zamieñ bazê podanej liczby "l" na "new_base"
		static Large convert(Large l, long new_base){

			//TODO: wykonaj sprawdzenie czy:
			// this.base = new_base^x, wtedy ka¿d¹ pozycje w "this" zamianiamy na x cyfr w nowej liczbie
			// jeœli this.base = new_base^-x, wtedy ka¿de x pozycji w "this" bêdzie 1 now¹ pozycja w wyniku 

			Large result(new_base);
			long power = 0;									//ile razy trzeba pomno¿yæ przez baze
			for(long i=l.lista.size()-1; i >= 0; i--){
				long a = l.lista[i];						//wspó³czynnik na pozycji "i"
				
				Large partial(new_base);					//czêœciowy wynik
				while(a >= new_base){
					partial.lista.insert(partial.lista.begin(), a%new_base);//pocz¹tkowa wartoœæ
					//partial.lista.push_front(a%new_base);	
					a = a/new_base;
				}
				partial.lista.insert(partial.lista.begin() ,a);
				//partial.lista.push_front(a);

				for(int j=0; j<power; j++){
					partial = partial * l.base;				//zwiêksz ?-krotnie
				}

				result = result.simpleAdd(partial);			//zwiêksz ostateczny wynik

				power++;
			}

			//TODO:obejœciue
			/*long test = result.lista[0];
			if(test >= new_base){
				result.lista.insert(result.lista.begin(), test/new_base);
				//result.lista.push_front(test/new_base);
				result.lista[1] = test%new_base;
			}*/
			result.fix();

			result.setNegative(l.isNegative());
			return result;
		}

		Large operator*(Large second){
			Large res = Karatsuba(second);
			if(isNegative() != second.isNegative()){
				res.setNegative(true);
				return res;
			}else{
				res.setNegative(false);
				return res;
			}
		}

		Large operator*(int val){

			//na potrzeby profilera
			multiplication_count++;

			Large res(base);

			long carry = 0;
			long sum = 0;
			for(int i = lista.size()-1; i>=0; i--){ 
				sum = lista[i]*val;
				sum += carry;
				//long c = carry;	//przechowaj wartoœæ przeniesienia
				carry = 0;		//nalicz nowe przeniesienie

				//mieœci siê w przedziale
				if(sum < base){
					//ustaw i-t¹ cyfrê na sum 
					res.lista.insert(res.lista.begin(), sum);
					//res.lista.push_front(sum);
				}
				//jest wiêksza ni¿ podstawa systemu
				if(sum>=base){
					//ustaw i-t¹ cyfrê na sum/base
					res.lista.insert(res.lista.begin(), sum%base);
					//res.lista.push_front(sum%base);
					carry = sum/base;
				}
				//dosz³o do przepe³nienia
				if(sum < 0){
					//po kroczku do przepe³nienia
					for(int jj=0;jj<val;jj++){
						for(int kk=0; kk<lista[i]; kk++){
							//res.lista[i]++;
							//zwiêksz o 1
							if(res.lista.size() <= (unsigned)i){
								res.lista.insert(res.lista.begin(), 1);
								//res.lista.push_front(1);
							}else{
								res.lista[i]++;
							}
							//dosz³o do przepe³nienia
							if(res.lista[i]<0 || res.lista[i]>=base){
								carry++;
								//res.lista[i] = 0;
								//ustaw obecn¹ cyfrê na 0
								//TODO: czy if ma sens? zbadaæ czy sam push wystarczy
								if(res.lista.size() <=  (unsigned)i){
									res.lista.insert(res.lista.begin(), 0);
									//res.lista.push_front(0);
								}else{
									res.lista[i] = 0;
								}
							}
						}
					}
				}
			}

			//jeœli mamy przeniesienie to dodaj
			if(carry > 0){
				res.lista.insert(res.lista.begin(), carry);
				//res.lista.push_front(carry);
			}

			res.setNegative(this->negative);

			return res;
		}

		//na razie zak³adamy, ¿e maj¹ tak¹ sam¹ podstawê
		//i ¿e s¹ tegosamego znaku
		Large simpleAdd(Large val){

			//na potrzeby profilera
			addition_count++;

			Large res(base);

			long carry = 0;
			long sum = 0;
			long size = lista.size();
			if(val.lista.size() >  (unsigned)size){
				size = val.lista.size();
			}

			for(long i = 0; i<size; i++){ 
				//pobierz wartoœæ i-ta od prawej z liczby this
				long left;
				long index = lista.size();
				index--;
				index = index - i;
				if(index >= 0){
					left = lista[index];
				}else{
					left = 0;
				}
				
				//pobierz wartoœæ i-t¹ od prawej z liczby val
				long right;
				index = val.lista.size();
				index--;
				index = index - i;
				if(index >= 0){
					right = val.lista[index];
				}else{
					right = 0;
				}

				sum = left + right;	//dodaj wartoœci cz¹stkowe
				sum += carry;
				//long c = carry;		//przechowaj wartoœæ przeniesienia
				carry = 0;			//nalicz nowe przeniesienie

				//mieœci siê w przedziale
				if(sum < base){
					//w razie potrzeby rozszerz tablicê
					//ustaw i-t¹ cyfrê na sum
					res.lista.insert(res.lista.begin(), sum);
					//res.lista.push_front(sum);
				}
				//jest wiêksza ni¿ podstawa systemu
				if(sum>=base){
					//ustaw i-t¹ cyfrê na sum/base
					res.lista.insert(res.lista.begin(), sum%base);
					//res.lista.push_front(sum%base);
					carry = sum/base;
				}

				//TODO: inny sposób na wykrycie przepe³nienia
				//dosz³o do przepe³nienia
				if(sum < 0){
					//po kroczku do przepe³nienia
					for(int jj=0;jj<right;jj++){
						res.lista[i]++;
						//dosz³o do przepe³nienia
						if(res.lista[i]<0 || res.lista[i]>=base){
							carry++;
							res.lista[i] = 0;
						}
					}
				}
			}

			//jeœli mamy przeniesienie to dodaj
			if(carry > 0){
				res.lista.insert(res.lista.begin(), carry);
				//res.lista.push_front(carry);
			}

			//res.fix();
			res.setNegative(this->negative);
			return res;
		}

		/*
			Metoda porównuj¹ca dwie liczby typu Large
			Metoda zwraca:
			-1	jeœli liczba na której rzecz jest wykonywane compare jest wiêksza
			0	gdy liczby s¹ równe
			1	gdy liczba second jest wiêksza
		*/
		int compare(Large second){
			//obie liczby s¹ ró¿nego znaku
			Large l1 = Large(*this);
			l1.fix();
			Large l2 = Large(second);
			l2.fix();

			if(l1.isNegative() != l2.isNegative()){
				if(l1.isNegative()){
					return 1;
				}else{
					return -1;
				}
			}else{
				int result = l1.compareAbsolute(l2);
				if(l1.isNegative()){
					result *=-1;
				}
				return result;
			}
		}

		/*
			Metoda porównuj¹ca wartoœæ bezwglêdn¹ dwóch liczb typu Large
			Metoda zwraca:
			-1	jeœli liczba na której rzecz jest wykonywane compare jest wiêksza
			0	gdy liczby s¹ równe
			1	gdy liczba second jest wiêksza
		*/
		int compareAbsolute(Large second){
			//zacznij od porównania d³ugoœci
			Large l1 = Large(*this);
			Large l2 = Large(second);
			l1.fix();
			l2.fix();
			if(l1.lista.size() != l2.lista.size()){
				if(l1.lista.size() > l2.lista.size()){
					return -1;
				}else{
					return 1;
				}
			}else{
				//przechodzimy po kolei i porównujemy elementy
				int i = 0;
				int size = l1.lista.size();
				//dopóki mamy jeszcze nie sprawdzone pozycje
				while(i < size){
					//ten obiekt jest wiêkszy na pozycji i
					if(l1.lista[i] > l2.lista[i]){
						return -1;
					} 
					//obiekt second jest wiêkszy na pozycji i
					if(l1.lista[i] < l2.lista[i]){
						return 1;
					} 

					//jeœli dotarliœmy tutaj to znaczy ¿e na pozycjach <i obiekty s¹ identyczne
					i++;
				}

				//jeœli porównywanie kolejnych cyfr nie przynios³o skutku to obiekty s¹ równe
				return 0;
			}
		}

		/*
		Algorytm mno¿enia Karatsuby
		zak³adamy, ¿e liczby s¹ tej samej bazy
		*/
		Large Karatsuba(Large second){

			//mno¿enie coœ*0(0) i 0(0)*coœ 
			Large zero = Large::Set("0", this->getBase(), 10);
			if(this->compareAbsolute(zero)==0 || second.compareAbsolute(zero)==0 || this->lista.size()==0 || second.lista.size()==0){
				return zero;
			}

			if(lista.size()!=second.lista.size() && lista.size()!=1 && second.lista.size()!=1){
				//uzupelnij liczbe large zerami od lewej
				// a¿ d³ugoœæ liczby bêdzie poteg¹ 2 
				fillWithZeros(*this, second);
			}

			//przypadek bazowy d³ugoœæ liczby = 1
			if(lista.size()<=1 || second.lista.size()<=1){
				//po prostu mno¿ymy 2 liczby
				Large product = Large(base);
				if(lista.size() <= 1){
					if(lista.size()==0){
						return second;
					}else{
						product = second * lista[0];
						return product;
					}
				}
				
				if(second.lista.size() <= 1){
					if(second.lista.size() == 0){
						return *this;
					}else{
						product = *this * second.lista[0]; 
						return product;
					}
				}
				return product;
			}else{
				//przechowa tymczasowe wartoœci
				Large temp(base);
				
				//oblicz X
				//stwórz obiekt large na podstawie danych z listy(deque)
				Large X(copyUpper(*this), base);
				//do temp przypisz czêœæ drugiej liczby
				temp = Large(copyUpper(second), base);
				//mnó¿ (rekursywnie)
				X = X.Karatsuba(temp);

				//oblicz Y
				Large Y = Large(copyLower(*this), base);
				temp = Large(copyLower(second), base);
				Y = Y.Karatsuba(temp);
			
				//oblicz A
				Large A = Large(copyUpper(*this), base).simpleAdd( Large(copyLower(*this), base) );

				//oblicz B
				Large B = Large(copyUpper(second), base).simpleAdd( Large(copyLower(second), base) );

				//oblicz Z
				Large Z = A.Karatsuba(B);
				Z = Z.simpleSubtract(X);
				Z = Z.simpleSubtract(Y);

				//wynik = X*10^2n + Z*10^n + Y
				int m;
				if(lista.size()%2==1){
					m = (lista.size()+1)/2;
				}else{
					m = lista.size()/2;
				}

				Large wynik = X << (2*m);
				wynik = wynik.simpleAdd(Z << m);
				wynik = wynik.simpleAdd(Y);

				wynik.setNegative(false);
				return wynik;
			}
		}

		/*
			Algorytm mno¿enia "w s³upku",
			algorytm nie uwzglêdnia znaku i 
			zak³ada, ¿e oba systemy maj¹ t¹ sam¹ podstawê   
		*/
		Large ColumnMultplication(Large second){
			Large res = Large(base);
			//ka¿da cyfra z "second"
			for(int i=second.lista.size()-1, potega=0; i>=0 ; i--, potega++){
				//oblicz wynik cz¹stkowy
				Large part = Large(*this);
				part = part * second.lista[i];
				//podnieœ do odpowiedniej potêgi
				for(int j=0; j<potega; j++){
					part = part * base;
				}
				//dodaj do ostatecznego wyniku
				res = res.simpleAdd(part);
			}
			return res;
		}

		string toHex(){
			stringstream ss;
			
			if(isNegative()){
				ss << '-';
			}

			Large l = Large(base);
			//konwertuj na hex'y
			if(base != 16){
				l = Large::convert(*this, 16);
			}else{
				l = *this;
			}
			for(unsigned i=0; i<l.lista.size(); i++){
				switch(l.lista[i]){
				case 0:
				case 1:
				case 2:
				case 3:
				case 4:
				case 5:
				case 6:
				case 7:
				case 8:
				case 9: 
					ss << l.lista[i];
					break;
				case 10:
					ss << 'a';
					break;
				case 11:
					ss << 'b';
					break;
				case 12:
					ss << 'c';
					break;
				case 13:
					ss << 'd';
					break;
				case 14:
					ss << 'e';
					break;
				case 15:
					ss << 'f';
					break;
				}
			}
			return ss.str();
		}

		static char comparisonToChar(Large arg0, Large arg1){
			if(arg0 < arg1){
				return '<';
			}
			if(arg0 > arg1){
				return '>';
			}
			return '=';
		}

		Large divide(Large second, Large& rest);

		void fix();

		void removeZero();

		void checkBase();

		long getBase();

		long lastNum();

		//OPERATORY
		inline bool operator<(Large l) {
			return (compare(l) == 1);
		}

		inline bool operator<=(Large l) {
			return compare(l) >= 0;
		}

		inline bool operator>(Large l) {
			return compare(l) == -1;
		}

		inline bool operator>=(Large l) {
			return compare(l) <= 0;
		}

		inline bool operator==(Large l) {
			return compare(l) == 0;
		}

		inline bool operator!=(Large l) {
			return compare(l) != 0;
		}

		inline Large operator<<(long l){
			Large res = Large(this->lista, base);
			//przesuñ w lewo
			for(int i=0; i<l; i++){
				res.lista.push_back(0);
			}
			return res;
		}

		inline bool isNegative(){
			return negative;
		}

		inline void setNegative(bool val){
			negative = val;
		} 

		inline bool switchSign(){
			negative = !negative;
			return negative;
		}

		//uproœæ by miêdzy this a second by³ tylko jeden operator: +
		// (tj. druga liczba ma byæ dowolna, byle by realizowaæ operacjê dodawania)
		// i potem przekazuj dalej
		inline Large operator-(Large second){
			//1| this - (-second)  = this + second
			//2| this - second  = this + (-second)
			second.switchSign();
			//przeka¿ do w³aœciwej procedury licz¹cej
			return this->operate(second);
		}

		inline Large operator+(Large second){
			return this->operate(second); 
		}

		inline Large operator/(Large second){
			Large rest(base);
			Large res = this->divide(second, rest); 
			if(this->isNegative() != second.isNegative()){
				res.setNegative(true);
			}else{
				res.setNegative(false);
			}
			return res;
		}
};

#endif