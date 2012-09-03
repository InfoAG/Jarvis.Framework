#include "Integer.h"
namespace CAS {

Integer::Integer(){
	sign   = false;
}
Integer::Integer(short s){
	sign   = false;
}
Integer::Integer(unsigned short us){
	sign   = false;
}
Integer::Integer(int i){
}
Integer::Integer(unsigned int ui){
	sign   = false;
}
Integer::Integer(long l){
}
Integer::Integer(unsigned long ul){
}
Integer::Integer(long long ll){
}
Integer::Integer(unsigned long long ull){
	sign   = false;
}
Integer::Integer(float f){

}
Integer::Integer(double d){

}
Integer::Integer(std::string str){

}

/****

****/

Integer::Integer(const Natural& nat){
	sign   = false;
}
Integer::Integer(const Integer& rhs){
}

/****

****/

//Natural Integer::getNumber() const{
//}
fbyte Integer::getNumberAt(unsigned int ui) const{
	return 0;
}
fbyte Integer::getSize() const{
	return 0;
}
bool Integer::getSign()const{
	return sign;
}
std::string Integer::toString(){
	std::string str;
	return str;
}

/****

****/

bool Integer::isInteger(){
	return true;
}
bool Integer::isEven(){
	return this->isOdd();
}
bool Integer::isOdd(){
	return digits.at(0)%2;
}
bool Integer::isPrime(){
	return false;
}

/****

****/

Integer Integer::leftShift(unsigned int ui)const{
	return Integer(0);
}
Integer Integer::rightShift(unsigned int ui)const{
	return Integer(0);
}
Integer Integer::msb(unsigned int ui)const{
	return Integer(0);
}
Integer Integer::lsb(unsigned int ui)const{
	return Integer(0);
}

/****

****/

Integer Integer::addition(const Integer& rhs, bool b){
	return Integer(0);
}
Integer Integer::subtraction(const Integer& rhs, bool b){
	return Integer(0);
}
Integer Integer::multiplication(const Integer& rhs, bool b){
	return Integer(0);
}
Integer Integer::division(const Integer& rhs, bool b){
	return Integer(0);
}
Integer Integer::remainder(const Integer& rhs, bool b){
	return Integer(0);
}

/****

****/

Integer Integer::karatsuba(const Integer& rhs){
	return Integer(0);
}
Integer Integer::toom33(const Integer& rhs){
	return Integer(0);
}
Integer Integer::toom44(const Integer& rhs){
	return Integer(0);
}
Integer Integer::FFT(const Integer& rhs){
	return Integer(0);
}

/****

****/

Integer Integer::operator+(const Integer& rhs){
	return Integer(0);
}
Integer Integer::operator-(const Integer& rhs){
	return Integer(0);
}
Integer Integer::operator*(const Integer& rhs){
	return Integer(0);
}
Integer Integer::operator/(const Integer& rhs){
	return Integer(0);
}
Integer Integer::operator%(const Integer&rhs){
	return Integer(0);
}

/****

****/

bool Integer::operator<(const Integer& rhs){
	if(sign!=rhs.getSign()){
		return sign;
	}
}
bool Integer::operator<=(const Integer& rhs){
	return !((*this)>rhs);
}
bool Integer::operator==(const Integer& rhs){
	if(sign!=rhs.getSign())
		return false;
}
bool Integer:: operator>=(const Integer& rhs){
	return !((*this)<rhs);
}
bool Integer::operator>(const Integer& rhs){
	if(sign!=rhs.getSign()){
		return rhs.getSign();
	}
}

}



















