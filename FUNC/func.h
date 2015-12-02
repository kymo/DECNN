#ifndef FUNC_H
#define FUNC_H

#include <iostream>
#include <string>
#include <stdio.h>
using namespace std;


#define FUNC_ONE_NAME "FUNCTION_ONE"

enum func_type {
	ONE = 1,
	TWO,
	THREE,
	FOR,
	FIVE
} ;

class IFUNC {

	
public:
	int		_dim;
	double 	_opt_val;	
	string 	_func_name;
	double	*_x_left_bound;
	double 	*_x_right_bound;

	
	IFUNC() {}
	
	IFUNC(string func_name, int dim, double opt_val) : _func_name(func_name),
		_dim(dim), _opt_val(opt_val) {
		
		_x_left_bound 	= new double[_dim];
		_x_right_bound 	= new double[_dim];
		
	}	
	
	virtual ~IFUNC() {
		
		if ( NULL != _x_left_bound) {
			delete _x_left_bound;
			_x_left_bound = NULL;
		}
	
		if ( NULL != _x_right_bound ) {
			delete _x_right_bound;
			_x_right_bound = NULL;
		}
	
	}
	
	virtual double _fitness(const double *x) const = 0;

};




// definition for function :
// f(x_i) = 

class FUNC_ONE : public IFUNC {
	
public:
	
	FUNC_ONE() {}
	virtual ~FUNC_ONE() {}
	FUNC_ONE(int dim, double opt_val) : IFUNC(FUNC_ONE_NAME,
			dim,
			opt_val) {
		
		for ( int i = 0; i < _dim; i++ ) {
			_x_left_bound[i] = -500;
			_x_right_bound[i] = 500;
		}
		
	}
	
	double _fitness(const double *x) const {

		double ret_val = 0.0;
		for ( int j = 0; j < _dim; j ++) {
			ret_val += x[j] * x[j];
		}
		return ret_val;

	}
	
};


class FuncFactory {
private:
	FuncFactory() {}
public:
	
	static FuncFactory* get_instance() {
		static FuncFactory* instance;
		if ( instance == NULL ) {
			instance = new FuncFactory();
		}
		return instance;
		
	}
	
	IFUNC*	create(int func_type, int dim, double opt_val) {
		switch(func_type) {
			case ONE:
				return new FUNC_ONE(dim, opt_val);
			default:
				break;
		}	
	}
};

#endif



