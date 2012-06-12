#include <string>
#include <iostream>
#include "Utility.h"
#include "Natural.h"
using namespace CAS;
using namespace std;

Natural::Natural(){
	size=1;
	digits=new ebyte[size];
	digits[0]=0;
}
Natural::Natural(unsigned int ui){
	size=1;
	digits=new ebyte[size];
	digits[0]=ui;
}
Natural::Natural(string str){
	int i=0;
	size=str.length()/MAX_SIZE+1;
	digits=new ebyte[size];
	for(int j=0;j<size;j++){
		digits[j]=0;
	}
	ebyte max=0;
	while(str.length()-max > MAX_SIZE){
		for(int j = 0 ; j < MAX_SIZE ; j++ ){
			digits[size-(i+1)]+=(str.at(max+j)-48)*mod[MAX_SIZE-(j+1)];
		}
		i++;
		max=MAX_SIZE*i;
	}//togo
	ebyte length=str.length()-max;
	for(int j = 0 ; j < length ; j++ ){
		digits[0]+=(str.at(max+j)-48)*mod[length-(j+1)];
	}
}
Natural::Natural(const Natural& rhs){
	digits=rhs.digits;
	size=rhs.size;
}

bool Natural::isInteger(){
	return true;
}

string Natural::toString(){
	string str = "";
	char c;

	for(int i=size-1 ; i >= 0 ; i-- ){
		for( int j = 17 ; j >= 0 ; j-- ){
			c=(digits[i]/mod[j])%10+48;
			str.push_back(c);
		}
	}
	
	cropzeros(&str);
	//if(str=="")
	//	str="0";
	return str;
}
void Natural::setDigits(ebyte* d, unsigned int ui){
	digits=d;
	size=ui;
}
unsigned int Natural::getSize(){
	return size;
}

//eigentlich Natural to be changed
Natural Natural::Addition(Natural right){
	Natural result(0);
	unsigned int s=((getSize() < right.getSize())? right.getSize() : getSize())+1;
	unsigned int min=((getSize() > right.getSize())? right.getSize() : getSize())+1;
	ebyte* f=new ebyte[s];
	ebyte buffer=0;
	for(int i=0;i<min;i++){
		f[i]=(buffer+digits[i]+right.digits[i])%mod[18];
		buffer=(buffer+digits[i]+right.digits[i])/mod[18];
	}
	if(getSize() > min){
		for(int i=min;i<s;i++){
			f[i]=(buffer+digits[i])%mod[18];
			buffer=(buffer+digits[i])/mod[18];
		}
	}else if(right.getSize() > min){
		for(int i=min;i<s;i++){
			f[i]=(buffer+right.digits[i])%mod[18];
			buffer=(buffer+right.digits[i])/mod[18];
		}
	}
	if(f[s-1]==0){
		result.size=s-1;
		result.digits=new ebyte[result.getSize()];
		for(int i=0;i<s-1;i++){
			result.digits[i]=f[i];
		}
	}else{
		result.size=s;
		result.digits=f;
	}
	return result;
}

Natural Natural::operator+(Natural right){
	return (*this).Addition(right);
}
