#include <string>
#include <iostream>
#include "utility.h"
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

bool Natural::isInteger(){
	return true;
}

string Natural::toString(){
	string str = "";
	char c;
	int i=size-1;
	for( ; i > 0 ; i-- ){
		for( int j = 17 ; j >= 0 ; j-- ){
			c=(digits[i]/mod[j])%10+48;
			str.push_back(c);
		}
	}
	for(int j=17;j>=0;j--){
		if(digits[0]>mod[j]){
			c=(digits[i]/mod[j])%10+48;
			str.push_back(c);		
		}
	}
	cropzeros(&str);
	return str;
}
void Natural::setDigits(ebyte* d, unsigned int ui){
	digits=d;
	size=ui;
}
unsigned int Natural::getSize(){
	return size;
}

Natural Natural::operator+(Natural& right){
	Number result;
	unsigned int s=(getSize() < right.getSize())? right.getSize()+1 : getSize()+1;
	unsigned int min=(getSize() > right.getSize())? right.getSize() : getSize();
	ebyte* d=new ebyte[s];
	ebyte buffer=0;
	for(int i=0;i<min;i++){
		d[i]=(buffer+digits[i]+right.digits[i])%mod[19];
		buffer=(buffer+digits[i]+right.digits[i])/mod[19];
	}
	if(getSize() > min){
		for(int i=min;i<s;i++){
			d[i]=(buffer+digits[i])%mod[19];
			buffer=(buffer+digits[i])/mod[19];
		}
	}else if(right.getSize() > min){
		for(int i=min;i<s;i++){
			d[i]=(buffer+right.digits[i])%mod[19];
			buffer=(buffer+right.digits[i])/mod[19];			
		}
	}

	result->digits=d;
	result->size=s;
	return result;
}