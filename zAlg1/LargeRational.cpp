#include "stdafx.h"

#include "Large.h"
#include "LargeRational.h"

#include <vector>


string LargeRational::toHex(){
	stringstream ss;

	if(licznik.isNegative()){
		ss << '-';
	}

	ss << licznik.toHex();
	ss << "-";
	ss << mianownik.toHex();

	ss << "(";
	ss <<  licznik.getBase();
	ss <<  ")";

	return ss.str();
}

/*
	Metoda dodaje 2 liczby wymierne, 
	 ignorujemy kwestie znaku, 
	 zak³adamy ¿e argumenty dodawania maj¹ tak¹ sam¹ podstawê
*/
LargeRational LargeRational::add(LargeRational second){
	//zmienne pomocnicze
	Large zero = Large::Set("0", licznik.getBase());
	Large one = Large::Set("1", licznik.getBase());

	if(licznik == zero){
		return LargeRational(second);
	}
	if(second.licznik == zero){
		return LargeRational(*this);
	}

	Large d = LargeRational::GCD(this->mianownik, second.mianownik);
	if(d == one){
		LargeRational res = LargeRational(licznik*second.mianownik + mianownik*second.licznik, mianownik*second.mianownik);
		return res;
	}else{
		Large t1 = licznik * (second.mianownik/d);
		t1 = t1 + second.licznik * (mianownik/d);
		Large t2 = mianownik * (second.mianownik/d); 

		if(t1 == zero){
			return LargeRational(Large::Set("0",licznik.getBase(), 10));
		}else{
			Large e = LargeRational::GCD(t1, d); 
			LargeRational res = LargeRational(t1/e, t2/e);
			return res;
		}
	}
}

/**
	Dzielenie dwóch ulamków na zasadzie mno¿enia z liczb¹ odwrotn¹ 
*/
LargeRational LargeRational::divide(LargeRational arg2){
	LargeRational lr = LargeRational(licznik*arg2.mianownik, mianownik*arg2.licznik);
	//TODO: powinno byæ jeszcze poprawione korzystaj¹c z GCD
	return lr;
}		

/*
	Typowe (szkolne) odejmowanie u³amków
	Nie interesuje nas kwestia znaku.
	Zak³adamy, ¿e liczby s¹ tej samej podstawy.
	This jest wiêksze ni¿ arg.
*/
LargeRational LargeRational::substract(LargeRational arg){
	LargeRational res = LargeRational(licznik*arg.mianownik - arg.licznik*mianownik, mianownik*arg.mianownik); 
	return res;
}

/*
	Mno¿ymy dwie dlugie liczby rzeczywiste.
	Zak³adamy, ¿e s¹ tej samej podstawy.
	Ignorujemy kwestie znaku
*/
LargeRational LargeRational::mul(LargeRational second){
	fix();
	second.fix();

	Large zero = Large::Set("0", licznik.getBase(), 10);
	Large one = Large::Set("1", licznik.getBase(), 10);
	LargeRational res = LargeRational(zero, one);

	if(*this == zero || second == zero){
		return res;
	}

	Large d1 = LargeRational::GCD(licznik, second.mianownik);
	Large d2 = LargeRational::GCD(second.licznik, mianownik);
	if(d1 == one){
		res.licznik = licznik;
		res.mianownik = second.mianownik; 
	}else{
		res.licznik = (licznik/d1);
		res.mianownik = (second.mianownik/d1); 
	}
	if(d2 == one){
		res.licznik = (res.licznik * second.licznik);
		res.mianownik = (mianownik * res.mianownik);
	}else{
		res.licznik = (second.licznik/d2) * res.licznik;
		Large test = (mianownik/d2);
		res.mianownik = (mianownik/d2) * res.mianownik;
	}
	res.fix();
	return res;
}

LargeRational LargeRational::simpleMul(LargeRational second){
	fix();
	second.fix();
	LargeRational lr = LargeRational(licznik*second.licznik, mianownik*second.mianownik);
	lr.fix();
	Large gcd = LargeRational::GCD(lr.licznik, lr.mianownik);
	lr.licznik = lr.licznik/gcd;
	lr.mianownik = lr.mianownik/gcd;
	lr.fix();
	return lr;
}

void LargeRational::fix(){
	licznik.fix();
	mianownik.fix();
}