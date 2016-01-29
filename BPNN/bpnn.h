/*FileName: bpnn.h */
#ifndef BPNN_H_
#define BPNN_H_

#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <fstream>
#include <vector>
#include <cstdlib>
#include <cstdio>
#include <string.h>
#include <iostream>

using namespace std;

#define D 28 * 28
#define ON 10

class BPNN {

public:
	int			_i_neuo_cnt;
	int			_h_neuo_cnt;
	int			_o_neuo_cnt;

	double**	_w_i_h;
	
	double**	_w_h_o;
	
	double*		_h_bias;
	
	double*		_o_bias;
	
	double			**_x;
	int				**_y;
	double			**_t_x;
	int				**_t_y;
	
	int				_train_sample_cnt;
	int				_test_sample_cnt;

	double		*_h_v;
	double		*_o_v;
	
	BPNN() {}
	BPNN( int i_neuo_cnt, 
			int h_neuo_cnt,
			int o_neuo_cnt,
			int train_sample_cnt,
			int test_sample_cnt)  {
		_i_neuo_cnt = i_neuo_cnt;
		_h_neuo_cnt = h_neuo_cnt;
		_o_neuo_cnt = o_neuo_cnt;
		_train_sample_cnt = train_sample_cnt;
		_test_sample_cnt = test_sample_cnt;

		_w_i_h = new double*[_i_neuo_cnt];
		for ( int i = 0; i < _i_neuo_cnt; i ++) {
			_w_i_h[i] = new double[_h_neuo_cnt];
		}
		_w_h_o = new double*[_h_neuo_cnt];
		for ( int i = 0; i < _h_neuo_cnt; i ++) {
			_w_h_o[i] = new double[_o_neuo_cnt];
		}
		_h_bias = new double[_h_neuo_cnt];
		_o_bias = new double[_o_neuo_cnt];
		
		_x = new double*[_train_sample_cnt];
		_y = new int*[_train_sample_cnt];
		
		for ( int i = 0; i < _train_sample_cnt; ++i) {
			_x[i] = new double[D];
			_y[i] = new int[ON];
		}
		
		_t_x = new double*[_test_sample_cnt];
		_t_y = new int*[_test_sample_cnt];
		
		for ( int i = 0; i < _test_sample_cnt; ++i) {
			_t_x[i] = new double[D];
			_t_y[i] = new int[ON];
		}		
		_h_v = new double[_h_neuo_cnt];
		_o_v = new double[_o_neuo_cnt];
	}

	void _get_from_dev(const double*x) ;		

	double* _calculate(double *v);
	double _cost_val_sig(double *v, int *y);

	void _load_train_data();
	
	void _load_test_data();

	void _test();

};

#endif
