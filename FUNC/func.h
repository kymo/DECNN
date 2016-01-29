#ifndef FUNC_H
#define FUNC_H

#include <iostream>
#include <string>
#include <stdio.h>
#include <math.h>
#include "cnn.h"
#include "bpnn.h"

using namespace std;


#define FUNC_ONE_NAME "Sphere"
#define FUNC_TWO_NAME "Schwefel 2.22"
#define FUNC_THREE_NAME "Schwefel 1.2"
#define FUNC_FOUR_NAME "Schwefel 2.21"
#define FUNC_FIVE_NAME "Rosenbrock"
#define FUNC_SIX_NAME "Step"
#define FUNC_SEVEN_NAME "Quartic"
#define FUNC_EIGHT_NAME "Schwefel"
#define FUNC_NINE_NAME "Rastrigin"
#define FUNC_TEN_NAME "Ackley"
#define FUNC_ELEVEN_NAME "Griewank"
#define FUNC_TWELVE_NAME "Penalized Function 1"
#define FUNC_THIRTEEN_NAME "Penalized Function 2"
#define FUNC_CEC_ONE_NAME "CEC Shpere"

#define CNN_NAME "CNN"
#define BPNN_NAME "BPNN"

enum func_type {
	ONE = 1,TWO,THREE,FOUR,
	FIVE,SIX,SEVEN,EIGHT,
	NINE,TEN,ELEVEN,TWELVE,THIRTEEN,FOURTEEN,CNN,BPNNS
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
			_x_left_bound[i] = -100;
			_x_right_bound[i] = 100;
		}
		
	}
	
	double _fitness(const double *x) const {

		double ret_val = 0.0;
		double vlas[100] = {-3.9311900e+001,5.8899900e+001,-4.6322400e+001,-7.4651500e+001,-1.6799700e+001,-8.0544100e+001,-1.0593500e+001,2.4969400e+001,8.9838400e+001,9.1119000e+000,-1.0744300e+001,-2.7855800e+001,-1.2580600e+001,7.5930000e+000,7.4812700e+001,6.8495900e+001,-5.3429300e+001,7.8854400e+001,-6.8595700e+001,6.3743200e+001,3.1347000e+001,-3.7501600e+001,3.3892900e+001,-8.8804500e+001,-7.8771900e+001,-6.6494400e+001,4.4197200e+001,1.8383600e+001,2.6521200e+001,8.4472300e+001,3.9176900e+001,-6.1486300e+001,-2.5603800e+001,-8.1182900e+001,5.8695800e+001,-3.0838600e+001,-7.2672500e+001,8.9925700e+001,-1.5193400e+001,-4.3337000e+000,5.3430000e+000,1.0560300e+001,-7.7726800e+001,5.2085900e+001,4.0394400e+001,8.8332800e+001,-5.5830600e+001,1.3181000e+000,3.6025000e+001,-6.9927100e+001,-8.6279000e+000,-5.6894400e+001,8.5129600e+001,1.7673600e+001,6.1529000e+000,-1.7695700e+001,-5.8953700e+001,3.0356400e+001,1.5920700e+001,-1.8008200e+001,8.0641100e+001,-4.2391200e+001,7.6277600e+001,-5.0165200e+001,-7.3573600e+001,2.8336900e+001,-5.7990500e+001,-2.2732700e+001,5.2026900e+001,3.9259900e+001,1.0867900e+001,7.7820700e+001,6.6039500e+001,-5.0066700e+001,5.5706300e+001,7.3714100e+001,3.8529600e+001,-5.6786500e+001,-8.9647700e+001,3.7957600e+001,2.9472000e+001,-3.5464100e+001,-3.1786800e+001,7.7323500e+001,5.4790600e+001,-4.8279400e+001,7.4271400e+001,7.2610300e+001,6.2964000e+001,-1.4144600e+001,2.0492300e+001,4.6589700e+001,-8.3602100e+001,-4.6480900e+001,8.3737300e+001,-7.9661100e+001,2.4347900e+001,-1.7230300e+001,7.2340400e+001,-3.6402200e+001};
		double f_bias = -450;
		for ( int j = 0; j < _dim; j ++) {
			ret_val += (x[j]) * (x[j]  );
		}
		return ret_val ;

	}
	
};


class FUNC_TWO : public IFUNC {

public:
	FUNC_TWO() {}
	virtual ~FUNC_TWO() {}
	FUNC_TWO(int dim, double opt_val) : IFUNC(FUNC_TWO_NAME,
			dim,
			opt_val) {
		
		for ( int i = 0; i < _dim; i++ ) {
			_x_left_bound[i] = -10;
			_x_right_bound[i] = 10;
		}
		
	}
	
	double _fitness(const double *x) const {

		double ret_f_val = 0.0;
		double ret_s_val = 1.0;
		for ( int i = 0; i < _dim; i ++) {
			ret_f_val += fabs(x[i]);
			ret_s_val *= fabs(x[i]);
		}
		
		return ret_f_val + ret_s_val;

	}
	
};


class FUNC_THREE : public IFUNC {

public:
	FUNC_THREE() {}
	virtual ~FUNC_THREE() {}
	FUNC_THREE(int dim, double opt_val) : IFUNC(FUNC_THREE_NAME,
			dim,
			opt_val) {
		
		for ( int i = 0; i < _dim; i++ ) {
			_x_left_bound[i] = -100;
			_x_right_bound[i] = 100;
		}
		
	}
	
	double _fitness(const double *x) const {
		double ret_val = 0.0;
		for ( int i = 0; i < _dim; i ++) {
			double tmp_val = 0.0;
			for ( int j = 0; j <= i; j ++) {
				tmp_val += x[j];
			}
			ret_val += tmp_val * tmp_val;
		}
		return ret_val;
	}
	
};

class FUNC_FOUR : public IFUNC {

public:
	FUNC_FOUR() {}
	virtual ~FUNC_FOUR() {}
	FUNC_FOUR(int dim, double opt_val) : IFUNC(FUNC_FOUR_NAME,
			dim,
			opt_val) {
		
		for ( int i = 0; i < _dim; i++ ) {
			_x_left_bound[i] = -100;
			_x_right_bound[i] = 100;
		}
		
	}
	
	double _fitness(const double *x) const {
		double ret_val = 0.0;
		for ( int i = 0; i < _dim; i ++) {
			ret_val = max(ret_val, fabs(x[i]));
		}
		
		return ret_val;
		
	}
	
};


class FUNC_FIVE : public IFUNC {

public:
	FUNC_FIVE() {}
	virtual ~FUNC_FIVE() {}
	FUNC_FIVE(int dim, double opt_val) : IFUNC(FUNC_FIVE_NAME,
			dim,
			opt_val) {
		
		for ( int i = 0; i < _dim; i++ ) {
			_x_left_bound[i] = -30;
			_x_right_bound[i] = 30;
		}
		
	}
	
	double _fitness(const double *x) const {
		double ret_val = 0.0;
		for ( int i = 0; i < _dim - 1; i ++) {
			double val = x[i] * x[i] - x[i + 1];
			ret_val += val * val * 100 + (x[i] - 1) * (x[i] - 1);
		}
		return ret_val;
	}
	
};

class FUNC_SIX : public IFUNC {

public:
	FUNC_SIX() {}
	virtual ~FUNC_SIX() {}
	FUNC_SIX(int dim, double opt_val) : IFUNC(FUNC_SIX_NAME,
			dim,
			opt_val) {
		
		for ( int i = 0; i < _dim; i++ ) {
			_x_left_bound[i] = -100;
			_x_right_bound[i] = 100;
		}
		
	}
	
	double _fitness(const double *x) const {
		double ret_val = 0.0;
		for ( int i = 0; i < _dim; i ++) {
			int v = floor(x[i] + 0.5);
			ret_val += v * v;
		}
		return ret_val;
	}
	
};

class FUNC_SEVEN : public IFUNC {

public:
	FUNC_SEVEN() {}
	virtual ~FUNC_SEVEN() {}
	FUNC_SEVEN(int dim, double opt_val) : IFUNC(FUNC_SEVEN_NAME,
			dim,
			opt_val) {
		
		for ( int i = 0; i < _dim; i++ ) {
			_x_left_bound[i] = -1.28;
			_x_right_bound[i] = 1.28;
		}
		
	}
	
	double _fitness(const double *x) const {
		double ret_val = 0.0;
		
		for ( int i = 0; i < _dim; i ++) {
			
			ret_val += (i + 1) * x[i] * x[i] * x[i] * x[i];
		
		}
		
		double vl = ( rand() / (double) RAND_MAX );
		
		return ret_val + vl;
	
	}
	
};

class FUNC_EIGHT : public IFUNC {

public:
	FUNC_EIGHT() {}
	virtual ~FUNC_EIGHT() {}
	FUNC_EIGHT(int dim, double opt_val) : IFUNC(FUNC_EIGHT_NAME,
			dim,
			opt_val) {
		
		for ( int i = 0; i < _dim; i++ ) {
			_x_left_bound[i] = -500;
			_x_right_bound[i] = 500;
		}
		
	}
	
	double _fitness(const double *x) const {
		double ret_val = 0.0;
		for ( int i = 0; i < _dim; i ++) {
			ret_val += x[i] * sin(sqrt(fabs(x[i])));
		}
		return _dim * 418.9829 - ret_val;
	}
};


class FUNC_NINE : public IFUNC {

public:
	FUNC_NINE() {}
	virtual ~FUNC_NINE() {}
	FUNC_NINE(int dim, double opt_val) : IFUNC(FUNC_NINE_NAME,
			dim,
			opt_val) {
		
		for ( int i = 0; i < _dim; i++ ) {
			_x_left_bound[i] = -5.12;
			_x_right_bound[i] = 5.12;
		}
		
	}
	
	double _fitness(const double *x) const {
		double ret_val = 0.0;
		for ( int i = 0; i < _dim; i ++) {
			ret_val += x[i] * x[i] - 10 * cos(2 * M_PI * x[i]) + 10;
		}
		return ret_val;
	}
};

class FUNC_TEN : public IFUNC {

public:
	FUNC_TEN() {}
	virtual ~FUNC_TEN() {}
	FUNC_TEN(int dim, double opt_val) : IFUNC(FUNC_TEN_NAME,
			dim,
			opt_val) {
		
		for ( int i = 0; i < _dim; i++ ) {
			_x_left_bound[i] = -32;
			_x_right_bound[i] = 32;
		}
		
	}
	
	double _fitness(const double *x) const {
		double ret_val = 0.0;
		double v1 = 0.0, v2 = 0.0;
		for ( int i = 0; i < _dim; i ++) {
			v1 += x[i] * x[i];
			v2 += cos(2 * M_PI * x[i]);
		}
		return -20 * exp(-0.2 * sqrt(v1 / _dim)) - exp(v2 / _dim) + 20 + M_E;
	}
};


class FUNC_ELEVEN : public IFUNC {

public:
	FUNC_ELEVEN() {}
	virtual ~FUNC_ELEVEN() {}
	FUNC_ELEVEN(int dim, double opt_val) : IFUNC(FUNC_ELEVEN_NAME,
			dim,
			opt_val) {
		
		for ( int i = 0; i < _dim; i++ ) {
			_x_left_bound[i] = -600;
			_x_right_bound[i] = 600;
		}
		
	}
	
	double _fitness(const double *x) const {
		double ret_val = 0.0;
		double v1 = 0.0, v2 = 1.0;
		for ( int i = 0; i < _dim; i ++) {
			v1 += x[i] * x[i];
			v2 *= cos(x[i] / sqrt(i + 1));
		}
		return v1 / 4000.0 - v2 + 1.0;
	}
};


class FUNC_TWELVE : public IFUNC {

public:
	FUNC_TWELVE() {}
	virtual ~FUNC_TWELVE() {}
	FUNC_TWELVE(int dim, double opt_val) : IFUNC(FUNC_TWELVE_NAME,
			dim,
			opt_val) {
		
		for ( int i = 0; i < _dim; i++ ) {
			
			_x_left_bound[i] = -50;
			_x_right_bound[i] = 50;
		
		}
		
	}
	
	double _fitness(const double *x) const {
		int a = 10, k = 100, m = 4;
		double v1 = 0.0, v2 = 0.0;
		for ( int i = 0; i < _dim - 1; i ++) {
			double yi = 1 + 0.25 * (1 + x[i]);
			double yi1 = 1 + 0.25 * (1 + x[i + 1]);
			double v = sin(M_PI * yi1);
			v1 += (yi - 1) * (yi - 1) * (1 + 10 * v * v);
		}
		for ( int i = 0; i < _dim; i ++) {
			if (x[i] > a) 
			{
				double tv = 1.0;
				for ( int j = 0; j < m; j ++) tv *= (x[i] - a);
				v2 += k * tv;
			} else if ( x[i] < -a) {
				double tv = 1.0;
				for ( int j = 0; j < m; j ++) tv *= (- x[i] - a);
				v2 += k * tv;
			}
			
		}
		double yd = 0.25 * (x[_dim - 1] + 1);
		double y1 = 0.25 * (x[0] + 1) + 1;
		v1 += 10 * sin(M_PI * y1) * sin(M_PI * y1) + yd * yd;
		v1 = v1 * M_PI / _dim;
		v1 += v2;
		return v1;
	}
};


class FUNC_THIRTEEN : public IFUNC {

public:
	FUNC_THIRTEEN() {}
	virtual ~FUNC_THIRTEEN() {}
	FUNC_THIRTEEN(int dim, double opt_val) : IFUNC(FUNC_THIRTEEN_NAME,
			dim,
			opt_val) {
		
		for ( int i = 0; i < _dim; i++ ) {
			
			_x_left_bound[i] = -50;
			_x_right_bound[i] = 50;
		
		}
		
	}
	
	double _fitness(const double *x) const {
		int a = 5, k = 100, m = 4;
		double v1 = 0.0, v2 = 0.0;
		
		v1 = sin(3 * M_PI * x[0]) * sin(3 * M_PI * x[0]) + (x[_dim - 1] - 1) * (x[_dim - 1] - 1) * 
		
			( 1 + sin(2 * M_PI * x[_dim - 1]) * sin(2 * M_PI * x[_dim - 1]));
		
		for ( int i = 0; i < _dim - 1; i ++) {
			
			double v = sin(3 * M_PI * x[i + 1]);
			v1 += (x[i] - 1) * (x[i] - 1) * (1 + v * v);
		
		}
		
		v1 /= 10.0;
		
		for ( int i = 0; i < _dim; i ++) {
			
			if (x[i] > a) {
				double tv = 1.0;
				for ( int j = 0; j < m; j ++) tv *= (x[i] - a);
				v2 += k * tv;

			} else if ( x[i] < -a) {
				double tv = 1.0;
				for ( int j = 0; j < m; j ++) tv *= (- x[i] - a);
				v2 += k * tv;
			}
			
		}
		v1 += v2;
		return v1;
	}
};

class FUNC_CEC_ONE : public IFUNC {

private:
	double *o;
	
public:
	FUNC_CEC_ONE() {}
	virtual ~FUNC_CEC_ONE() {
		if ( NULL != o ) {
			delete o;
			o = NULL;
		}
	}
	FUNC_CEC_ONE(int dim, double opt_val) : IFUNC(FUNC_CEC_ONE_NAME,
			dim,
			opt_val) {
		
		for ( int i = 0; i < _dim; i++ ) {
			
			_x_left_bound[i] = -100;
			_x_right_bound[i] = 100;
			
		}
		
		o = new double[dim];
	}
	
	double _fitness(const double *x) const {
		
		for ( int i = 0; i < _dim; i ++) {
			
			
			
		}
	}
};

class FUNC_CNN : public IFUNC {
	
private:
	ConvNeuralNetwork *cnn;
	
public:
	FUNC_CNN() {}
	virtual ~FUNC_CNN() {}
	FUNC_CNN(int dim, double opt_val) : IFUNC(CNN_NAME,
			dim,
			opt_val) {
		
		cnn = new ConvNeuralNetwork(2204, 400, 400);
		
		if ( NULL == cnn ) {
			cerr << "[ERROR] bad alloc for CNN!" << endl;
			exit (0);
		}
		
		// 对CNN进行初始化，包括结构初始化，权值不用进行初始化
		// ，DE里的函数可以自动进行,以及卷积层的连接进行初始化
		
		cnn->_load_train_data();
		cnn->_load_test_data();
		
		cnn->_init_net();
			
		for ( int i = 0; i < _dim; i++ ) {
			
			_x_left_bound[i] = -1;
			_x_right_bound[i] = 1;
		
		}
	}
	
	double _fitness(const double *x) const {
		
		
		cnn->_get_from_dev(x);	
		/*
			
		
		for ( int i = 0; i < cnn->_layers.size(); i ++) {
			cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
			cout << "layer " << i << ", type: " << cnn->_layers[i]->_layer_type << endl;
			if ( cnn->_layers[i]->_layer_type == 1 ) {
				
				cout << "kernels : " << endl;
				int pt = 0;
				for ( int j = 0; j < cnn->_layers[i]->_o_fmap_cnt; j ++) {
					for ( int k = 0; k < cnn->_layers[i]->_i_fmap_cnt; k ++) {
						if ( cnn->_layers[i]->_connect_graph[j][k] ) {
							int idx = j * cnn->_layers[i]->_i_fmap_cnt + k;
							cout << "kernel:" << pt << endl;
							pt ++ ;
							for ( int kr = 0; kr < cnn->_layers[i]->_kernel_r; kr ++) {
								for ( int kc = 0; kc < cnn->_layers[i]->_kernel_r; kc ++) {
									cout << cnn->_layers[i]->_kernel[idx][kr][kc] << "\t" ;
								}
								cout << endl;
							}
						}
					}
				}
				cout << "bias: " << endl;
				for ( int j = 0; j < cnn->_layers[i]->_o_fmap_cnt; j ++) {
					cout << cnn->_layers[i]->_bias[j] << "\t";
				}
				cout << endl;
			} else if ( cnn->_layers[i]->_layer_type == 5 ) {
				cout << "weights : " << endl;
				for ( int j = 0; j < cnn->_layers[i]->_i_neuo_cnt; j ++) {
					for ( int k = 0; k < cnn->_layers[i]->_o_neuo_cnt; k ++) {
						cout << cnn->_layers[i]->_w[j][k] << "\t";
					}
					cout << endl;
				}
				cout << "bias: " << endl;
				for ( int j = 0; j < cnn->_layers[i]->_o_neuo_cnt; j ++) {
					cout << cnn->_layers[i]->_bias[j] << "\t";
				}
				cout << endl;
			}
		}
		*/	
		double ret_val = 0.0;
		for ( int i = 0; i < 4; i ++) {
			int v = rand() % 400;
			ret_val += cnn->_cost_val_sig(cnn->_x[v], cnn->_y[v]);
		}
		return ret_val;
	}
	
	void _test(const double *x) {
		cnn->_get_from_dev(x);
		cnn->_test();
	}
	
};

class FUNC_BPNN : public IFUNC {
private:
	BPNN *bpnn;
public:
	FUNC_BPNN() {}
	virtual ~FUNC_BPNN() {}
	FUNC_BPNN(int dim, double opt_val) : IFUNC(BPNN_NAME,
			dim,
			opt_val) {
		
		bpnn = new BPNN(49, 32, 10, 400, 400);

		cout << "BONN" << endl;

		if ( NULL == bpnn ) {
			cerr << "[ERROR] bad alloc for BPNN!" << endl;
			exit (0);
		}
		
		// 对BPNN进行初始化，包括结构初始化，权值不用进行初始化
		// ，DE里的函数可以自动进行,以及卷积层的连接进行初始化
		
		bpnn->_load_train_data();
		bpnn->_load_test_data();
			
		for ( int i = 0; i < _dim; i++ ) {	
			_x_left_bound[i] = -1;
			_x_right_bound[i] = 1;
		}
	}
	
	double _fitness(const double *x) const {
		bpnn->_get_from_dev(x);	
		double ret_val = 0.0;
		for ( int i = 0; i < 40; i ++) {
			int v = rand() % 400;
			ret_val += bpnn->_cost_val_sig(bpnn->_x[v], bpnn->_y[v]);
		}
		return ret_val;
	}
	
	void _test(const double *x) {
		bpnn->_get_from_dev(x);
		bpnn->_test();
		cout << "hello from bpnn!" << endl;
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
			case TWO:
				return new FUNC_TWO(dim, opt_val);
			case THREE:
				return new FUNC_THREE(dim, opt_val);
			case FOUR:
				return new FUNC_FOUR(dim, opt_val);
			case FIVE:
				return new FUNC_FIVE(dim, opt_val);
			case SIX:
				return new FUNC_SIX(dim, opt_val);
			case SEVEN:
				return new FUNC_SEVEN(dim, opt_val);
			case EIGHT:
				return new FUNC_EIGHT(dim, opt_val);
			case NINE:
				return new FUNC_NINE(dim, opt_val);
			case TEN:
				return new FUNC_TEN(dim, opt_val);
			case ELEVEN:
				return new FUNC_ELEVEN(dim, opt_val);
			case TWELVE:
				return new FUNC_TWELVE(dim, opt_val);
			case THIRTEEN:
				return new FUNC_THIRTEEN(dim, opt_val);
				
				
				
			// CEC FUNCTIOn
			case FOURTEEN:
				return new FUNC_CEC_ONE(dim, opt_val);
				
			case CNN:
				return new FUNC_CNN(dim, opt_val);
			
			case BPNNS:
				return new FUNC_BPNN(dim, opt_val);
				
			default:
				break;
		}	
	}
};

#endif



