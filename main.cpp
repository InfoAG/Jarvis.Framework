#include <iostream>
#include <vector>
#include <time.h>
#include "Natural.h"
using namespace std;
using namespace CAS;

int main(int argc, char* argv[]){
	Natural f1 = "0";
	Natural f2 = "1";
	Natural f3 = "1";
	Natural f4;
	clock_t start;
	clock_t end;
	clock_t star=clock();
	for(fbyte i=0;i<100000;i++){
		f1=f2;
		f2=f3;
		f3=f1+f2;
		if(i==49999)
			f4=f1;
	//	f3*f2;
	}
	clock_t en=clock();
	cout<<"Time "<<((double)(en-star))/CLOCKS_PER_SEC<<endl<<endl;
	//cout<<f1.getSize()<<endl;
	//cout<<f1.toString()<<endl<<endl;
	//cout<<f4.toString()<<endl;
	//cout<<f4.getSize()<<endl<<endl;
	cout<<(f1/f4).toString()<<endl;
	cout<<(f1/f4).toString()<<endl;
	start=clock();
	/*for(int i=100000;i>4737;i--){
		f1=f3-f2;
		f3=f2;
		f2=f1;

	}*/
	end=clock();
	cout<<"done in "<<((double)(end-start))/CLOCKS_PER_SEC<<endl;
	int a;
	cin>>a;
	return 0;
}
