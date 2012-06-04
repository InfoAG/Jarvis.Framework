#ifndef _NATURAL_H_
#define _NATURAL_H_

#include <string>
#include <iostream>
#include "Number.h"

using namespace std;

namespace CAS{
	class Natural : public Number{
	private:
		ebyte *digits;
		unsigned int size;
	public:
		Natural();
		Natural(unsigned int);
		Natural(string);
		bool isInteger();
		string toString();
		void setDigits(ebyte*, unsigned int);
		unsigned int getSize();

		Natural& operator+(Natural& right);
	};
};

#endif