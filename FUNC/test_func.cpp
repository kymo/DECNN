#include "func.h"


int main () {
	IFUNC* func = FuncFactory::get_instance()->create(ONE, 100, 0.0);
	double x[100];
	for ( int i = 0; i < 100; i ++) x[i] = 0.5;
	cout << func->_fitness(x) << endl;
	return 0;
	
}
