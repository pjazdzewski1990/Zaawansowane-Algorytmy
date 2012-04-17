#include "stdafx.h"

#include "Large.h"
#include <vector>

using namespace std;

//TODO: to powinno by� statyczne, ale no c�: C++
//na potrzeby profilowania
long multiplication_count;
long addition_count;

// dzielimy "this" przez "second"
// w rest zapisujemy reszt�
Large Large::divide(Large v, Large& rest){
	Large u = Large(lista, base);
	u.setNegative(false);

	//przypadki bazowe
	//przypadek u<v
	if(this->compareAbsolute(v) == 1){
		rest = Large(u);
		return Large::Set("0", base);
	}
	//pojedyncze liczby
	if(u.lista.size() == 1 && v.lista.size() == 1){
		if(rest.lista.size() == 1){
			rest.lista[0] = u.lista[0]%v.lista[0];
		}else{
			rest.lista.push_back(u.lista[0]%v.lista[0]);
		}
		Large l(base);
		l.lista.push_back(u.lista[0]/v.lista[0]);
		return l;
	}
	//r�wne liczby
	if(u==v){
		rest = Large::Set("0", base, 16);
		Large res = Large(base);
		res.setNegative(false);
		res.lista.push_back(1);
		return res;
	}
	
	//Algorytm z zaj��
	//nie chcemy dzieli� przez zero
	v.fix();

	//poprawka algorytmu
	long d = base / (v.lista[0]+1);
	u = u * d;
	v = v * d;

	//dodaj zero na pocz�tku u je�li d=1
	//if(d==1){
		u.lista.insert(u.lista.begin(), 0);
	//}

	//zgodnie z algorytmem z zaj��
	Large q(base);
	q.setNegative(false);

	long j = u.lista.size() - v.lista.size();
	long i=0;

	while(j >= i){
		//przerwij je�li U jest ju� mniejsze od V
		if(u.compareAbsolute(v) == 1){
			//ew. musimy jeszcze doda� brakuj�ce zera na koniec 
			while(j > i){
				q.lista.push_back(0);
				i++;
			}
			break;
		}

		//TODO: zak�adamy, �e mo�na wykona� "standardowe" dzielenie
		long num =0;
		if(u.lista.size()>(unsigned)i){
			num = u.lista[i]*base;
		}
		if(u.lista.size()>(unsigned)i+1){
			num += u.lista[i+1];
		}

		long _q = num / v.lista[0];
		//bo na raz mo�emy wstawi� tylko jedn� cyfr�
		if(_q > base){
			_q = _q/base;
		}
		long _r = num % v.lista[0];

		if(v.lista.size()>1 && u.lista.size()>(unsigned)i+2 && _q*v.lista[1] > base*_r+u.lista[i+2]){
			_q--;
			_r = _r + v.lista[0];
			if(_q*u.lista[1] > base*_r+u.lista[i+1]){
				_q--;
			}
		}

		//TODO: kwestia znaku
		Large temp = v*_q;
		//temp.setNegative(false);
		
		//przesu� kilka razy potem mozna ju� odejmowa�
		temp = temp<<(j-i-1);
		temp.setNegative(false);
		u = u-temp;

		//dzielimy przez baz�
		q.lista.push_back(_q);

		if(u.isNegative()){
			q.lista[q.lista.size()-1]--;
			u = u + v;
		}
		i++;
	}
	//by otrzyma� poprawn� reszt� trzeba jeszcze podzieli� przez d
	Large dd = Large(base);
	dd.lista.push_back(d);
	dd.fix();
	Large tmp(base);
	rest = u.divide(dd, tmp);
	rest.fix();

	q.fix();
	return q;
}

//popraw liczb�:
// A|zmniejsz liczby w kom�rkach by pasowa�y do bazy
// B|obetnij 0 na pocz�tku
void Large::fix(){
	//A|
	removeZero();

	//B|
	checkBase();
}

/*
	Usuwa z liczby zera znajduj�ce si� na pocz�tkowych pozycjach
*/
void Large::removeZero(){
	for(unsigned i=0; i<lista.size();i++){
		if(lista[i]==0 && lista.size()>1){
			lista.erase(lista.begin());
			i--;
		}else{
			break;
		}
	}
}

void Large::checkBase(){
	long carry = 0;
	for(int i=lista.size()-1; i>=0; i--){
		lista[i]+=carry;
		if(lista[i]>=base){
			carry = lista[i] / base;
			lista[i] = lista[i] % base;
		}
	}
	while(carry!=0){
		lista.insert(lista.begin(), carry%base);
		carry = carry/base;
	}
}

long Large::getBase(){
	return base;
}

long Large::lastNum(){
	long result = lista[lista.size()-1];
	return result;
}