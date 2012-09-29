#include "Rational.h"

namespace CAS{

Rational::Rational(){
	numerator   = 0;
	denominator = 1;
	sign = false;
}
Rational::Rational(short s){

}
Rational::Rational(unsigned short us){

}
Rational::Rational(int i){

}
Rational::Rational(unsigned int ui){

}
Rational::Rational(long l){

}
Rational::Rational(unsigned long ul){

}
Rational::Rational(long long ll){

}
Rational::Rational(unsigned long long ull){

}
Rational::Rational(float f){

}
Rational::Rational(double d){

}
Rational::Rational(std::string str){

}

Rational::Rational(const Natural& rhs){

}
Rational::Rational(const Integer& rhs){

}
Rational::Rational(const Rational& rhs){

}

Natural Rational::getNumerator()const{

}
Natural Rational::getDenominator()const{

}
bool Rational::getSign()const{

}
std::string Rational::toString()const{

}

bool Rational::isInteger(){

}
bool Rational::isEven(){

}
bool Rational::isOdd(){

}
bool Rational::isPrime(){

}

const Rational Rational::operator+(const Natural& rhs)const{

}
const Rational Rational::operator-(const Natural& rhs)const{

}
const Rational Rational::operator*(const Natural& rhs)const{

}
const Rational Rational::operator/(const Natural& rhs)const{

}
const Rational Rational::operator%(const Natural& rhs)const{

}
Rational& Rational::operator=(const Natural& rhs){

}
Rational& Rational::operator+=(const Natural& rhs){

}
Rational& Rational::operator-=(const Natural& rhs){

}
Rational& Rational::operator*=(const Natural& rhs){

}
Rational& Rational::operator/=(const Natural& rhs){

} 
const Rational Rational::operator+(const Integer& rhs)const{

}
const Rational Rational::operator-(const Integer& rhs)const{

}
const Rational Rational::operator*(const Integer& rhs)const{

}
const Rational Rational::operator/(const Integer& rhs)const{

}
const Rational Rational::operator%(const Integer& rhs)const{

}
Rational& Rational::operator=(const Integer& rhs){

}
Rational& Rational::operator+=(const Integer& rhs){

}
Rational& Rational::operator-=(const Integer& rhs){

}
Rational& Rational::operator*=(const Integer& rhs){

}
Rational& Rational::operator/=(const Integer& rhs){

}
const Rational Rational::operator+(const Rational& rhs)const{

}
const Rational Rational::operator-(const Rational& rhs)const{

}
const Rational Rational::operator*(const Rational& rhs)const{

}
const Rational Rational::operator/(const Rational& rhs)const{

}
const Rational Rational::operator%(const Rational& rhs)const{

}
Rational& Rational::operator=(const Rational& rhs){

}
Rational& Rational::operator+=(const Rational& rhs){

}
Rational& Rational::operator-=(const Rational& rhs){

}
Rational& Rational::operator*=(const Rational& rhs){

}
Rational& Rational::operator/=(const Rational& rhs){

}
bool Rational::operator<(const Rational&)const{

}
bool Rational::operator<=(const Rational& rhs)const{

}
bool Rational::operator==(const Rational& rhs)const{

}
bool Rational::operator!=(const Rational& rhs)const{

}
bool Rational::operator>=(const Rational& rhs)const{

}
bool Rational::operator>(const Rational& rhs)const{

}

};