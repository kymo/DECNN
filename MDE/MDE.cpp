
/* FileName: MDE.cpp */

#include "MDE.h"


bool cmp(const Individual &first, const Individual & second) {
	return first._fit_val < second._fit_val;
}


MDE::~MDE() {
}



void MDE::_mutation( int ind_index ) {
	
	// 	find r1, r2, r3 which r1 != r2 != r3 != i
	int r1, r2, r3;
	
	do { r1 = rand() % _np; } while ( r1 == ind_index ) ;
	
	do { r2 = rand() % _np; } while ( r2 == ind_index || r2 == r1 );
	
	do { r3 = rand() % _np; } while ( r3 == ind_index || r3 == r2 || r3 == r1 ) ;
	
	for ( int j = 0; j < _dim; j ++) {
		
		(_mu_pop->_inds[ind_index])._x[j] = _cur_pop->_inds[r1]._x[j] + 
										  (_cur_pop->_inds[r2]._x[j] - _cur_pop->_inds[r3]._x[j]) * F;
		
		if ( _mu_pop->_inds[ind_index]._x[j] > _func->_x_right_bound[j] || 
				_mu_pop->_inds[ind_index]._x[j] < _func->_x_left_bound[j] ) {
			_mu_pop->_inds[ind_index]._x[j] = _cur_pop->_inds[ind_index]._x[j];
		}
		
	}
}


void MDE::_cross_over( int ind_index ) {
	
	int chose = rand() % _dim;
	for ( int j = 0; j < _dim; j ++) {
		double rate =  ( rand() / (double) RAND_MAX );
		if ( rate < CR || j == chose ) {
			_lab_pop->_inds[ind_index]._x[j] = _mu_pop->_inds[ind_index]._x[j];
		} else {
			_lab_pop->_inds[ind_index]._x[j] = _cur_pop->_inds[ind_index]._x[j];
		}
	}
}

/*
void MDE::_selection( int ind_index ) {
		
	int i;
	
	double fit_cur_pop = _fitness(_cur_pop->_inds[ind_index]);
	double fit_lab_pop = _fitness(_lab_pop->_inds[ind_index]);
	
	Individual tmp_ind(_dim);
	for ( i = 0; i < _dim; i ++) {
		
		tmp_ind._x[i] = (_func->_x_right_bound[i] + _func->_x_left_bound[i]) 
			- _cur_pop->_inds[ind_index]._x[i];	
		
	}
	double val = _fitness(tmp_ind);
	
	Individual tmp_ind_2(_dim);
	
	for ( i = 0; i < _dim; i ++) {
		tmp_ind_2._x[i] = (_func->_x_right_bound[i] + _func->_x_left_bound[i]) 
			- _mu_pop->_inds[ind_index]._x[i];	
	}
	
	double val_2 = _fitness(tmp_ind_2);
	
	_cur_pop->_inds[ind_index]._fit_val = fit_cur_pop;
	
	_lab_pop->_inds[ind_index]._fit_val = fit_lab_pop;

	Individual tmp_ind_best(_dim);
	
	double min_val = min(val, min(val_2, fit_lab_pop));
	
	if ( min_val < fit_cur_pop ) {
		
		if ( val < val_2 ) {
			for ( int i = 0; i < _dim; i ++) {
				tmp_ind_best._x[i] = tmp_ind._x[i];
			}
		} else {
			for ( int i = 0; i < _dim; i ++) {
				tmp_ind_best._x[i] = tmp_ind_2._x[i];
			}
		}
		
		if ( min(val, val_2) > fit_lab_pop ) {
			for ( int i = 0; i < _dim; i ++) {
				tmp_ind_best._x[i] = _lab_pop->_inds[ind_index]._x[i];
			}
		}
		for ( int i = 0; i < _dim; i ++) {
			_cur_pop->_inds[ind_index]._x[i] = tmp_ind_best._x[i];
		}
	}
}

*/
void MDE::_selection( int ind_index ) {
		
	double fit_cur_pop = _cur_pop->_inds[ind_index]._fit_val;
	double fit_lab_pop = _fitness(_lab_pop->_inds[ind_index]);
	//_lab_pop->_inds[ind_index]._fit_val = fit_lab_pop;
	if ( fit_cur_pop > fit_lab_pop ) {
		for ( int j = 0; j < _dim; j ++) {
			_cur_pop->_inds[ind_index]._x[j] = _lab_pop->_inds[ind_index]._x[j];
		}
		_cur_pop->_inds[ind_index]._fit_val = fit_lab_pop;
	}
	
}

/*
void MDE::_selection( int ind_index ) {
	
	ALPHA = 1.9;
	double fit_cur_pop = _fitness(_cur_pop->_inds[ind_index]);
	double fit_lab_pop = _fitness(_lab_pop->_inds[ind_index]);
	_cur_pop->_inds[ind_index]._fit_val = fit_cur_pop;
	_lab_pop->_inds[ind_index]._fit_val = fit_lab_pop;
	
	
	// 增加局部搜索能力
	Individual *new_cur_ind = new Individual(_dim);
	
	for ( int i = 0; i < _dim; i ++) {
		new_cur_ind->_x[i] = _cur_pop->_inds[ind_index]._x[i];
	}
	
	double max_val = (double) INT_MAX;
	int		max_index = 0;
	double vec = 0.0, tmp_val = 0.0;
	
	for ( int i = 0; i < _dim; i ++) {
		vec = _cur_pop->_inds[ind_index]._x[i] - _last_pop->_inds[ind_index]._x[i];
		new_cur_ind->_x[i] +=  ALPHA * vec;
	}
	
	double new_cur_ind_val = _fitness(*new_cur_ind);
	
//	cout << fit_lab_pop << " " << new_cur_ind_val << " " << fit_lab_pop << endl;
	
	if ( min(fit_lab_pop, new_cur_ind_val ) < fit_cur_pop ) {
		
		if ( fit_lab_pop < new_cur_ind_val ) {
			for ( int j = 0; j < _dim;j ++) {
				_cur_pop->_inds[ind_index]._x[j] = _lab_pop->_inds[ind_index]._x[j];
			}
		} else {
			for ( int j = 0; j < _dim;j ++) {
				_cur_pop->_inds[ind_index]._x[j] = new_cur_ind->_x[j];
			}
		}
		
	}
	 
	for ( int i = 0; i < _dim; i ++) {
		_last_pop->_inds[ind_index]._x[i] = _cur_pop->_inds[ind_index]._x[i];
	}
	
	//if ( ind_index == 23 ) {
	//for ( int i = 0; i < 10; i ++) {
			//cout <<  _last_pop->_inds[ind_index]._x[i] << " ";
		//}
		//cout << endl;
	//}
	
	if ( NULL != new_cur_ind ) {
		delete new_cur_ind;
		new_cur_ind = NULL;
	}
}
*/
void MDE::_set_or(double or_val) {
	
	OR = or_val;

}


double MDE::_de(int lock) {
	
	srand( (unsigned)time( NULL ) );
	
	// init population
	_init_population();
	
	_update_global_opt();
	_fe = 0;
	Individual tmp(_dim);
	
	while (_fe < MAX_FE) {
		
		// mutation & cross over
		for ( int j = 0; j < _np; j ++) {
			_mutation(j);
		}	
		
		for ( int j = 0; j < _np; j ++) {
			
			
			for ( int k = 0; k < _dim; k ++) {
				double t = (fabs(_mu_pop->_inds[j]._x[k] - 0.1 * _cur_pop->_inds[j]._x[j]) + 1.0e-323) / 
					(1.0e-323 + fabs(_cur_pop->_inds[j]._x[j])) ;
				tmp._x[k] =  1 / t * _mu_pop->_inds[j]._x[k];
				//tmp._x[k] = (rb[k] + lb[k]) - 1 / t * _mu_pop->_inds[j]._x[k];
				if ( tmp._x[k] > _func->_x_right_bound[k] || 
						tmp._x[k] < _func->_x_left_bound[k] ) {
					tmp._x[k] = _mu_pop->_inds[j]._x[k];
				}
			}
			double rate = rand() * 1.0 / RAND_MAX;
			if (rate < OR) {
				for ( int k = 0; k < _dim; k ++) {
					_mu_pop->_inds[j]._x[k] = tmp._x[k];
				}
			}
		}
		
		
		for ( int j = 0; j < _np; j ++) {
			_cross_over(j);	
		}
		
		// selection by greedy strategy
		for ( int j = 0; j < _np; j ++) {
			_selection(j);
		}
		
		_update_global_opt();
		_fe += _np;
		if ( ! lock ) {
			cout << _global_opt_val << endl;
		}
		
	}
		
		
	_update_global_opt();
	return _global_opt_val;
}


