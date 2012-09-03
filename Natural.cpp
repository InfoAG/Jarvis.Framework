#include "Natural.h"
#include <iostream>
using namespace std;

namespace CAS {

Natural::Natural(){
	size=1;
	digits.resize(size);
	digits.at(0)=0;
}

Natural::Natural(short s){
	if(s<0)
		s *= -1;
	size = 1;
	digits.resize(size);
	digits.at(0) = s;
}

Natural::Natural(unsigned short us){
	size = 1;
	digits.resize(size);
	digits.at(0) = us;
}

Natural::Natural(int i){
	if(i<0)
		i *= -1;
	if(i < intmod[MAX_INT]){
		size = 1;
		digits.resize(1);
		digits.at(0) = i;
	}else{
		size = 2;
		digits.resize(size);
		digits.at(0) = i % intmod[MAX_INT];
		digits.at(1) = i / intmod[MAX_INT];
	}
}

Natural::Natural(unsigned int ui){
	if(ui < intmod[MAX_INT]){
		size = 1;
		digits.resize(1);
		digits.at(0) = ui;
	}else{
		size = 2;
		digits.resize(size);
		digits.at(0) = ui % intmod[MAX_INT];
		digits.at(1) = ui / intmod[MAX_INT];
	}
}

Natural::Natural(long l){
	if(l<0)
		l *= -1;
	if(l < intmod[MAX_INT]){
		size = 1;
		digits.resize(1);
		digits.at(0) = l;
	}else{
		size = 2;
		digits.resize(size);
		digits.at(0) = l % intmod[MAX_INT];
		digits.at(1) = l / intmod[MAX_INT];
	}
}

Natural::Natural(unsigned long ul){
	if(ul < intmod[MAX_INT]){
		size = 1;
		digits.resize(1);
		digits.at(0) = ul;
	}else{
		size = 2;
		digits.resize(size);
		digits.at(0) = ul % intmod[MAX_INT];
		digits.at(1) = ul / intmod[MAX_INT];
	}
}

Natural::Natural(long long ll){
	if(ll<0)
		ll *= -1;
	size = 1;
	digits.resize(size);
	digits.at(ll % intmod[MAX_INT]);
	ll = ll / intmod[MAX_INT];
	if(ll > 0){
		digits.push_back(ll % intmod[MAX_INT]);
		size++;
		ll = ll / intmod[MAX_INT];
	}
	if(ll > 0){
		digits.push_back(ll % intmod[MAX_INT]);
		size++;
		ll = ll / intmod[MAX_INT];
	}
}

Natural::Natural(unsigned long long ull){ 
	size = 1;
	digits.resize(size);
	digits.at(ull % intmod[MAX_INT]);
	ull = ull / intmod[MAX_INT];
	if(ull > 0){
		digits.push_back(ull % intmod[MAX_INT]);
		size++;
		ull = ull / intmod[MAX_INT];
	}
	if(ull > 0){
		digits.push_back(ull % intmod[MAX_INT]);
		size++;
		ull = ull / intmod[MAX_INT];
	}
}

Natural::Natural(float f){

}

Natural::Natural(double d){

}

Natural::Natural(std::string str){
	if(str.find_first_not_of("0123456789")!=str.npos){
		//throw exception()
	}
	if(str.length()%9==0)
		size=str.length()/9;
	else
		size=str.length()/9+1;
	digits.resize(size);
	fbyte t=0;
	fbyte buffer=0;
	unsigned int i = str.length() - 1;
	if(i>9){
		for(;i>8;i-=9){
			for(int j=0;j<9;j++){
				buffer+=(str.at(i-j)-48)*intmod[j];
			}
			digits.at(t)=buffer%intmod[MAX_INT];
			t++;
			buffer=0;
		}
		if(i!=0){
			for(fbyte j=0;j<=i;j++){
				buffer+=(str.at(i-j)-48)*intmod[j];
			}
			digits.at(t)=buffer;
		}else{
			digits.at(t)=(str.at(0)-48);
		}
	}else{
		for(int j=0;j<=i;j++){
			buffer+=(str.at(i-j)-48)*intmod[j];
		}	
		digits.at(t)=buffer;	
	}
}

/****

****/

Natural::Natural(const Natural& rhs){
	digits=rhs.getDigits();
	size=rhs.getSize();
}

/*Natural::Natural(const Integer& rhs){
	digits=rhs.getDigits();
	size=rhs.getSize();
}*/

/****
GETTER FUNCTIONS
****/

std::vector<fbyte> Natural::getDigits()const{
	return digits;
}

fbyte Natural::getDigitsAt(unsigned int ui)const{
	return digits.at(ui);
}

fbyte Natural::getSize()const{
	return size;
}

std::string Natural::toString()const{
    std::string str = "";
	char c;
	for(int i=size-1 ; i >= 0 ; i-- ){
		for( int j = 8 ; j >= 0 ; j-- ){
			c=(digits.at(i)/intmod[j])%10+48;
			str.push_back(c);
		}
		str.push_back(' ');
	}
	
	cropzeros(&str);
	return str;
}


/****
PROPERTIES
****/

bool Natural::isInteger(){
	return true;
}
bool Natural::isEven(){
	return !this->isOdd();
}
bool Natural::isOdd(){
	if(digits.at(0) % 2 == 0)
		return false;
	return true;
}
bool Natural::isPrime(){
	return true;
}

/****
SHIFT OPERATIONS
****/

Natural Natural::LeftShift(int ui)const{
	Natural result;
	result.size = size + ui;
	result.digits.resize(result.size);
	for(fbyte i = 0 ; i < ui ; i++){
		result.digits.at(i) = 0;
	}for(fbyte i = ui ; i < result.size ; i++){
		result.digits.at(i) = digits.at(i - ui);
	}
	return result;
}
Natural Natural::RightShift(int ui)const{
	if(ui >= size){
		Natural result(0);
		return result;
	}
	if(ui == 0)
		return *this;
	Natural result;
	result.size = size - ui;
	result.digits.resize(result.size);
	for(fbyte i = 0 ; i < result.size ; i++){
		result.digits.at(i) = digits.at(i + ui);
	}
	return result;
}
Natural Natural::MSB(int ui)const{
	if(ui == 0){
		Natural result(0);
		return result;
	}
	if(ui >= size)
		return (*this);
	Natural result;
	result.size = ui;
	result.digits.resize(result.size);
	for(fbyte i = 0 ; i < ui ; i++){
		result.digits.at(i) = digits.at(size - ui + i);
	}
	return result;
}
Natural Natural::LSB(int ui)const{
	if(ui <= 0){
		Natural result(0);
		return result;
	}
	if(ui >= size){
		return (*this);
	}
	Natural result;
	result.size = ui;
	result.digits.resize(result.size);
	for(fbyte i = 0 ; i < ui ; i++){
		result.digits.at(i) = digits.at(i);
	}
	return result;
}

/****
SCHOOLBOOK ALGORITHMS
****/
Natural Natural::Addition(const Natural& rhs)const{
	fbyte min    = (size < rhs.getSize())? size : rhs.getSize();
	fbyte max    = (size > rhs.getSize())? size : rhs.getSize();
	fbyte tmp    = 0;
	fbyte buffer = 0;
    std::vector<fbyte> c(max);
	for(fbyte i = 0 ; i < min ; i++){
		tmp	    = buffer + digits.at(i) + rhs.getDigitsAt(i);
		buffer  = tmp / intmod[MAX_INT];
		c.at(i) = tmp % intmod[MAX_INT];
	}
	if(size >= max){
		for(fbyte i = min ; i < max ; i++){
			tmp     = buffer + digits.at(i);
			buffer  = tmp / intmod[MAX_INT];
			c.at(i) = tmp % intmod[MAX_INT];
		}	
	}
	if(rhs.getSize() >= max){
		for(fbyte i = min ; i < max ; i++){
			tmp		= buffer + rhs.getDigitsAt(i);
			buffer  = tmp / intmod[MAX_INT];
			c.at(i) = tmp % intmod[MAX_INT];
		}
	}
	Natural result;
	if(buffer == 0){
		result.digits = c;
		result.size   = max;
	}else{
		result.size = max + 1;
		result.digits.resize(result.size);
		for(fbyte i = 0 ; i < max ; i++){
			result.digits.at(i) = c.at(i);
		}
		result.digits.at(max) = buffer;
	}
	return result;
}

Natural Natural::simpleAddition(const Natural& rhs)const{
	Natural result;
	fbyte tmp = getDigitsAt(0) + rhs.getDigitsAt(0);
	if (tmp >= intmod[MAX_INT]){
		result.size = 2;
		result.digits.resize(result.size);
		result.digits.at(1) = tmp / intmod[MAX_INT];
		result.digits.at(0) = tmp % intmod[MAX_INT];
	}
	else{
		result.size = 1;
		result.digits.resize(result.size);
		result.digits.at(0) = tmp;
	}
	return result;
}
Natural Natural::Subtraction(const Natural& rhs)const{
	fbyte min   = rhs.getSize();
	fbyte max   = getSize();
	fbyte carry = 0;
	int tmp     = 0;
    std::vector<fbyte> c;
	c.resize(max);
	for(fbyte i = 0 ; i < min ; i++){
		tmp = digits.at(i) - rhs.getDigitsAt(i) - carry;
		if(tmp >= 0){
			c.at(i) = tmp % intmod[MAX_INT];
			carry   = 0;
		}else{
			c.at(i) = (intmod[MAX_INT] + tmp) % intmod[MAX_INT];
			carry   = 1;
		}
	}
	for(fbyte i = min ; i < max ; i++){
		tmp = digits.at(i) - carry;
		if(tmp >= 0){
			c.at(i) = tmp % intmod[MAX_INT];
			carry   = 0;
		}else{
			c.at(i) = (intmod[MAX_INT] + tmp) % intmod[MAX_INT];
			carry   = 1;
		}
	}
	fbyte count = 0;
	for(int i = max-1 ; i >= 1 && c.at(i) == 0; i--){
		count++;
	}
	Natural result;
	result.size = max - count;
	result.digits.resize(result.size);
	for(fbyte i = 0 ; i < result.size ; i++){
		result.digits.at(i) = c.at(i);
	}
	return result;
}
Natural Natural::simpleSubtraction(const Natural& rhs)const{
	Natural result;
	result.size = 1;
	result.digits.resize(result.size);
	result.digits.at(0) = getDigitsAt(0) - rhs.getDigitsAt(0);
	return result;
}
Natural Natural::Multiplication(const Natural& rhs)const{
	fbyte k = size;
	fbyte m = rhs.getSize();
	fbyte buffer = 0;
	ebyte tmp = 0;
    std::vector<fbyte> c;
	c.resize(k + m + 1);
	for(fbyte i = 0 ; i < k ; i++){
		buffer = 0;
		for(fbyte j = 0 ; j < m ; j++){
			tmp = (ebyte)c.at(i + j) + (ebyte)buffer + (ebyte)digits.at(i) * (ebyte)rhs.getDigitsAt(j);
			c.at(i + j) = (fbyte)(tmp % emod);
			buffer = (fbyte)(tmp / emod);
		}
		c.at(i + m)=buffer;
	}
	fbyte count=0;
	for(int i = k + m ; i >= 1 && c.at(i) == 0; i--){
		count++;
	}
	Natural result;
	result.size = k + m + 1 - count;
	result.digits.resize(result.size);
	for(fbyte i = 0 ; i < result.size ; i++){
		result.digits.at(i) = c.at(i);
	}
	return result;
}
Natural Natural::simpleMultiplication(const Natural& rhs)const{
    std::vector<fbyte> c;
	fbyte s   = getSize() + 1;
	ebyte tmp = 0;
	c.resize(s,0);
	for(fbyte i = 0 ; i < getSize() ; i++){
		tmp     = tmp + (ebyte)getDigitsAt(i)*(ebyte)rhs.getDigitsAt(0);
		c.at(i) = (fbyte) (tmp % emod);
		tmp     = (fbyte) (tmp / emod);
	}
	if(tmp!=0)
		c.at(getSize()) = tmp;
	else{
		c.pop_back();
		s--;
	}
	Natural result;
	result.digits=c;
	result.size=s;
	return result;
}
Natural Natural::shortDivision(const Natural& rhs)const{
	ebyte r   = 0;
	ebyte tmp = 0;
    std::vector<fbyte> c;
	c.resize(getSize());
	for(fbyte j = getSize()-1 ; j >= 1 ; j--){
		tmp     = r * emod + (ebyte)digits.at(j);
		c.at(j) = tmp / rhs.getDigitsAt(0);
		r       = tmp % rhs.getDigitsAt(0);
	}
	tmp     = r * emod + (ebyte)digits.at(0);
	c.at(0) = tmp / rhs.getDigitsAt(0);

	Natural result;
	result.size   = getSize();
	result.digits = c;
	return result;
}
Natural Natural::longDivision(const Natural& rhs)const{
	fbyte buffer;
	Natural Normalization((unsigned int)(emod/(rhs.getDigitsAt(rhs.getSize()-1)+1)));
	Natural tmp;
	Natural Buffer;
	Natural Q;
	Natural Dividend(*this);
	Natural Divisor(rhs);
	Dividend = Dividend * Normalization;
	Divisor  = Divisor  * Normalization;
	fbyte difference = Dividend.getSize() - Divisor.getSize();
	Q.size   = difference;
	Q.digits.resize(difference);
	for(int j = difference-1 ; j >= 0 ; j--){
		if(Dividend.getSize() >= 3)
			buffer = longDivisionSubRoutine(Dividend.digits.at(Dividend.getSize()-1),
											Dividend.digits.at(Dividend.getSize()-2),
											Dividend.digits.at(Dividend.getSize()-3),
											Divisor.digits.at(Divisor.getSize()-1),
											Divisor.digits.at(Divisor.getSize()-2));
		else if(Dividend.getSize() == 2)
			buffer = longDivisionSubRoutine(Dividend.digits.at(Dividend.getSize()-1),
											Dividend.digits.at(Dividend.getSize()-2),
											0,
											Divisor.digits.at(Divisor.getSize()-1),
											Divisor.digits.at(Divisor.getSize()-2));
		else
			buffer = 0;
		Buffer = buffer;
		tmp    = (Buffer * Divisor).LeftShift(j);
		if(Dividend >= tmp){
			Dividend = Dividend - tmp;
		}else{
			Dividend = (Dividend + Divisor.LeftShift(j)) - tmp;
			buffer -= 1;
		}
		Q.digits.at(j) = buffer;
	}
	return Q;
}
fbyte Natural::longDivisionSubRoutine(fbyte a1, fbyte a2, fbyte a3, fbyte b1, fbyte b2)const{
	ebyte tmp = (ebyte)a1 * emod + (ebyte)a2;
	fbyte q   = (fbyte)(tmp / (ebyte)b1);
	fbyte r   = (fbyte)(tmp % (ebyte)b1);
	if(q >= intmod[MAX_INT] || (ebyte)q*(ebyte)b2 > emod*(ebyte)r+(ebyte)a3){
		q--;
		r += b1;
	}
	if(r < intmod[MAX_INT]){
		if(q >= intmod[MAX_INT] || (ebyte)q*(ebyte)b2 > emod*(ebyte)r+(ebyte)a3){
			q--;
			r += b1;
		}
	}
	return q;
}
/****

****/

Natural Natural::fusedMultiplyAdd(const Natural& add, const Natural& rhs)const{
	fbyte k = size;
	fbyte m = rhs.getSize();
	fbyte buffer = 0;
	ebyte tmp = 0;
	std::vector<fbyte> c = add.getDigits();
	fbyte minsize = k + m + 1;
	fbyte s = add.getSize();
	if(minsize > s){
		c.resize(minsize,0);
		s = minsize;
	}
	for(fbyte i = 0 ; i < k ; i++){
		buffer = 0;
		for(fbyte j = 0 ; j < m ; j++){
			tmp = (ebyte)c.at(i + j) + (ebyte)buffer + (ebyte)digits.at(i) * (ebyte)rhs.getDigitsAt(j);
			c.at(i + j) = (fbyte)(tmp % emod);
			buffer = (fbyte)(tmp / emod);
		}
		c.at(i + m)+=buffer;
	}
	fbyte count=0;
	for(int i = k + m ; i >= 1 && c.at(i) == 0; i--){
		count++;
	}
	Natural result;
	result.size = s - count;
	result.digits.resize(result.size);
	for(fbyte i = 0 ; i < result.size ; i++){
		result.digits.at(i) = c.at(i);
	}
	return result;
}

Natural Natural::Karatsuba(const Natural& rhs)const{
	fbyte split    = (getSize() + rhs.getSize())/4;
	Natural x0     = LSB(split);
	Natural x1     = MSB(getSize() - split);
	Natural y0     = rhs.LSB(split);
	Natural y1     = rhs.MSB(rhs.getSize() - split);
	Natural z0     = x0 * y0;
	Natural z2     = x1 * y1;
	Natural z1     = ((x1 + x0) * (y0 + y1)) - z2 - z0;
	Natural result = z2.LeftShift(split + split) + z1.LeftShift(split) + z0;
	return result;
}
Natural Natural::Toom33(const Natural& rhs)const{
	fbyte split = (getSize() + rhs.getSize())/6;
	Natural u0 = LSB(split);
	Natural u1 = RightShift(split).LSB(split);
	Natural u2 = MSB(getSize()-split*2);
	Natural v0 = rhs.LSB(split);
	Natural v1 = rhs.RightShift(split).LSB(split);
	Natural v2 = rhs.MSB(rhs.getSize()-2*split);
	Natural uat0 = u0;
	Natural uat1 = u0 + u1   + u2;
	Natural uat2 = u0 + u1*2 + u2*4;
	Natural uat3 = u0 + u1*3 + u2*9;
	Natural uat4 = u0 + u1*4 + u2*16;
	Natural vat0 = v0;
	Natural vat1 = v0 + v1   + v2;
	Natural vat2 = v0 + v1*2 + v2*4;
	Natural vat3 = v0 + v1*3 + v2*9;
	Natural vat4 = v0 + v1*4 + v2*16;

	Natural wat0 = uat0 * vat0;
	Natural wat1 = uat1 * vat1;
	Natural wat2 = uat2 * vat2;
	Natural wat3 = uat3 * vat3;
	Natural wat4 = uat4 * vat4;
	//////////////////////////////////////
	Natural a0 = wat0;
	Natural a4 = wat4 - wat3;
	Natural a3 = wat3 - wat2;
	Natural a2 = wat2 - wat1;
	Natural a1 = wat1 - wat0;
	a4 = (a4 - a3)/2;
	a3 = (a3 - a2)/2;
	a2 = (a2 - a1)/2;
	
	a4 = (a4 - a3)/3;
	a3 = (a3 - a2)/3;

	a4 = (a4 - a3)/4;
	///////////////
	//Resolve Horner Scheme
	a3 = a3 - (a4*3);
	a2 = a2 - (a3*2);
	a1 = a1 - a2;
	a3 = a3 - (a4*2);
	a2 = a2 - a3;
	a3 = a3 - a4;
	Natural result = a0 + a1.LeftShift(split) + a2.LeftShift(2*split) + a3.LeftShift(3*split) + a4.LeftShift(4*split);
	return result;
}
Natural Natural::Toom44(const Natural& rhs)const{
	fbyte split = (getSize() + rhs.getSize())/8;
	Natural u0 = LSB(split);
	Natural u1 = RightShift(split);
	Natural u2 = u1.RightShift(split).LSB(split);
	Natural u3 = MSB(getSize()-3*split);
	u1         = u1.LSB(split);
	Natural v0 = rhs.LSB(split);
	Natural v1 = rhs.RightShift(split);
	Natural v2 = v1.RightShift(split).LSB(split);
	Natural v3 = rhs.MSB(rhs.getSize()-3*split);
	v1         = v1.LSB(split);
	
	Natural uat0 = u0;
	Natural uat1 = u0 + u1   + u2    + u3;
	Natural uat2 = u0 + u1*2 + u2*4  + u3*8;
	Natural uat3 = u0 + u1*3 + u2*9  + u3*27;
	Natural uat4 = u0 + u1*4 + u2*16 + u3*64;
	Natural uat5 = u0 + u1*5 + u2*25 + u3*125;
	Natural uat6 = u0 + u1*6 + u2*36 + u3*216;

	Natural vat0 = v0;
	Natural vat1 = v0 + v1   + v2    + v3;
	Natural vat2 = v0 + v1*2 + v2*4  + v3*8;
	Natural vat3 = v0 + v1*3 + v2*9  + v3*27;
	Natural vat4 = v0 + v1*4 + v2*16 + v3*64;
	Natural vat5 = v0 + v1*5 + v2*25 + v3*125;
	Natural vat6 = v0 + v1*6 + v2*36 + v3*216;

	Natural wat0 = uat0 * vat0;
	Natural wat1 = uat1 * vat1;
	Natural wat2 = uat2 * vat2;
	Natural wat3 = uat3 * vat3;
	Natural wat4 = uat4 * vat4;
	Natural wat5 = uat5 * vat5;
	Natural wat6 = uat6 * vat6;

	Natural a0 = wat0;
	Natural a1 = wat1 - wat0;
	Natural a2 = wat2 - wat1;
	Natural a3 = wat3 - wat2;
	Natural a4 = wat4 - wat3;
	Natural a5 = wat5 - wat4;
	Natural a6 = wat6 - wat5;

	a6 = (a6 - a5)/2;
	a5 = (a5 - a4)/2;
	a4 = (a4 - a3)/2;
	a3 = (a3 - a2)/2;
	a2 = (a2 - a1)/2;

	a6 = (a6 - a5)/3;
	a5 = (a5 - a4)/3;
	a4 = (a4 - a3)/3;
	a3 = (a3 - a2)/3;

	a6 = (a6 - a5)/4;
	a5 = (a5 - a4)/4;
	a4 = (a4 - a3)/4;

	a6 = (a6 - a5)/5;
	a5 = (a5 - a4)/5;

	a6 = (a6 - a5)/6;

	a5 = a5 - a6*5;
	a4 = a4 - a5*4;
	a3 = a3 - a4*3;
	a2 = a2 - a3*2;
	a1 = a1 - a2;

	a5 = a5 - a6*4;
	a4 = a4 - a5*3;
	a3 = a3 - a4*2;
	a2 = a2 - a3;

	a5 = a5 - a6*3;
	a4 = a4 - a5*2;
	a3 = a3 - a4;

	a5 = a5 - a6*2;
	a4 = a4 - a5;

	a5 = a5 - a6;
	
	Natural result = a0 + a1.LeftShift(split) + a2.LeftShift(2*split) + a3.LeftShift(3*split) + a4.LeftShift(4*split) + a5.LeftShift(5*split) + a6.LeftShift(6*split);
	return result;
}

/****
ARBITRARY INTEGER OPERATORS
****/
const Natural Natural::operator+(const Natural& rhs)const{
	if(this->getSize()==1&&rhs.getSize()==1)
		return this->simpleAddition(rhs);
	return this->Addition(rhs);
}
const Natural Natural::operator-(const Natural& rhs)const{
	if(this->operator<(rhs)){
		//trow Exception
		Natural result(0);
		return result;
	}
	if(this->getSize()==1&&rhs.getSize()==1){
		return (*this).simpleSubtraction(rhs);
	}
	return (*this).Subtraction(rhs);
}
const Natural Natural::operator*(const Natural& rhs)const{
	fbyte max = (getSize()<rhs.getSize())?getSize():rhs.getSize();
	if(max>=2000)
		return this->Toom44(rhs);
	if(max>=800)
		return this->Toom33(rhs);
	if(max>=200)
		return this->Karatsuba(rhs);
	return this->Multiplication(rhs);
}
const Natural Natural::operator/(const Natural& rhs)const{
	Natural result(0);
	if(result==rhs){
		return result;
	}
	if((*this)<rhs){	//throw Exception
		return result;
	}
	if(rhs.getSize()==1){
		return this->shortDivision(rhs);
	}
	return this->longDivision(rhs);
}
const Natural Natural::operator%(const Natural& rhs)const{
	return Natural(0);
}
Natural &Natural::operator=(const Natural& rhs){
	size=rhs.getSize();
	digits.resize(size);
	for(fbyte i=0;i<size;i++){
		digits.at(i)=rhs.getDigitsAt(i);
	}
	return (*this);
}
Natural &Natural::operator+=(const Natural& rhs){
	*this = *this + rhs;
	return *this;
}
Natural &Natural::operator-=(const Natural& rhs){
	*this = *this - rhs;
	return *this;
}
Natural &Natural::operator*=(const Natural& rhs){
	*this = *this * rhs;
	return *this;
}
Natural &Natural::operator/=(const Natural& rhs){
	*this = *this / rhs;
	return *this;
}


/****
INTEGER OPERATIONS
****/

const Natural Natural::operator+(const unsigned int& ui)const{
	Natural su(ui);
	return this->Addition(su);
}
const Natural Natural::operator-(const unsigned int& ui)const{
	Natural subtrahend(ui);
	return this->Subtraction(subtrahend);
}
const Natural Natural::operator*(const unsigned int& ui)const{
	Natural multiplicant(ui);
	return this->simpleMultiplication(multiplicant);
}
const Natural Natural::operator/(const unsigned int& ui)const{
	Natural divisor(ui);
	if(divisor.getSize()==1)
		return this->shortDivision(divisor);
	return this->longDivision(divisor);
}
const Natural Natural::operator%(const unsigned int& ui)const{
	return Natural(0);
}
Natural &Natural::operator=(const unsigned int& ui){
	digits.resize(1);
	digits.at(0)=ui;
	size=1;
	return (*this);
}
Natural &Natural::operator+=(const unsigned int& ui){
	*this = *this + ui;
	return *this;
}
Natural &Natural::operator-=(const unsigned int& ui){
	*this = *this - ui;
	return *this;
}
Natural &Natural::operator*=(const unsigned int& ui){
	*this = *this * ui;
	return *this;
}
Natural &Natural::operator/=(const unsigned int& ui){
	*this = *this / ui;
	return *this;
}
Natural &Natural::operator++(){
	*this += 1;
	return *this;
}
Natural &Natural::operator--(){
	*this -= 1;
	return *this;
}
Natural Natural::operator++(int){
	Natural result(*this);
	*this += 1;
	return result;
}
Natural Natural::operator--(int){
	Natural result(*this);
	*this -= 1;
	return result;
}
/****

****/

bool Natural::operator<(const Natural& rhs)const{
	if(size < rhs.getSize())
		return true;
	if(size > rhs.getSize())
		return false;
	for(fbyte i = size-1; i >=1 ; i--){
		if(getDigitsAt(i) != rhs.getDigitsAt(i)){
			return getDigitsAt(i) < rhs.getDigitsAt(i);
		}
	}
	return getDigitsAt(0) < rhs.getDigitsAt(0);
}
bool Natural::operator<=(const Natural& rhs)const{
	return !((*this)>rhs);
}
bool Natural::operator==(const Natural& rhs) const {
	if(size != rhs.getSize())
		return false;
	for(fbyte i = size-1; i >=1 ; i--){
		if(getDigitsAt(i) != rhs.getDigitsAt(i)){
			return false;
		}
	}
	return getDigitsAt(0) == rhs.getDigitsAt(0);
}
bool Natural::operator!=(const Natural& rhs) const{
	return !((*this)==rhs);
}
bool Natural::operator>=(const Natural& rhs)const{
	return !((*this)<rhs);
}
bool Natural::operator>(const Natural& rhs)const{
	if(size > rhs.getSize())
		return true;
	if(size < rhs.getSize())
		return false;
	for(fbyte i = size-1; i >=1 ; i--){
		if(getDigitsAt(i) != rhs.getDigitsAt(i)){
			return getDigitsAt(i) > rhs.getDigitsAt(i);
		}
	}
	return getDigitsAt(0) > rhs.getDigitsAt(0);
}

Natural nfaculty(unsigned int ui){
	if(ui<=1){
		Natural result((unsigned int)1);
		return result;
	}
	if(ui==2){
		Natural result((unsigned int)2);
		return result;
	}
	Natural result=(unsigned int)2;
	Natural tmp=(unsigned int)3;
	Natural add=(unsigned int)1;
	for(fbyte i=2;i<ui;i++){
		result=result*tmp;
		tmp=tmp+add;
	}
	return result;
}

}//End of Namespace CAS


























