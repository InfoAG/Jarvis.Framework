#include "Integer.h"

namespace CAS {

Integer::Integer(){
	nat = 0;
	sign = false;
}
Integer::Integer(short s){
	if(s < 0){
		s    *= -1;
		sign  =  true;
	}else
		sign = false;
	nat = s;
}
Integer::Integer(unsigned short us){
	sign = false;
	nat = us;
}
Integer::Integer(int i){
	if(i < 0){
		i   *= -1;
		sign = true;
	}else
		sign = false;
	nat = i;
}
Integer::Integer(unsigned int ui){
	sign = false;
	nat  = ui;
}
Integer::Integer(long l){
	if(l < 0){
		l   *= -1;
		sign = true;
	}else
		sign = false;
	nat = l;
}
Integer::Integer(unsigned long ul){
	sign = false;
	nat = ul;
}
Integer::Integer(long long ll){
	if(ll < 0){
		ll   *= -1;
		sign = true;
	}else
		sign = false;
	nat = ll;
}
Integer::Integer(unsigned long long ull){
	sign = false;
	nat = ull;
}
Integer::Integer(float){

}
Integer::Integer(double){

}
Integer::Integer(std::string str){
	if(str.at(0)=='-'){
		sign = true;
		nat  = str.substr(1);
	}else{
		sign = false;
		nat  = str;
	}
}

Integer::Integer(const Natural& rhs){
	nat  = rhs;
	sign = false;
}
Integer::Integer(const Integer& rhs){
	nat = rhs.getNat();

}
/****

****/
Natural Integer::getNat()const{
	return nat;
}
fbyte Integer::getNumberAt(unsigned int ui)const{
	return nat.getDigitsAt(ui);
}
fbyte Integer::getSize()const{
	return nat.getSize();
}
std::string Integer::toString()const{
	std::string str;
	if(sign)
		str.push_back('-');
	return str + nat.toString();
}

/****

****/
bool Integer::isInteger(){
	return true;
}
bool Integer::isEven(){
	return nat.isEven();
}
bool Integer::isOdd(){
	return nat.isOdd();
}
bool Integer::isPrime(){
	return true;
}

/****

****/
const Integer Integer::operator+(const Natural& rhs)const{
	Integer result;
	if(sign){
		if(nat <= rhs){
			result.nat  = rhs - nat;
			result.sign = false;
		}else{
			result.nat  = nat - rhs;
			result.sign = true;
		}
		return result;
	}else{
		result.sign = false;
		result.nat  = rhs + nat;
	}
	return result;
}
const Integer Integer::operator-(const Natural& rhs)const{
	Integer result;
	if(sign){
		result.nat  = nat + rhs;
		result.sign = sign;
	}else{
		if(nat < rhs){ 
			result.nat  = rhs - nat;
			result.sign = true;
		}else{
			result.nat  = nat - rhs;
			result.sign = false;
		}
	}
	return result;
}
const Integer Integer::operator*(const Natural& rhs)const{
	Integer result;
	result.nat  = nat * rhs;
	result.sign = sign;
	return result;
}
const Integer Integer::operator/(const Natural& rhs)const{
	Integer result;
	result.nat  = nat / rhs;
	result.sign = sign;
	return result;
}
const Integer Integer::operator%(const Natural& rhs)const{
	return Integer(0);
}
Integer& Integer::operator=(const Natural& rhs){
	Integer result;
	result.sign = false;
	result.nat  = rhs;
	return  result;
}
Integer& Integer::operator+=(const Natural& rhs){
	*this = *this + rhs;
	return *this;
}
Integer& Integer::operator-=(const Natural& rhs){
	*this = *this - rhs;
	return *this;
}
Integer& Integer::operator*=(const Natural& rhs){
	*this = *this * rhs;
	return *this;
}
Integer& Integer::operator/=(const Natural& rhs){
	*this = *this / rhs;
	return *this;
}

/****
****/
const Integer Integer::operator+(const Integer& rhs)const{
	Integer result;
	if(sign == rhs.sign){
		result.sign = sign;
		result.nat  = nat + rhs.nat;
	}else if(sign){ 
		if(nat <= rhs.nat){
			result.nat  = rhs.nat - nat;
			result.sign = false;
		}else{ 
			result.nat  = nat - rhs.nat;
			result.sign = true;
		}
	}else{
		if(nat < rhs.nat){
			result.nat  = rhs.nat - nat;
			result.sign = true;
		}else{
			result.nat  = nat - rhs.nat;
			result.sign = false;
		}
	}
	return result;
}
const Integer Integer::operator-(const Integer& rhs)const{
	Integer result;
	if(sign == rhs.sign){
		if(nat < rhs.nat){ 
			result.nat  = rhs.nat - nat;
			result.sign = true;
		}else{ 
			result.nat  = nat - rhs.nat;
			result.sign = false;
		}		
	}else if(sign){
		result.nat  = nat + rhs.nat;
		result.sign = true;
	}else{
		result.nat  = nat + rhs.nat ;
		result.sign = false;
	}
	return result;
}
const Integer Integer::operator*(const Integer& rhs)const{
	Integer result;
	result.nat  = nat * rhs.nat;
	result.sign = sign ^ rhs.sign;
	return result;
}
const Integer Integer::operator/(const Integer& rhs)const{
	Integer result;
	result.nat  = nat / rhs.nat;
	result.sign = sign ^ rhs.sign;
	return result;
}
const Integer Integer::operator%(const Integer& rhs)const{
	return Integer(0);
}
Integer& Integer::operator=(const Integer& rhs){
	nat  = rhs.nat;
	sign = rhs.sign;
	return *this;
}
Integer& Integer::operator+=(const Integer& rhs){
	*this = *this + rhs;
	return *this;
}
Integer& Integer::operator-=(const Integer& rhs){
	*this = *this - rhs;
	return *this;
}
Integer& Integer::operator*=(const Integer& rhs){
	*this = *this * rhs;
	return *this;
}
Integer& Integer::operator/=(const Integer& rhs){
	*this = *this / rhs;
	return *this;
}
/****

****/
const Integer Integer::operator+(const int& ui)const{
	return *this + Integer(ui);
}
const Integer Integer::operator-(const int& ui)const{
	return *this - Integer(ui);
}
const Integer Integer::operator*(const int& ui)const{
	return *this * Integer(ui);
}
const Integer Integer::operator/(const int& ui)const{
	return *this / Integer(ui);
}
const Integer Integer::operator%(const int& ui)const{
	return *this % Integer(ui);
}
Integer& Integer::operator=(const int& ui){
	nat  = -1*ui;
	sign = (ui<0);
	return *this;
}
Integer& Integer::operator+=(const int& ui){
	return Integer(0);
}
Integer& Integer::operator-=(const int& ui){
	return Integer(0);
}
Integer& Integer::operator*=(const int& ui){
	return Integer(0);
}
Integer& Integer::operator/=(const int& ui){
	return Integer(0);
}
/****


****/
bool Integer::operator<(const Integer& rhs){
	if(sign != rhs.sign){
		if(sign)
			return false;
		else 
			return true;
	}
	if(nat < rhs.nat)
		return true;
	else 
		return false;
}
bool Integer::operator<=(const Integer& rhs){
	if(sign != rhs.sign){
		if(sign)
			return false;
		else
			return true;
	}
	if(nat <= rhs.nat)
		return true;
	else 
		return false;
}
bool Integer::operator==(const Integer& rhs){
	if(sign != rhs.sign)
		return false;
	if(nat == rhs.nat)
		return true;
	return false;
}
bool Integer::operator>=(const Integer& rhs){
	if(sign != rhs.sign){
		if(sign)
			return true;
		else
			return false;
	}
	if(nat >= rhs.nat)
		return true;
	else 
		return false;
}
bool Integer::operator>(const Integer& rhs){
	if(sign != rhs.sign){
		if(sign)
			return true;
		else
			return false;
	}
	if(nat > rhs.nat)
		return true;
	else 
		return false;
}

}


















