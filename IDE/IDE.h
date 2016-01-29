#ifndef IDE_H
#define IDE_H
/* FileName: IDE.h */

#include <cstring>
#include <vector>
#include <iostream>
#include <math.h>
#include <time.h>
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "func.h"

using namespace std;


#define STRATEGY_ONE 1
#define STRATEGY_TWO 2
#define STRATEGY_THREE 3

class Individual {
public:
	int		_x_dim;
	double 	*_x;
	double	_fit_val;
	
	~Individual() {
		
		//cout << "Indivial delete" << endl;
		if ( _x != NULL ) {
			free(_x);
			_x = NULL;
		}
	}
	
	Individual() {
		_x = NULL;		
	}
	
	Individual(int x_dim) : _x_dim(x_dim) {
		_x = (double *) malloc ( sizeof(double) * x_dim);
		if ( NULL == _x ) {
			cerr << "Error when malloc indivual x values" << endl;
			exit(0);
		}
	}
	
	void init_indi(int x_dim) {
		if ( NULL == _x ) {
			_x_dim = x_dim;
			_x = (double *) malloc ( sizeof(double) * x_dim);
		
			if ( NULL == _x ) {
				cerr << "Error when malloc indivual x values" << endl;
				exit(0);
			}
		}
	}
};


class Population {
	
private:
	int		_np;
	int		_dim;
	int		_best_ind_index;

public:
	
	// definition for individual
	Individual* 	_inds;	
	Population() {}
	Population( int dim , int np ) : _dim (dim), _np(np) {
		_inds = new Individual[np];
		
		for ( int j = 0; j < _np; j ++) {
			_inds[j]._x_dim = _dim;
			_inds[j]._x = ( double * ) malloc ( sizeof(double) * _dim);
			if ( NULL == _inds[j]._x ) {
				cerr << "Error when init the populations!" << endl;
				exit(0);
			}
		}
		
		if ( _inds == NULL ) {
			cerr << "Error when init the space for indivuals!" << endl;
			exit(0);
		}
	}
	
	~ Population() {
		if ( NULL != _inds ) {
			delete[] _inds;
			_inds = NULL;
		}
	}
	
};


class IDE {
	
public:
	
	//	dimension & number of population
	int 		_dim;
	int 		_np;
	int			_fe;
	
	//	global optimial data
	double		_global_opt_val;
	int			_global_opt_idx;
	
	//	three kinds of population
	Population 	*_cur_pop;
	Population 	*_mu_pop;
	Population 	*_lab_pop;
	
	// IFUNC 
	IFUNC		*_func;
	
	// parameters
	double	F;
	double	CR;
	int		MAX_FE;	
	
	IDE() {}
	IDE( int dim, int np, int func_type, double global_opt,  double opt_val ) {
			
		_cur_pop 		= new Population(dim, np);
		_mu_pop 		= new Population(dim, np);
		_lab_pop		= new Population(dim, np);
		_dim			= dim;
		_np				= np;
		_global_opt_val = global_opt;
		_fe				= 0;
		_func			= FuncFactory::get_instance()->create(func_type, dim, opt_val);
		if ( NULL == _func ) {
			cerr << " Error when create function instance!" << endl;
			exit(0);	
		}
	}
	
	~IDE() {
		
		
		if ( _cur_pop != NULL ) {
			delete _cur_pop;
			_cur_pop = NULL;
		}
		
		if ( _mu_pop != NULL ) {
			delete _mu_pop;
			_mu_pop = NULL;
		}
		
		if ( _lab_pop != NULL ) {
			delete _lab_pop;
			_lab_pop = NULL;
		}
		
		if ( NULL != _func ) {
			delete _func;
			_func = NULL;
		}
		
	}
	
	// set max 
	void _set_fes(int max_fes) {
		MAX_FE = max_fes;
	}
	// set f
	void _set_f(double f) {
		F = f;
	}
	// set cr
	void _set_cr(double cr) {
		CR = cr;
	}
	
	// calculate the fitness value	
	double _fitness(const Individual &ind) {
		// _fe += 1;
		return _func->_fitness(ind._x);		
	}
	
	// update global optimisation values
	void _update_global_opt() {
		for ( int i = 0; i < _np; i ++) {		
			double cur_fit_val = _cur_pop->_inds[i]._fit_val ;
			if ( _global_opt_val > cur_fit_val ) {
				_global_opt_val = cur_fit_val;
				_global_opt_idx = i;
			}
		}
	}
	
	// init population & parameters
	void	_init_population() {
		
		_global_opt_idx = 0;
		_global_opt_val = INT_MAX;	
		for ( int i = 0; i < _np; i ++ ) {
			for ( int j = 0; j < _dim; j ++) {
			
				_cur_pop->_inds[i]._x[j] 	= 	_func->_x_left_bound[j] + 
					( rand() / (double) RAND_MAX ) * (_func->_x_right_bound[j] - _func->_x_left_bound[j]);
					
			}
			_cur_pop->_inds[i]._fit_val = _fitness(_cur_pop->_inds[i]);
		}
		
	//	cout << endl;
	}
	// de method
	virtual double	_de(int lock) {	}
	// virtual methods needed to be override
	virtual void _mutation(int ind_index) {}
   	virtual void _cross_over(int ind_index) {}
	virtual void _selection(int ind_index) {}
};

	
#endif
