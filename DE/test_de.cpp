/* FileName: test_de.cpp */

#include "DE.h"

int main () {
	
	DE *de = new DE(30, 100, ONE, INT_MAX, 0.0);
	
	de->_set_f(0.9);
	de->_set_cr(0.5);
	de->_set_fes(10000000);
	de->_de();
	
	return 0;
}
