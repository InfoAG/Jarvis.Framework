#ifndef NUMBER_H
#define NUMBER_H

#include <string>
#include <iostream>
using namespace std;

typedef unsigned long long ebyte;

namespace CAS{

	class Number{
	private:
	public:
		virtual bool isInteger()=0;
		virtual string toString()=0;
		virtual Natural Add(Natural, Natural)=0;
	};

};

#endif //NUMBER_H

