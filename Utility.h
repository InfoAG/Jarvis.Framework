#ifndef _UTILITY_H_
#define _UTILITY_H_

#include <string>
#include <iostream>
using namespace std;

typedef unsigned long long ebyte;

const int MAX_SIZE = 18;
const ebyte mod[19]={1, 
				10,
				100,
				1000,
				10000,
				100000,
				1000000,
				10000000,
				100000000,
				1000000000,
				10000000000,
				100000000000,
				1000000000000,
				10000000000000,
				100000000000000,
				1000000000000000,
				10000000000000000,
				100000000000000000,
				1000000000000000000};

void cropzeros(string*);

char inttochar(int);

#endif //_UTILITY_H_