/* FileName: test_mde.cpp */

#include "MDE.h"

#define PRO 1
#define T 1
#define D 30
#define NP 30
#define DEBUG 0

int main (int argc, char* argv[]) {
	
	
	int t  = atoi(argv[1]);
	
	for ( int pro = 1; pro <= PRO; pro ++) {	
		double ans[25];
		double avg = 0.0;
		/*
		cout << "problem " << pro << ":\t";
		cout << endl;
		cout << "answers : " << endl;
		*/
		for ( int cnt = 0; cnt < T; cnt ++) {
			MDE mde(D, NP, t, INT_MAX, 0.0);
			mde._set_f(0.5);
			mde._set_cr(0.5);
			mde._set_or(0.4);
			mde._set_fes(100000);
			ans[cnt] = mde._de(DEBUG);
			//cout << ans[cnt] << " ";
			avg += ans[cnt];
		}
		/*
		cout << endl;
		avg /= T;
		cout << avg << "\t";
	   	double dev = 0.0;
		for ( int i = 0; i < T; i ++) {
			dev += (avg - ans[i]) * (avg - ans[i]);
		}	
		cout << sqrt(dev) << endl;
		*/
		
	}
	return 0;	
}
