/* FileName : layer.cpp */
#include "layer.h"

void ConvolutionLayer::_init_connect_type(int** connect_graph) {
	
	for ( int i = 0; i < _o_fmap_cnt; i ++) {
		for ( int j = 0; j < _i_fmap_cnt; j ++) {
			_connect_graph[i][j] = *((int*)connect_graph + _i_fmap_cnt * i + j);
		}
	}
}
	
/*
void ConvolutionLayer::_init_kernel() {
	srand((unsigned)time(NULL));
	for ( int i = 0; i < _o_fmap_cnt; i ++) {
		for ( int j = 0; j < _i_fmap_cnt; j ++) {
			if ( _connect_graph[i][j] ) {
				for ( int k = 0; k < _kernel_r; k ++) {
					for ( int l = 0; l < _kernel_c; l ++ ) {
						_kernel[i * _o_fmap_cnt + j][k][l] = rand() * 1.0 / (double) RAND_MAX;
					}
				}
			}
		}
	}
}

void ConvolutionLayer::_init_bias() {
	for ( int i = 0; i < _o_fmap_cnt; i ++) {
		_bias[i] = rand() * 1.0 / (double) RAND_MAX;
	}
}
*/
void ConvolutionLayer::_forward( Layer*& prior_layer) {

	// for each output feature map	
	for ( int i = 0; i < _o_fmap_cnt; i ++) {
		
		// init the value of the i-th output feature map
		for ( int j = 0; j < _o_fmap_r; j ++) {
			for ( int k = 0; k < _o_fmap_c; k ++) {
				_o_fmap[i]._data[j][k] = 0.0;
			}
		}
		
		// each output feature map is connected with several input feature map
		// defined in the _connect_graph by several convolutional kernels
		
		for ( int j = 0; j < _i_fmap_cnt; j ++) {
			
			if ( ! _connect_graph[i][j]) {
				continue;
			}
			
			int	kernel_id = i * _i_fmap_cnt + j;
			
			for ( int k = 0; k < _o_fmap_r; k ++) {
				for ( int l = 0; l < _o_fmap_c; l ++) {
					
					double vl = 0.0;
					for ( int kr = 0; kr < _kernel_r; kr ++) {
						for ( int kc = 0; kc < _kernel_c; kc ++) {
							vl += _kernel[kernel_id][kr][kc] * prior_layer->_o_fmap[j]._data[k + kr][l + kc];
						}
					}
					_o_fmap[i]._data[k][l] += vl;
				}
			}
		}
		
		for ( int k = 0; k < _o_fmap_r; k ++) {
			for ( int l = 0; l < _o_fmap_c; l ++) {
				_o_fmap[i]._data[k][l] = sigm(_o_fmap[i]._data[k][l]) + _bias[i];		
				//cout << _o_fmap[i]._data[k][l] << " ~ " ;
			}
		}
	}
}

void PoolingLayer::_forward( Layer*& prior_layer) {
	for ( int i = 0; i < _o_fmap_cnt; i ++) {
		for ( int j = 0; j < _o_fmap_r; j ++) {
			for ( int k = 0; k < _o_fmap_c; k ++) {
				double vl = 0.0;
				for ( int pr = 0; pr < _pool_r; pr ++) {
					for ( int pc = 0; pc < _pool_c; pc ++) {
						vl += prior_layer->_o_fmap[i]._data[j * _pool_r + pr][k * _pool_c + pc];
					}
				}
				_o_fmap[i]._data[j][k] = vl / (_pool_r * _pool_c);
			}
		}	
	}
	
}

void FullInputLayer::_forward( Layer*& prior_layer) {
	_o_neuo_cnt 	= prior_layer->_o_fmap_cnt * prior_layer->_o_fmap_r * prior_layer->_o_fmap_c;
	if ( NULL == _full_input_v ) {

		_full_input_v 	= new double[_o_neuo_cnt];
	}
	int cnt = 0;
	for ( int i = 0; i < prior_layer->_o_fmap_cnt; i ++) {
		for ( int j = 0; j < prior_layer->_o_fmap_r; j ++) {
			for ( int k = 0; k < prior_layer->_o_fmap_c; k ++) {
				_full_input_v[cnt ++] = prior_layer->_o_fmap[i]._data[j][k];
			}
		}
	}
}


void OutputLayer::_forward( Layer*& prior_layer) {
	if ( prior_layer->_layer_type != FULLI ) {
		cerr << "[ERROR] The layer before output Layer  must be full input layer !" << endl;
		exit(0);
	}
	
	for ( int i = 0; i < _o_neuo_cnt; i ++) {
		double v = 0.0;
		for ( int j = 0; j < prior_layer->_o_neuo_cnt; j++) {
			v += prior_layer->_full_input_v[j] * _w[j][i];
		}
		v += _bias[i];
		_o[i] = sigm(v);
	}
}
