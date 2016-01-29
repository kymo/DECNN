/* FileName : cnn.cpp */
#include "cnn.h"

void ConvNeuralNetwork::_transfer_to_dev(double *a) {
	
	a 		= new double[_param_cnt];
	int pt 	= 0;
	
	for ( int i = 0; i < _layers.size(); i ++) {		
		
		if ( _layers[i]->_layer_type == CONV ) {
			int ofmap_cnt = _layers[i]->_o_fmap_cnt;
			for ( int j = 0; j < _layers[i]->_o_fmap_cnt; j ++) {
				for ( int k = 0; k < _layers[i]->_i_fmap_cnt; k ++) {
					// 判断输入特征图j和输出特征图k之间是否有卷积
					if ( ! _layers[i]->_connect_graph[j][k] ) {
						continue;
					}
					for ( int kr = 0; kr < _layers[i]->_kernel_r; kr ++) {
						for ( int kc = 0; kc < _layers[i]->_kernel_c; kc ++) {
							a[pt ++] = _layers[i]->_kernel[j * ofmap_cnt + k][kr][kc];
						}
					}
				}
			}
			for ( int j = 0; j < _layers[i]->_o_fmap_cnt; j ++) {
				a[pt ++] = _layers[i]->_bias[j];
			}
		} else if ( _layers[i]->_layer_type == OUTPUT ) {
			for ( int j = 0; j <  _layers[i]->_i_neuo_cnt; j ++) {
				for ( int k = 0; k < _layers[i]->_o_neuo_cnt; k ++) {
					a[pt ++] = _layers[i]->_w[j][k];
				}
			}
			for (  int j = 0; j < _layers[i]->_o_neuo_cnt; j ++) {
				a[pt ++] = _layers[i]->_bias[j];
			}
		}	
	}
}

void ConvNeuralNetwork::_get_from_dev(const double *a) {
	
	int pt = 0;
	for ( int i = 0; i < _layers.size(); i ++) {
		if ( _layers[i]->_layer_type == CONV ) {
			int ifmap_cnt = _layers[i]->_i_fmap_cnt;
			
			for ( int j = 0; j < _layers[i]->_o_fmap_cnt; j ++) {
				for ( int k = 0; k < _layers[i]->_i_fmap_cnt; k ++) {
					
					if ( ! _layers[i]->_connect_graph[j][k] ) {
						continue;
					}
					for ( int kr = 0; kr < _layers[i]->_kernel_r; kr ++) {
						for ( int kc = 0; kc < _layers[i]->_kernel_c; kc ++) {
							_layers[i]->_kernel[j * ifmap_cnt + k][kr][kc] = a[pt ++];
						}
					}
				}
			}
			for ( int j = 0; j < _layers[i]->_o_fmap_cnt; j ++) {
				_layers[i]->_bias[j] = a[pt ++];
			}
		} else if ( _layers[i]->_layer_type == OUTPUT ) {
			for ( int j = 0; j <  _layers[i]->_i_neuo_cnt; j ++) {
				for ( int k = 0; k < _layers[i]->_o_neuo_cnt; k ++) {
					_layers[i]->_w[j][k] = a[pt ++];
				}
			}
			for (  int j = 0; j < _layers[i]->_o_neuo_cnt; j ++) {
				_layers[i]->_bias[j] = a[pt ++];
			}
		}	
	}
}

void ConvNeuralNetwork::_add_layer( Layer* &layer) {
	_layers.push_back(layer);
}

double* ConvNeuralNetwork::_calculate(double *v) {

	_layers[0]->_set_input_fmap(v);
	for ( int _lc = 1; _lc < _layers.size(); _lc ++) {
		_layers[_lc]->_forward(_layers[_lc - 1]);
	}
	
	Layer *o_layer = _layers[_layers.size() -1];
	int o_cnt = o_layer->_o_neuo_cnt;
	
	double *tv = new double[o_cnt];
	
	for ( int _oc = 0; _oc < o_layer->_o_neuo_cnt; _oc ++) {
		tv[_oc] = o_layer->_o[_oc];
	}
	
	return tv;
}

double ConvNeuralNetwork::_cost_val_sig(double *v, int *y) {
	
	
	_layers[0]->_set_input_fmap(v);
	/*
	for ( int i = 0; i < _layers[0]->_o_fmap_r; i ++) {
		for ( int j = 0; j < _layers[0]->_o_fmap_c; j ++) {
			cout << _layers[0]->_o_fmap[0]._data[i][j] << " ";
		}
		cout << endl;
	}	
	int pt = 0;
	for ( int i = 0; i < _layers[1]->_o_fmap_cnt; i ++) {
		for ( int j = 0; j < _layers[1]->_i_fmap_cnt; j ++) {
			if ( _layers[1]->_connect_graph[i][j] ) {
				int idx = i * _layers[1]->_i_fmap_cnt + j;
				cout << "Kernel" << pt << endl;
				pt += 1;
				for ( int kr = 0; kr < _layers[1]->_kernel_r; kr ++) {
					for ( int kc = 0; kc < _layers[1]->_kernel_c; kc ++) {
						cout << _layers[1]->_kernel[idx][kr][kc] << " ";
					}
					cout << endl;
				}
			}
		}
	}
	*/
	for ( int _lc = 1; _lc < _layers.size(); _lc ++) {
		
		//cout << "layer : " << _lc << endl;
		
		_layers[_lc]->_forward(_layers[_lc - 1]);
		
		/*
		for ( int k = 0; k < _layers[_lc]->_o_fmap_cnt; k ++) {
			//cout << "FeatureMap " << k + 1 << endl;
			for ( int i = 0; i < _layers[_lc]->_o_fmap_r; i ++) {
				for ( int j = 0; j < _layers[_lc]->_o_fmap_c; j ++) {
					cout << _layers[_lc]->_o_fmap[k]._data[i][j] << "\t";
				}
				cout << endl;
			}
		}
		*/
		
	}
	
	

	Layer *o_layer = _layers[_layers.size() -1];
	double ret = 0.0;
	for ( int _oc = 0; _oc < o_layer->_o_neuo_cnt; _oc ++) {
		ret += (y[_oc] - o_layer->_o[_oc]) * (y[_oc] - o_layer->_o[_oc]) ;
	}
	return 0.5 * ret;
}


void ConvNeuralNetwork::_load_train_data() {
	
	const char fileName[] = "train-images.idx3-ubyte";  
	const char labelFileName[] = "train-labels.idx1-ubyte";  
    ifstream lab_ifs(labelFileName, ios_base::binary);  
	ifstream ifs(fileName, ios_base::binary);  
	
	if( lab_ifs.fail() ) 	{
		cerr << "[ERROR] error when open the label train file!" << endl;
		exit (0);
	}
	
	if (ifs.fail()) {
		cerr << "[ERROR] error when open the train file!" << endl;
		exit (0);
	}
	
    //Read train data number and image rows / cols   
    char magicNum[4], ccount[4], crows[4], ccols[4];  
	
    ifs.read(magicNum, sizeof(magicNum));  
    ifs.read(ccount, sizeof(ccount));  
    ifs.read(crows, sizeof(crows));  
    ifs.read(ccols, sizeof(ccols));
	
	swap_buffer(magicNum);
	swap_buffer(ccount);
	swap_buffer(crows);
	swap_buffer(ccols);

	int count, rows, cols;  
    memcpy(&count, ccount, sizeof(count));  
    memcpy(&rows, crows, sizeof(rows));  
    memcpy(&cols, ccols, sizeof(cols));  

	lab_ifs.read(magicNum, sizeof(magicNum));
	lab_ifs.read(ccount, sizeof(magicNum));

	int idx = 0;
	
	while(! ifs.eof() && idx < _train_sample_cnt)
	{
		int pt = 0;
		for(int i = 0; i < 28; i ++)
		{
			for(int j = 0; j < 28; j ++)
			{
				char st[4] ={'0'};
				ifs.read(st, 1);
				int t = 0;
				memcpy(&t, st, sizeof(t));
				// load _x feature
				_x[idx][pt ++] = t;
			}
		}
		char num[4] = {'0'};
		lab_ifs.read(num, 1);
		int out;
		
		memcpy(&out, num, sizeof(out));
		memset(_y[idx], 0, sizeof(_y[idx]));
		_y[idx][out] = 1;
		idx += 1;
	}
	
	cerr << "[LOG] Train data is loaded completed! "<<endl;
}

void ConvNeuralNetwork::_load_test_data() {
	
	const char fileName[] = "t10k-images.idx3-ubyte";  
	const char labelFileName[] = "t10k-labels.idx1-ubyte";
	
    ifstream lab_ifs(labelFileName, ios_base::binary);  
	ifstream ifs(fileName, ios_base::binary);  
	
	if(lab_ifs.fail()) 	{
		cerr << "[ERROR] error when open the label train file!" << endl;
		exit (0);
	}
	
	if(ifs.fail()) {
		cerr << "[ERROR] error when open the train file!" << endl;
		exit (0);
	}
	
    char magicNum[4], ccount[4], crows[4], ccols[4];  
    ifs.read(magicNum, sizeof(magicNum));  
    ifs.read(ccount, sizeof(ccount));  
    ifs.read(crows, sizeof(crows));  
    ifs.read(ccols, sizeof(ccols));
	
	swap_buffer(magicNum);
	swap_buffer(ccount);
	swap_buffer(crows);
	swap_buffer(ccols);

	int count, rows, cols;  
    memcpy(&count, ccount, sizeof(count));  
    memcpy(&rows, crows, sizeof(rows));  
    memcpy(&cols, ccols, sizeof(cols));  

	lab_ifs.read(magicNum, sizeof(magicNum));
	lab_ifs.read(ccount, sizeof(magicNum));

	int idx = 0;

	while(! ifs.eof() && idx < _test_sample_cnt)
	{
		int pt = 0;
		for(int i = 0; i < 28; i ++)
		{
			for(int j = 0; j < 28; j ++)
			{
				char st[4] ={'0'};
				ifs.read(st, 1);
				int t = 0;
				memcpy(&t, st, sizeof(t));
				// load _x feature
				_t_x[idx][pt ++] = t;
			}
		}
		
		char num[4] = {'0'};
		lab_ifs.read(num, 1);
		int out;
		memcpy(&out, num, sizeof(out));
		memset(_y[idx], 0, sizeof(_y[idx]));
		_t_y[idx][out] = 1;
		idx += 1;
	}
	
	cerr << "[LOG] Test data is loaded completed! "<<endl;
}



void ConvNeuralNetwork::_init_net() {
	
	Layer *input_layer_1 = new InputLayer(28, 28, 1, 1);
	_add_layer(input_layer_1);
	
	Layer *conv_layer_2 = new ConvolutionLayer(5, 5, 24, 24, 6, 1);
	int conv_layer_2_connect_type[6][1] = {{1}, {1}, {1}, {1}, {1}, {1}};
	
	conv_layer_2->_init_connect_type((int**)(conv_layer_2_connect_type));
	
	_add_layer(conv_layer_2);
	
	Layer *pool_layer_3 = new PoolingLayer(2, 2, 12, 12, 6, 6);
	
	_add_layer(pool_layer_3);
	
	Layer *conv_layer_4 = new ConvolutionLayer(5, 5, 8, 8, 8, 6);
	
	int conv_layer_4_connect_type[8][6] = {
		{1, 1, 1, 0, 0, 0},
		{0, 1, 1, 1, 0, 0},
		{0, 0, 1, 1, 1, 0},
		{0, 0, 0, 1, 1, 1},
		{1, 1, 1, 1, 0, 0},
		{0, 1, 1, 1, 1, 0},
		{0, 0, 1, 1, 1, 1},
		{1, 1, 1, 1, 1, 1}
	};
	
	conv_layer_4->_init_connect_type((int**)(conv_layer_4_connect_type));
	
	_add_layer(conv_layer_4);
	
	Layer *pool_layer_5 = new PoolingLayer(2, 2, 4, 4, 8, 8);
	_add_layer(pool_layer_5);
	
	Layer *full_input_layer_6 = new FullInputLayer();
	
	_add_layer(full_input_layer_6);
	
	Layer *output_layer_7 = new OutputLayer(128, 10);

	_add_layer(output_layer_7);
	
	cerr << "[LOG] Init net completed!" << endl;	
}

void ConvNeuralNetwork::_test() {
	int right_cnt = 0, tot_cnt = 0;
	for ( int i = 0; i < _test_sample_cnt; i ++) {
		double *ry = _calculate(_t_x[i]);
		int flag = 0;
		for ( int j = 0; j < 10; j ++) {
			cout << ry[j] << ",";
			if ( ry[j] > 0.5 && _t_y[i][j] == 0 || 
					ry[j] < 0.5 && _t_y[i][j] == 1 ) {
				flag = 1;
			}
			cout << _t_y[i][j] << " ";
		}
		cout << endl;
		
		if ( ry != NULL ) {
			delete [] ry;
			ry = NULL;
		}
		if (! flag ) {
			right_cnt += 1;
		}
		tot_cnt += 1;
	}
	cerr << "[LOG] right cnt : " << right_cnt << " " << "total cnt: " << tot_cnt << endl;
	
}

