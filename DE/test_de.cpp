/* FileName: test_de.cpp */

#include "DE.h"

int main (int argc, char* argv[]) {
	
	/*
	int t;
	t = atoi(argv[1]);
	*/
	DE *de = new DE(30, 100, 15, INT_MAX, 0.0);
	de->_set_f(0.5);
	de->_set_cr(0.5);
	de->_set_fes(100000);
	de->_de(0);
	
	return 0;
}
