/* FileName: layer.h */

#ifndef _LAYER_H_
#define _LAYER_H_

#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "util.h"

using namespace std;

enum layer_type {
	INPUT = 0,
	CONV ,
	POOL ,
	FULLI, 
	HIDDEN ,
	OUTPUT ,
};

class FeatureMap {

public:
	double		**_data;
	int	   		_c;
	int	   		_r;
	
	FeatureMap() {}
	
	void _set_size(int c, int r) {
		_c = c;
		_r = r;
		_data = new double*[_r];
		if ( NULL == _data ) {
			cerr  << "Error when allocate memory for FeatureMap!" << endl;
			exit (0);
		}
		for ( int i = 0; i < r; i ++) {
			_data[i] = new double[c];
			if ( NULL == _data[i] ) {
				cerr  << "Error when allocate memory for FeatureMap!" << endl;
				exit (0);
			}
		}
	}
	
};

class Layer {
public:
	FeatureMap*	_o_fmap;				// 	输出FeatureMap
	int			_o_fmap_cnt;			//	输出特征图数目
	int			_i_fmap_cnt;			//	输入特征图数目
	int			_layer_type;			//	层类型
	double		*_bias;					// 	输出特征图的偏置
	int			_o_fmap_r;				// 	输出FM的行
	int			_o_fmap_c;				// 	输出FeatureMap的列
	
	
	/* FOR CONVOLUTION LAYER */
	int			_kernel_cnt;			// 卷积核数量
	int			_kernel_c;				// 卷积核行数
	int			_kernel_r;				// 卷积核列数
	double		*** _kernel;			// 卷积核
	int			**_connect_graph;		// 输入FeatureMap和输出FeatureMap的连接图谱
	/* FOR POOLING LAYER */
	int			_pool_r;
	int 		_pool_c;
	/* FOR FULLIN LAYER */
	double  	*_full_input_v;
	/* FOR OUTPUT LAYER */
	
	int			_i_neuo_cnt;
	int 		_o_neuo_cnt;			// 输出神经元数量
	double 		**_w;					// 输出层全连接权值
	double  	*_o;					// 输出
	

public:
	Layer() {}
	Layer(int i_fmap_cnt, int o_fmap_cnt, int o_fmap_r, int o_fmap_c) {
		_o_fmap_cnt = o_fmap_cnt;
		_i_fmap_cnt = i_fmap_cnt;
		_o_fmap_r	= o_fmap_r;
		_o_fmap_c	= o_fmap_c;
		_o_fmap		= new FeatureMap[_o_fmap_cnt];
		for ( int i = 0; i < _o_fmap_cnt; i ++) {
			_o_fmap[i]._set_size(_o_fmap_r, _o_fmap_c);
		}
		if ( NULL == _o_fmap ) {
			cerr << "[ERROR] bad alloc for _io_con_index in line:" << __LINE__ << " in file layer.h" << endl;
			exit(0);
		}
	}
   	~Layer() {
		if ( NULL != _o_fmap ) {
			delete[] _o_fmap;
			_o_fmap = NULL;
		}
	}
	FeatureMap*& _get_o_fmap() { return _o_fmap; }
	int			 _get_o_fmap_cnt() const { return _o_fmap_cnt; }
	int			 _get_i_fmap_cnt() const { return _i_fmap_cnt; }
	
	/* FOR CONVOLUTION LAYER */
	virtual void		_init_connect_type(int** connect_graph) {}	// 初始化连接方式
	
	/* FOR INPUT LAYER */
	virtual void 		_set_input_fmap(double *val) {}
	
	
	virtual void		_forward( Layer*& prior_layer) {}
	
};

class ConvolutionLayer : public Layer {
	
public:	
	~ConvolutionLayer() {}
	ConvolutionLayer(
			int kernel_r, 
			int kernel_c,
			int o_fmap_r,
			int o_fmap_c,
			int o_fmap_cnt,
			int i_fmap_cnt ) : Layer(i_fmap_cnt, o_fmap_cnt, o_fmap_r, o_fmap_c) {
		_kernel_cnt 	= i_fmap_cnt * o_fmap_cnt; 
		_kernel_c 		= kernel_c;
		_kernel_r 		= kernel_r;
		_layer_type		= CONV;
		_kernel = new double**[_kernel_cnt];
		if ( NULL == _kernel ) {
			cerr << "[ERROR] bad alloc for _kernel in line:" << __LINE__ << " in file layer.h" << endl;
			exit(0);
		}
		for ( int i = 0; i < _kernel_cnt; i ++) {
			_kernel[i] = new double*[_kernel_r];
			if ( NULL == _kernel[i] ) {
				cerr << "[ERROR] bad alloc for _kernel[i] in line:" << __LINE__ << " in file layer.h" << endl;
				exit(0);
			}
			for ( int j = 0; j < _kernel_r; j ++) {
				_kernel[i][j] = new double[_kernel_c]; 
				if ( NULL == _kernel[i][j] ) {
					cerr << "[ERROR] bad alloc for _kernel[i][j] in line:" << __LINE__ << " in file layer.h" << endl;
					exit(0);
				}
			}
		}
		
		_connect_graph = new int*[_o_fmap_cnt];
		if ( NULL == _connect_graph ) {
			cerr << "[ERROR] bad alloc for _connect_graph in line:" << __LINE__ << " in file layer.h" << endl;
			exit(0);
		}
		
		for ( int i = 0; i < _o_fmap_cnt; i ++) {
			_connect_graph[i] = new int[_i_fmap_cnt];
			if ( NULL == _connect_graph[i] ) {
				cerr << "[ERROR] bad alloc for _connect_graph in line:" << __LINE__ << " in file layer.h" << endl;
				exit(0);
			}
		}
		
		_bias = new double[_o_fmap_cnt];
		if ( NULL == _bias ) {
			cerr << "[ERROR] bad alloc for _bias in line:" << __LINE__ << " in file layer.h" << endl;
			exit(0);
		}
	}
	
	void		_init_connect_type(int** connect_graph) ;	// 初始化连接方式
	void		_forward( Layer*& prior_layer) ;
	void 		_set_input_fmap(double *val) {}
		
};

class InputLayer : public Layer {

public:
	
	InputLayer(	
		int o_fmap_r,
		int o_fmap_c,
		int o_fmap_cnt,
		int i_fmap_cnt) : Layer(i_fmap_cnt, o_fmap_cnt, o_fmap_r, o_fmap_c) {
		_layer_type 	= INPUT;
		
	}
	~InputLayer() {}
	
	void _set_input_fmap(double *val) {
		int pt = 0;
		for ( int fcnt = 0; fcnt < _o_fmap_cnt; fcnt ++) {
			for ( int i = 0; i < _o_fmap_r; i ++) {
				for ( int j = 0; j < _o_fmap_c; j ++) {
					_o_fmap[fcnt]._data[i][j] = val[pt ++];
				}
			}
		}
	}
	
	void		_init_connect_type(int** connect_graph) {}	// 初始化连接方式
	void 		_forward( Layer*& prior_layer) {}
};


class PoolingLayer : public Layer {
public:
	PoolingLayer( int pool_r, 
		int pool_c,
		int o_fmap_r,
		int o_fmap_c,
		int o_fmap_cnt,
		int i_fmap_cnt) : Layer(i_fmap_cnt, o_fmap_cnt, o_fmap_r, o_fmap_c) {
		_layer_type = POOL;
		_pool_r 	= pool_r;
		_pool_c		= pool_c;
	}
	~PoolingLayer() {}
	void 		_forward( Layer*& prior_layer) ;
	void		_init_connect_type(int** connect_graph) {}	// 初始化连接方式
	void 		_set_input_fmap(double *val) {}
	
};

// 全连接层的输入层
class FullInputLayer : public Layer {
public:
	FullInputLayer() {
		_layer_type 	= FULLI;
	}
	~FullInputLayer() {}
	void 		_forward( Layer*& prior_layer) ;
	void		_init_connect_type(int** connect_graph) {}	// 初始化连接方式
	void 		_set_input_fmap(double *val) {}
};

class OutputLayer : public Layer {
public:
	OutputLayer(int i_neuo_cnt,
		int o_neuo_cnt) {
		_i_neuo_cnt = i_neuo_cnt;
		_o_neuo_cnt = o_neuo_cnt;
		_o = new double[_o_neuo_cnt];
		if ( NULL == _o ) {
			cerr << "[ERROR] bad alloc for _o in line:" << __LINE__ << " in file layer.h" << endl;
			exit(0);
		}
		_w = new double*[_i_neuo_cnt];
		_layer_type	= OUTPUT;
		if ( NULL == _w ) {
			cerr << "[ERROR] bad alloc for _w in line:" << __LINE__ << " in file layer.h" << endl;
			exit(0);
		}
		for ( int i = 0; i < _i_neuo_cnt; i ++) {
			_w[i] = new double[_o_neuo_cnt];
			if ( NULL == _w[i] ) {
				cerr << "[ERROR] bad alloc for _w[i] in line:" << __LINE__ << " in file layer.h" << endl;
				exit(0);
			}
		}
		_bias = new double[_o_neuo_cnt];
		if ( NULL == _bias ) {
			cerr << "[ERROR] bad alloc for _b in line:" << __LINE__ << " in file layer.h" << endl;
			exit(0);
		}
	}
	
	~ OutputLayer() {}
	
	void 		_forward( Layer*& prior_layer) ;
	void		_init_connect_type(int** connect_graph) {}	// 初始化连接方式
	void 		_set_input_fmap(double *val) {}
	
};

#endif
