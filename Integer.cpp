#include "Integer.h"
namespace CAS {

Integer::Integer(){
	sign   = false;
}
Integer::Integer(short){
	sign   = false;
}
Integer::Integer(unsigned short){
	sign   = false;
}
Integer::Integer(int){
}
Integer::Integer(unsigned int){
	sign   = false;
}
Integer::Integer(long){
}
Integer::Integer(unsigned long){
}
Integer::Integer(long long){
}
Integer::Integer(unsigned long long){
	sign   = false;
}
Integer::Integer(float){

}
Integer::Integer(double){

}
Integer::Integer(std::string){

}

/****

****/

Integer::Integer(const Natural&){
	sign   = false;
}
Integer::Integer(const Integer&){
}

/****

****/

//Natural Integer::getNumber() const{
//}
fbyte Integer::getNumberAt(unsigned int) const{
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

Integer Integer::leftShift(unsigned int)const{
	return Integer(0);
}
Integer Integer::rightShift(unsigned int)const{
	return Integer(0);
}
Integer Integer::msb(unsigned int)const{
	return Integer(0);
}
Integer Integer::lsb(unsigned int)const{
	return Integer(0);
}

/****

****/

Integer Integer::addition(const Integer&, bool){
	return Integer(0);
}
Integer Integer::subtraction(const Integer&, bool){
	return Integer(0);
}
Integer Integer::multiplication(const Integer&, bool){
	return Integer(0);
}
Integer Integer::division(const Integer&, bool){
	return Integer(0);
}
Integer Integer::remainder(const Integer&, bool){
	return Integer(0);
}

/****

****/

Integer Integer::karatsuba(const Integer&){
	return Integer(0);
}
Integer Integer::toom33(const Integer&){
	return Integer(0);
}
Integer Integer::toom44(const Integer&){
	return Integer(0);
}
Integer Integer::FFT(const Integer&){
	return Integer(0);
}

/****

****/

Integer Integer::operator+(const Integer&){
	return Integer(0);
}
Integer Integer::operator-(const Integer&){
	return Integer(0);
}
Integer Integer::operator*(const Integer&){
	return Integer(0);
}
Integer Integer::operator/(const Integer&){
	return Integer(0);
}
Integer Integer::operator%(const Integer&){
	return Integer(0);
}

/****

****/
/*
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
*/
}



















