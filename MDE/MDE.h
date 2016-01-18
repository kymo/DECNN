#ifndef MDE_H
#define MDE_H

/* FileName: MDE.h */

#include "IDE.h"

class MDE : public IDE {

private:
	int			_mu_best_idx;
	double 		_mu_best_val;
	double		OR;
	double		ALPHA;
	
	bool* 		turn_good;
	double**	F_vec;
	double**	CR_vec;
	//Population*	_last_pop;
	
public:
	MDE() {}
	MDE(int dim, int np, int func_type, double global_opt, double opt_val):
		IDE(dim, np, func_type, global_opt, opt_val) {
		_mu_best_idx = 0;
		_mu_best_val = global_opt;	
		/*_last_pop = new Population(dim, np);	
		
		for ( int i = 0; i < np; ++i) {
			_last_pop->_inds[i] = *(new Individual(dim));
			for ( int j = 0; j < _dim; j ++) {
				_last_pop->_inds[i]._x[j] = 0.0;
			}
		}
		*/
		
	}
	
	virtual ~MDE();
	double 	_de(int lock);
	void 	_mutation(int ind_index);
	void 	_cross_over(int ind_index);
	void 	_selection(int ind_index);
	void 	_set_or(double or_val);
};


bool cmp(const Individual &first, const Individual & second);


#endif
