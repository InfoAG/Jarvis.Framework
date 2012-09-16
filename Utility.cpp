#include "Utility.h"

namespace CAS {

void cropzeros(std::string* str){
	int i=0;
	for( ; i < str->size() - 1 && str->at(i)=='0';)
	{
		i++;
	}
	str->erase(0,i);
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

}
