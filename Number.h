#ifndef NUMBER_H
#define NUMBER_H

#include "Utility.h"

namespace CAS{
	
	class Number{
	private:
	public:
		virtual bool isInteger()=0;
		numType getType()const;
	};
	
};

#endif