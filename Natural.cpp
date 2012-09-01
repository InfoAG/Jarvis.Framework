#include "Natural.h"
#include <iostream>
namespace CAS {

Natural::Natural(){
	size=1;
	digits.resize(size);
	digits.at(0)=0;
}
Natural::Natural(char c){
	if(c<0)
		Natural((unsigned char)(c*-1));
	else 
		Natural((unsigned char)c);
}
Natural::Natural(unsigned char uc){
	digits.push_back((int)uc);
	size=1;
}
Natural::Natural(short s){
	if(s<0)
		Natural((unsigned short)(s*-1));
	else 
		Natural((unsigned short)s);
}
Natural::Natural(unsigned short us){
	digits.push_back(us);
	size=1;

}
Natural::Natural(int i){
	if(i<0)
		Natural((unsigned int)(i*-1));
	else
		Natural((unsigned int)i);
}
Natural::Natural(unsigned int ui){
	if(ui<intmod[MAX_INT]){
		digits.push_back(ui);
		size=1;
	}else{
		digits.push_back(ui%intmod[MAX_INT]);
		digits.push_back(ui/intmod[MAX_INT]);
		size=2;
	}
}
Natural::Natural(long l){
	if(l<0)
		Natural((unsigned int)(l*-1));
	else
		Natural((unsigned int)l);
}
Natural::Natural(unsigned long ul){
	Natural((unsigned int)ul);
}
Natural::Natural(long long ll){
	if(ll<0){
		Natural((unsigned long long)(ll*-1));
	}else{
		Natural((unsigned long long)ll);
	}
}
Natural::Natural(unsigned long long ull){ 

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


void Natural::randomize(unsigned int s, unsigned int seed){
	size=s;
	digits.resize(size);
	PRG p(time(NULL)^seed,seed^s);
	for(fbyte i = 0 ; i < size;i++){
        digits.at(i)=p.next()%intmod[std::numeric_limits<int>::max()];
	}
}
/****

****/

bool Natural::isInteger(){
	return true;
}
bool Natural::isEven(){
	return !this->isOdd();
}
bool Natural::isOdd(){
	if(digits.at(0)%2==0)
		return false;
	return true;
}
bool Natural::isPrime(){
	return true;
}

/****

****/

Natural Natural::LeftShift(int ui)const{
	Natural result;
	result.size=size+ui;
	result.digits.resize(result.size);
	for(fbyte i=0;i<ui;i++){
		result.digits.at(i)=0;
	}for(fbyte i=ui;i<result.size;i++){
		result.digits.at(i) = digits.at(i-ui);
	}
	return result;
}
Natural Natural::RightShift(int ui)const{
	if(ui>=size){
		Natural result(0);
		return result;
	}
	if(ui==0)
		return *this;
	Natural result;
	result.size=size-ui;
	result.digits.resize(result.size);
	for(fbyte i=0;i<result.size;i++){
		result.digits.at(i)=digits.at(i+ui);
	}
	return result;
}
Natural Natural::MSB(unsigned int ui)const{
	if(ui==0){
		Natural result(0);
		return result;
	}
	if(ui>=size)
		return (*this);
	Natural result;
	result.size=ui;
	result.digits.resize(result.size);
	for(fbyte i=0;i<ui;i++){
		result.digits.at(i) = digits.at(size-ui+i);
	}
	return result;
}
Natural Natural::LSB(unsigned int ui)const{
	if(ui==0){
		Natural result(0);
		return result;
	}
	if(ui>=size){
		return (*this);
	}
	Natural result;
	result.size=ui;
	result.digits.resize(result.size);
	for(fbyte i=0;i<ui;i++){
		result.digits.at(i) = digits.at(i);
	}
	return result;
}

/****

****/
Natural Natural::Addition(const Natural& rhs){
	fbyte min = (size < rhs.getSize())? size : rhs.getSize();
	fbyte max = (size > rhs.getSize())? size : rhs.getSize();
	fbyte tmp = 0;
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
	if(buffer==0){
		result.digits=c;
		result.size=max;
	}else{
		result.size=max+1;
		result.digits.resize(result.size);
		for(fbyte i=0;i<max;i++){
			result.digits.at(i) = c.at(i);
		}
		result.digits.at(max)=buffer;
	}
	return result;
}
Natural Natural::simpleAddition(const Natural& rhs){
	Natural result;
	fbyte tmp=getDigitsAt(0)+rhs.getDigitsAt(0);
	if (tmp>=intmod[MAX_INT]){
		result.size=2;
		result.digits.resize(result.size);
		result.digits.at(1)=tmp/intmod[MAX_INT];
		result.digits.at(0)=tmp%intmod[MAX_INT];
	}
	else{
		result.size=1;
		result.digits.resize(result.size);
		result.digits.at(0)=tmp;
	}
	return result;
}
Natural Natural::Subtraction(const Natural& rhs){
	fbyte min = rhs.getSize();
	fbyte max = getSize();
	fbyte carry = 0;
	int tmp = 0;
    std::vector<fbyte> c;
	c.resize(max);
	for(fbyte i = 0;i<min;i++){
		tmp=digits.at(i)-rhs.getDigitsAt(i)-carry;
		if(tmp>=0){
			c.at(i)=tmp%intmod[MAX_INT];
			carry=0;
		}else{
			c.at(i)=(intmod[MAX_INT]+tmp)%intmod[MAX_INT];
			carry=1;
		}
	}
	for(fbyte i=min;i<max;i++){
		tmp=digits.at(i)-carry;
		if(tmp>=0){
			c.at(i)=tmp%intmod[MAX_INT];
			carry=0;
		}else{
			c.at(i)=(intmod[MAX_INT]+tmp)%intmod[MAX_INT];
			carry=1;
		}
	}
	fbyte count=0;
	for(int i = max-1 ; i >= 1 && c.at(i)==0; i--){
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
Natural Natural::simpleSubtraction(const Natural& rhs){
	Natural result;
	result.size=1;
	result.digits.resize(result.size);
	result.digits.at(0)=getDigitsAt(0)-rhs.getDigitsAt(0);
	return result;
}
Natural Natural::Multiplication(const Natural& rhs){
	fbyte k = size;
	fbyte m = rhs.getSize();
	fbyte buffer = 0;
	ebyte tmp = 0;
    std::vector<fbyte> c;
	c.resize(k+m+1);

	for(fbyte i=0;i<k;i++){
		buffer=0;
		for(fbyte j=0;j<m;j++){
			tmp = (ebyte)c.at(i+j)+(ebyte)buffer+(ebyte)digits.at(i)*(ebyte)rhs.getDigitsAt(j);
			c.at(i+j) = (fbyte)(tmp % emod);
			buffer = (fbyte)(tmp / emod);
		}
		c.at(i+m)=buffer;
	}
	fbyte count=0;
	for(int i = k+m ; i >= 1 && c.at(i)==0; i--){
		count++;
	}
	Natural result;
	result.size = k+m+1 - count;
	result.digits.resize(result.size);
	for(fbyte i = 0 ; i < result.size ; i++){
		result.digits.at(i) = c.at(i);
	}
	return result;
}
Natural Natural::simpleMultiplication(const Natural& rhs)const{
    std::vector<fbyte> c;
	fbyte s=getSize()+1;
	ebyte tmp = 0;
	c.resize(s);
	for(fbyte i = 0 ; i < getSize() ; i++){
		tmp     = tmp + (ebyte)getDigitsAt(i)*(ebyte)rhs.getDigitsAt(0);
		c.at(i) = (fbyte) (tmp / emod);
		tmp     = (fbyte) (tmp % emod);
	}
	c.at(getSize())=tmp;
	Natural result;
	result.digits=c;
	result.size=s;
	return result;
}
Natural Natural::shortDivision(const Natural& rhs){
	ebyte r=0;
	ebyte tmp = 0;
    std::vector<fbyte> c;
	c.resize(getSize());
	for(fbyte j=getSize()-1;j>=1;j--){
		tmp     = r * emod + (ebyte)digits.at(j);
		c.at(j) = tmp / rhs.getDigitsAt(0);
		r       = tmp % rhs.getDigitsAt(0);
	}
	tmp     = r * emod + (ebyte)digits.at(0);
	c.at(0) = tmp / rhs.getDigitsAt(0);

	Natural result;
	result.size=getSize();
	result.digits=c;
	return result;
}
Natural Natural::longDivision(const Natural& rhs){
	fbyte buffer;
	Natural Normalization((unsigned int)(emod/(rhs.getDigitsAt(rhs.getSize()-1)+1)));
	Natural tmp;
	Natural Buffer;
	Natural Q;
	Natural Dividend(*this);
	Natural Divisor(rhs);
	Dividend = Dividend*Normalization;
	Divisor  = Divisor*Normalization;
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
        //cout<<"Dividend:"<<endl<<Dividend.toString()<<endl;
        //cout<<"TMP:"<<endl<<tmp.toString()<<endl;
		//cout<<"quotient  "<<j<<" "<<buffer<<endl;
		if(Dividend >= tmp){
			//cout<<"true"<<endl;
			Dividend = Dividend - tmp;
		}else{
			//cout<<"false"<<endl;
			Dividend = (Dividend + Divisor.LeftShift(j)) - tmp;
			buffer-=1;
		}
		Q.digits.at(j) = buffer;
		//cin>>buffer;
	}
	return Q;
}
fbyte Natural::longDivisionSubRoutine(fbyte a1, fbyte a2, fbyte a3, fbyte b1, fbyte b2){
	ebyte tmp = (ebyte)a1*emod+(ebyte)a2;
	fbyte q = (fbyte)(tmp / (ebyte)b1);
	fbyte r = (fbyte)(tmp % (ebyte)b1);
	if(q >= intmod[MAX_INT] || (ebyte)q*(ebyte)b2 > emod*(ebyte)r+(ebyte)a3){
		q--;
		r+=b1;
	}
	if(r < intmod[MAX_INT]){
		if(q >= intmod[MAX_INT] || (ebyte)q*(ebyte)b2 > emod*(ebyte)r+(ebyte)a3){
			q--;
			r+=b1;
		}
	}
	return q;
}
/****

****/

Natural Natural::Karatsuba(const Natural& rhs){
	fbyte split=(getSize()+rhs.getSize())/4;
	Natural x0=LSB(split);
	Natural x1=MSB(getSize()-split);
	Natural y0=rhs.LSB(split);
	Natural y1=rhs.MSB(rhs.getSize()-split);
	Natural z0=x0*y0;
	Natural z2=x1*y1;
	Natural z1=((x1+x0)*(y0+y1))-z2-z0;
	Natural result=z2.LeftShift(split+split)+z1.LeftShift(split)+z0;
	return result;
}

Natural Natural::Toom33(const Natural& rhs){
	return Natural();
}

Natural Natural::Toom44(const Natural& rhs){
	return Natural();
}

/****

****/
Natural Natural::operator+(const Natural& rhs){
	//if(this->getSize()==1&&rhs.getSize()==1)
	//	return this->simpleAddition(rhs);
	return this->Addition(rhs);
}
Natural Natural::operator+(const unsigned int& ui){
	Natural su(ui);
	return this->Addition(su);
}
Natural Natural::operator-(const Natural& rhs){
	if((*this)<rhs){
		//trow Exception
		Natural result(0);
		return result;
	}
	/*if(this->getSize()==1&&rhs.getSize()==1){
		return (*this).simpleSubtraction(rhs);
	}*/
	return (*this).Subtraction(rhs);
}
Natural Natural::operator-(const unsigned int& ui){
	Natural subtrahend(ui);
	return this->Subtraction(subtrahend);
}
Natural Natural::operator*(const Natural& rhs){
	fbyte min = (getSize()<rhs.getSize())?getSize():rhs.getSize();
	/*if(min>10000)
		return this->Toom44(rhs);
	if(min>1000)
		return this->Toom33(rhs);*/
	if(min>=100)
		return this->Karatsuba(rhs);
	return this->Multiplication(rhs);
}
Natural Natural::operator*(const unsigned int& ui) {
	Natural multiplicant(ui);
	return this->simpleMultiplication(multiplicant);
}
Natural Natural::operator/(const Natural& rhs){
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
Natural Natural::operator/(const unsigned int& ui){
	Natural divisor(ui);
	if(divisor.getSize()==1)
		return this->shortDivision(divisor);
	return this->longDivision(divisor);
}
Natural Natural::operator%(const Natural& rhs){
	return Natural(0);
}
Natural Natural::operator%(const unsigned int& ui){
	return Natural(0);
}
Natural Natural::operator=(const Natural& rhs){
	size=rhs.getSize();
	digits.resize(size);
	for(fbyte i=0;i<size;i++){
		digits.at(i)=rhs.getDigitsAt(i);
	}
	return (*this);
}
Natural Natural::operator=(const unsigned int& ui){
	digits.resize(1);
	digits.at(0)=ui;
	size=1;
	return (*this);
}
/****

****/

bool Natural::operator<(const Natural& rhs){
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
bool Natural::operator<=(const Natural& rhs){
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
bool Natural::operator>=(const Natural& rhs){
	return !((*this)<rhs);
}
bool Natural::operator>(const Natural& rhs){
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

}


























