#ifndef UTILITY_H
#define UTILITY_H

#include <string>

namespace CAS {

typedef unsigned int fbyte;
typedef unsigned long long ebyte;



const int MAX_INT = 9;

const fbyte intmod[10]={1,
					  10,
					  100,
					  1000,
					  10000,
					  100000,
					  1000000,
					  10000000,
					  100000000,
					  1000000000};

const ebyte emod =    1000000000;

const fbyte p = intmod[MAX_INT]+7;
void cropzeros(std::string* str);

class PRG{
private:
	fbyte x;
	fbyte y;
public:
	PRG(fbyte, fbyte);
	fbyte next();
};

}

#endif
