#ifndef ConvNeuralNetwork_H_
#define ConvNeuralNetwork_H_

#include <iostream>
#include <vector>
#include <fstream>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "layer.h"

using namespace std;

#define D 28 * 28
#define ON 10

class ConvNeuralNetwork {


public:
	vector<Layer*> 	_layers;	// 层
	int 			_param_cnt;	// 参数数量 2204
	double			**_x;
	int				**_y;
	double			**_t_x;
	int				**_t_y;
	
	int				_train_sample_cnt;
	int				_test_sample_cnt;
	
	ConvNeuralNetwork() {}
	
	ConvNeuralNetwork( int param_cnt, int train_sample_cnt, int test_sample_cnt) :
	   	_param_cnt(param_cnt),
   		_train_sample_cnt(train_sample_cnt),
		_test_sample_cnt(test_sample_cnt) {
		
		_x = new double*[_train_sample_cnt];
		if ( NULL == _x ) {
			cerr << "[ERROR] bad alloc for _x in ConvNeuralNetwork !" << endl;
			exit (0);
		}
		
		_y = new int*[_train_sample_cnt];
		if ( NULL == _y ) {
			cerr << "[ERROR] bad alloc for _y in ConvNeuralNetwork !" << endl;
			exit (0);
		}
		
		for ( int i = 0; i < _train_sample_cnt; ++i) {
			_x[i] = new double[D];
			_y[i] = new int[ON];
			
			if ( NULL == _x[i] ) {
				cerr << "[ERROR] bad alloc for _x[i] in ConvNeuralNetwork !" << endl;
				exit (0);
			}
			
			if ( NULL == _y[i] ) {
				cerr << "[ERROR] bad alloc for _y[i] in ConvNeuralNetwork !" << endl;
				exit (0);
			}
			
		}
		
		_t_x = new double*[_test_sample_cnt];
		
		if ( NULL == _t_x ) {
			cerr << "[ERROR] bad alloc for _t_x in ConvNeuralNetwork !" << endl;
			exit (0);
		}
		
		_t_y = new int*[_test_sample_cnt];
		if ( NULL == _t_y ) {
			cerr << "[ERROR] bad alloc for _t_y in ConvNeuralNetwork !" << endl;
			exit (0);
		}
		
		for ( int i = 0; i < _test_sample_cnt; ++i) {
			_t_x[i] = new double[D];
			_t_y[i] = new int[ON];
			
			if ( NULL == _t_x[i] ) {
				cerr << "[ERROR] bad alloc for _t_x[i] in ConvNeuralNetwork !" << endl;
				exit (0);
			}
			
			if ( NULL == _t_y[i] ) {
				cerr << "[ERROR] bad alloc for _t_y[i] in ConvNeuralNetwork !" << endl;
				exit (0);
			}
			
		}
		
	}	
	// 将卷积神经网络的卷积核、偏置、全连接层权值转
	// 化为差分演化算法个体的编码值，主要是卷积
	void 	_transfer_to_dev(double *a);
	// 将长度为len的个体的编码值解码为卷积神经网络的
	// 卷积核、偏置以及全连接层权值
	void 	_get_from_dev(const double *a);
	// 增加层
	void 	_add_layer(Layer* &layer);
	// 给定一个输入图像特征(v保存的是转化一维的图像特征),计算输出
	double*	_calculate(double *v);
	// 给定一个输入图像特征以及其标签(具体对应的数字的编码)，给定网络的计算误差
	double	_cost_val_sig(double *v, int *y);
	// 加载训练数据
	void	_load_train_data();
	// 加载测试数据
	void	_load_test_data();
	// 网络初始化
	void	_init_net();
	// 测试
	void	_test();
	
	// 使用BP进行训练
	// void train();
};

#endif
