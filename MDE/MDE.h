#ifndef MDE_H
#define MDE_H

/* FileName: MDE.h */

#include "IDE.h"

class MDE : public IDE {

public:
	MDE() {}
	MDE(int dim, int np, int func_type, double global_opt, double opt_val):
		IDE(dim, np, func_type, global_opt, opt_val) {}
	
	virtual ~MDE();
	void _mutation(int ind_index);
	void _cross_over(int ind_index);
	void _selection(int ind_index);
};

#endif
