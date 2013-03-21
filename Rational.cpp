 #include "Rational.h"

namespace CAS{

Rational::Rational(){
	numerator   = 0;
	denominator = 1;
	sign = false;
}

Rational::Rational(short s){
	denominator = 1;
	sign = s < 0 ? true : false;
	if(!sign){
		numerator = s;	
	}
	else{
		numerator = (unsigned short)(s*-1);
	}
}

Rational::Rational(unsigned short us){
	numerator = us;
	denominator = 1;
	sign = false;
}

Rational::Rational(int i){
	sign = i < 0 ? true : false;
	denominator = 1;
	if(!sign){
		numerator = i;	
	}
	else{
		numerator = (unsigned int)(i*-1);
	}
}

Rational::Rational(unsigned int ui){
	numerator = ui;
	denominator = 1;
	sign = false;
}

Rational::Rational(long l){
	denominator = 1;
	sign = l < 0 ? true : false;
	if(!sign){
		numerator = l;	
	}
	else{
		numerator = (unsigned long)(l*-1);
	}
}

Rational::Rational(unsigned long ul){
	numerator = ul;
	denominator = 1;
	sign = false;
}

Rational::Rational(long long ll){
	denominator = 1;
	sign = ll < 0 ? true : false;
	if(!sign){
		numerator = ll;	
	}
	else{
		numerator = (unsigned int)(ll*-1);
	}
}

Rational::Rational(unsigned long long ull){
	numerator = ull;
	denominator = 1;
	sign = false;
}

Rational::Rational(int n, int d){
	denominator = d;
	if(n < 0){
		numerator = (n*-1);
		if(d < 0){
			denominator = (d*-1);
			sign = false;
		}
		else{
			denominator = d;
			sign = true;
		}
	}else{
		numerator = n;
		if(d < 0){
			denominator = (d*-1);
			sign = true;
		}
		else{
			denominator = d;
			sign = false;
		}
	}
}

Rational::Rational(float f){

}

Rational::Rational(double d){

}

Rational::Rational(std::string str){

}


Rational::Rational(const Natural& rhs){
	numerator = rhs;
	denominator = 1;
	sign = false;
}

Rational::Rational(const Natural& n, const Natural& d){
	sign = false;
	numerator = n;
	denominator = d;
}

Rational::Rational(const Integer& rhs){
	numerator = rhs.getNat();
	denominator = 1;
	sign = rhs.getSign();

}

Rational::Rational(const Natural& n, const Integer& d){
	sign = d.getSign();
	numerator = n;
	denominator = d.getNat();
}

Rational::Rational(const Integer& n, const Natural& d){
	sign = n.getSign();
	numerator = n.getNat();
	denominator = d;
}

Rational::Rational(const Integer& n, const Integer& d){
	sign = n.getSign() == d.getSign() ? false : true;
	numerator = n.getNat();
	denominator = d.getNat();
}

Rational::Rational(const Rational& rhs){
	numerator = rhs.numerator;
	denominator = rhs.denominator;
	sign = rhs.sign;
}

Natural Rational::getNumerator()const{
	return numerator;
}

Natural Rational::getDenominator()const{
	return denominator;
}

bool Rational::getSign()const{
	return sign;
}

NUM_TYPE Rational::getType()const{
	return NUM_RAT;
}

std::string Rational::toString(int precision)const{
	Natural tmp = numerator/denominator;
	Rational t;
	if(sign){
		t = *this + tmp;
	}
	else{
		t = *this - tmp;
	}
	std::string result = (sign ? "-" + tmp.toString() : tmp.toString());
	if(t != 0){
		result += ".";
	}
	precision = (precision / 9)+1;
	if(t.numerator != 0){
		t.numerator = t.numerator.LeftShift(precision);
		result += (t.numerator/t.denominator).toString();
	}
	return result;
}

std::string Rational::fracToString()const{
	std::string number;
	if(sign){
		number+="-";
	}
	number += numerator.toString();
	if(denominator != 1){
		number += "/"+denominator.toString();
	}
	return number;
}

std::string Rational::fracToString2()const{
	if(numerator == 0)
		return "0";
	Natural tmp = numerator/denominator; 
	std::string result;
	if(sign){
		result += "-";
	}
	if(tmp != 0){
		result += tmp.toString();
	}
	Rational tmp2;
	if(sign){
		tmp2 = *this + tmp;
	}
	else{
		tmp2 = *this - tmp;
	}
	if(tmp2.numerator != 0){
		if(result != ""){
			result += " + ";
		}
		result += tmp2.numerator.toString() + "/" + tmp2.denominator.toString();
	}
	return result;
}

bool Rational::isInteger(){
	Natural gcd = Natural::GCD(numerator,denominator);
	numerator = numerator / gcd;
	denominator = denominator / gcd;
	if(denominator == 1){
		return true;
	}
	return false;
}

bool Rational::isEven(){
	if(!isInteger()){
		return false;
	}
	if(numerator.isEven()){
		return true;
	}
	return false;
}

bool Rational::isOdd(){
	return !isEven();
}

bool Rational::isPrime(){ // to come
	return true;
}

Rational Rational::round(const Rational& r, ROUND_MODE mode){
	Rational result = r.numerator/r.denominator;
	if(result != 0){
		result.sign = r.sign;
	}
	if(mode == ROUND_DOWN){
		if(r.sign && (result - r) != 0){
			return result-Rational(1);
		}
		return result;
	}else if(mode == ROUND_UP){
		if((result - r) != 0 && !r.sign){
			return result+Rational(1);
		}
		return result;
	}else if(mode == ROUND_TOWARD_ZERO){
		return result;
	}else if(mode == ROUND_AWAY_FROM_ZERO){
		if((result-r) != 0){
			if(r.sign){
				return result-Rational(1);
			}else{
				return result+Rational(1);
			}
		}
		return result;
	}else{ //ROUND_TO_NEAREST
		if( (result - r) < Rational(1,2)){
			return result;
		}
		if(r.sign){
			return result-Rational(1);		
		}else{
			return result+Rational(1);
		}
	}
}


const Rational Rational::operator+(const Natural& rhs)const{
	Rational result;
	Natural tmp = denominator*rhs;
	if(!sign){
		result.numerator = numerator+tmp;
		result.sign = false;
	}else{
		if(numerator > tmp){
			result.numerator = numerator-tmp;
			result.sign = true;
		}else{
			result.numerator = tmp - numerator;
			result.sign = false;
		}
	}
	if(numerator != 0)
		result.denominator = denominator;
	else
		result.denominator = 1;

	return result;
}

const Rational Rational::operator-(const Natural& rhs)const{
	Rational result;
	Natural tmp = denominator * rhs;
	if(sign){
		result.numerator = numerator + tmp;
		result.sign = true;
	}else{
		if(numerator >= tmp){
			result.numerator = numerator-tmp;
			result.sign = false;
		}else{
			result.numerator = tmp - numerator;
			result.sign = true;
		}
	}
	if(numerator != 0)
		result.denominator = denominator;
	else
		result.denominator = 1;

	return result;
}

const Rational Rational::operator*(const Natural& rhs)const{
	Rational result;
	result.numerator = numerator * rhs;
	result.denominator = denominator;
	result.sign = sign;
	return result;
}

const Rational Rational::operator/(const Natural& rhs)const{
	Rational result;
	result.numerator = numerator;
	result.denominator = denominator * rhs;
	result.sign = sign;
	return result;
}

const Rational Rational::operator%(const Natural& rhs)const{ 
	return *this - round(*this/rhs,ROUND_DOWN)*rhs;
}

Rational& Rational::operator=(const Natural& rhs){
	numerator = rhs;
	denominator = 1;
	sign = false;
	return (*this);
}

Rational& Rational::operator+=(const Natural& rhs){
	return *this = *this + rhs;
}

Rational& Rational::operator-=(const Natural& rhs){
	return *this = *this - rhs;
}

Rational& Rational::operator*=(const Natural& rhs){
	return *this = *this * rhs;
}

Rational& Rational::operator/=(const Natural& rhs){
	return *this = *this / rhs;
} 

const Rational Rational::operator+(const Integer& rhs)const{
	Rational result;
	Natural tmp = rhs.getNat()*denominator;
	result.denominator = denominator;
	if(sign == rhs.getSign()){
		result.numerator = numerator + tmp;
		result.sign = sign;
	}else{
		if(sign){
			if(tmp > numerator){
				result.numerator = tmp - numerator;
				result.sign = false;	
			}else if(numerator > tmp){
				result.numerator = numerator - tmp;
				result.sign = true;
			}else{
				result.numerator = 0;
				result.sign = false;
			}
		}else{
			if(tmp > numerator){
				result.sign = true;
				result.numerator = tmp - numerator;
			}else if(numerator > tmp){
				result.sign = false;
				result.numerator = numerator - tmp;
			}else{
				result.numerator = 0;
				result.sign = false;
			}
		}
	}
	return result;
}

const Rational Rational::operator-(const Integer& rhs)const{
	Rational result;
	Natural tmp = rhs.getNat()*denominator;
	result.denominator = denominator;
	if(sign != rhs.getSign()){
		result.numerator = numerator + tmp;
		result.sign = sign;
	}else{
		if(numerator < tmp){
			result.numerator = tmp - numerator;
			if(sign){
				result.sign = false;
			}else{
				result.sign = true;
			}
		}else if(numerator > tmp){
			result.numerator = numerator - tmp;
			if(sign){
				result.sign = true;
			}else{
				result.sign = false;
			}
		}else{
			result.numerator = 0;
			result.sign = false;
		}

	}
	return result;
}

const Rational Rational::operator*(const Integer& rhs)const{
	Rational result;
	result.sign = rhs.getSign() == sign ? false : true;
	result.numerator = numerator * rhs.getNat();
	result.denominator = denominator;
	return result;
}

const Rational Rational::operator/(const Integer& rhs)const{
	Rational result;
	result.sign = rhs.getSign() == sign ? false : true;
	result.numerator = numerator;
	result.denominator = denominator * rhs.getNat();
	return result;
}

const Rational Rational::operator%(const Integer& rhs)const{ //......
	return *this - round(*this/rhs,ROUND_DOWN)*rhs;
}

Rational& Rational::operator=(const Integer& rhs){
	numerator = rhs.getNat();
	denominator = 1;
	sign = rhs.getSign();
	return *this;
}

Rational& Rational::operator+=(const Integer& rhs){
	return *this = *this + rhs;
}

Rational& Rational::operator-=(const Integer& rhs){
	return *this = *this - rhs;
}

Rational& Rational::operator*=(const Integer& rhs){
	return *this = *this * rhs;
}

Rational& Rational::operator/=(const Integer& rhs){
	return *this = *this / rhs;
}

const Rational Rational::operator+(const Rational& rhs)const{
	Natural lnum = numerator * rhs.denominator;
	Natural rnum = rhs.numerator * denominator;
	Rational result;
	if(sign == rhs.sign){
		result.sign = sign;
		result.numerator = lnum + rnum;
	}else{
		if(lnum > rnum){
			result.sign = sign;
			result.numerator = lnum - rnum;
		}else if(rnum > lnum){
			result.sign = rhs.sign;			
			result.denominator = rnum - lnum;
		}else{
			result.numerator = 0;
			result.sign = false;
		}
	}
	result.denominator = denominator*rhs.denominator;
	return result;
}

const Rational Rational::operator-(const Rational& rhs)const{ 
	Rational result;
	result.denominator = denominator * rhs.denominator;
	Natural lnum = numerator * rhs.denominator;
	Natural rnum = rhs.numerator * denominator;

	if(sign != rhs.sign){
		result.numerator = lnum + rnum;
		result.sign = sign;
	}else{
		if(lnum > rnum){
			result.numerator = lnum - rnum;
			result.sign = sign;
		}else if(lnum < rnum){
			result.numerator = rnum - lnum;
			result.sign = !sign;
		}else{
			result.numerator = 0;
			result.sign = false;
		}
	}

	return result;
}

const Rational Rational::operator*(const Rational& rhs)const{
	Rational result;
	result.numerator = numerator * rhs.numerator;
	result.denominator = denominator * rhs.denominator;
	result.sign = (sign == rhs.getSign() ? false : true);
	return result;
}

const Rational Rational::operator/(const Rational& rhs)const{
	Rational result;
	result.numerator = numerator * rhs.denominator;
	result.denominator = denominator * rhs.numerator;
	result.sign = (sign == rhs.getSign() ? false : true);
	return result;
}

const Rational Rational::operator%(const Rational& rhs)const{  //......
	return *this - round(*this/rhs,ROUND_DOWN)*rhs;
}

Rational& Rational::operator=(const Rational& rhs){
	numerator = rhs.numerator;
	denominator = rhs.denominator;
	sign = rhs.sign;
	return *this;
}

Rational& Rational::operator+=(const Rational& rhs){
	return *this = *this + rhs;
}

Rational& Rational::operator-=(const Rational& rhs){
	return *this = *this - rhs;
}

Rational& Rational::operator*=(const Rational& rhs){
	return *this = *this * rhs;
}

Rational& Rational::operator/=(const Rational& rhs){
	return *this = *this / rhs;
}

/*****
 can be more efficient!
*****/

bool Rational::operator<(const int& i)const{
	return *this < Rational(i);
}

bool Rational::operator<=(const int& i)const{
	return *this <= Rational(i);
}

bool Rational::operator==(const int& i)const{
	return *this == Rational(i);
}

bool Rational::operator!=(const int& i)const{
	return *this != Rational(i);
}

bool Rational::operator>=(const int& i)const{
	return *this >= Rational(i);
}

bool Rational::operator>(const int& i)const{
	return *this > Rational(i);
}

/*****

*****/

bool Rational::operator<(const Natural& rhs)const{
	if(sign){
		return true;
	}
	Natural g = numerator/denominator;
	if(g < rhs){
		return true;
	}
	return false;
}

bool Rational::operator<=(const Natural& rhs)const{
	return !( *this > rhs );
}

bool Rational::operator==(const Natural& rhs)const{
	if(sign){
		return false;
	}
	Natural tmp = numerator/denominator;
	if( tmp == rhs ){
		Rational r = *this - tmp;
		if( r != 0 ){
			return false;
		}
		return true;
	}
	return false;
}

bool Rational::operator!=(const Natural& rhs)const{
	return !(*this == rhs);
}

bool Rational::operator>=(const Natural& rhs)const{
	return !( *this < rhs );
}

bool Rational::operator>(const Natural& rhs)const{
	if(sign){
		return false;
	}
	Natural tmp = numerator/denominator;
	if( tmp > rhs ){
		return true;
	}else if( tmp == rhs && (*this - tmp) != 0 ){
		return true;
	}
	return false;
}

/*****

*****/

bool Rational::operator<(const Integer& rhs)const{
	if(sign != rhs.getSign()){
		if(sign){
			return true;
		}
		return false;
	}
	return (*this < rhs.getNat());
}

bool Rational::operator<=(const Integer& rhs)const{
	return !( *this > rhs );
}

bool Rational::operator==(const Integer& rhs)const{
	if(sign != rhs.getSign()){
		return false;
	}
	return ( *this == rhs.getNat() );
}

bool Rational::operator!=(const Integer& rhs)const{
	return !( *this == rhs );
}

bool Rational::operator>=(const Integer& rhs)const{
	return !( *this < rhs );
}

bool Rational::operator>(const Integer& rhs)const{
	if(sign != rhs.getSign()){
		if(sign){
			return false;
		}else{
			return true;
		}
	}
	return ( *this > rhs.getNat() );
}

/******

******/

bool Rational::operator<(const Rational& rhs)const{
	Natural l = numerator*rhs.denominator;
	Natural r = rhs.numerator*denominator;
	if(l < r){
		return true;
	}
	return false;
}

bool Rational::operator<=(const Rational& rhs)const{
	return !(*this > rhs);
}

bool Rational::operator==(const Rational& rhs)const{
	Natural l = numerator*rhs.denominator;
	Natural r = rhs.numerator*denominator;
	if(l == r){
		return true;
	}
	return false;
}

bool Rational::operator!=(const Rational& rhs)const{
	return !(*this == rhs);
}

bool Rational::operator>=(const Rational& rhs)const{
	return !(*this < rhs);
}

bool Rational::operator>(const Rational& rhs)const{
	Natural l = numerator*rhs.denominator;
	Natural r = rhs.numerator*denominator;
	if(l > r){
		return true;
	}
	return false;
}


};