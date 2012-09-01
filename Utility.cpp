#include "Utility.h"
void cropzeros(string* str){
	while(str->length() > 1 && str->at(0) == '0'){
		str->erase(0,1);	
	}
}

PRG::PRG(fbyte dx, fbyte dy){
	x=dx;
	y=dy;
}

fbyte PRG::next(){
	x=(2*x+5)%p;
	y=(3*y+7)%p;
	return (x^y)%p;
}