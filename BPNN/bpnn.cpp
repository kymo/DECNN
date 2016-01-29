
/* FileName: bpnn.cpp */
#include "bpnn.h"
#include "util.h"

void BPNN::_get_from_dev(const double*x) {

	int pt = 0;
	for ( int i = 0; i < _i_neuo_cnt; i ++) {
		for ( int j = 0; j < _h_neuo_cnt; j ++) {
			_w_i_h[i][j] = x[pt ++];
		}
	}
	for ( int j = 0; j < _h_neuo_cnt; j ++) {
		_h_bias[j] = x[pt ++];
	}
	for ( int i = 0; i < _h_neuo_cnt; i ++) {
		for ( int j = 0; j < _o_neuo_cnt; j ++) {
			_w_h_o[i][j] = x[pt ++];
		}
	}
	for ( int j = 0; j < _o_neuo_cnt; j ++) {
		_o_bias[j] = x[pt ++];
	}

}

double* BPNN::_calculate(double*v) {

	for ( int j = 0; j < _h_neuo_cnt; j ++) {
		
		double vt = 0.0;
		for ( int i = 0; i < _i_neuo_cnt; i ++) {
			vt += v[i] * _w_i_h[i][j];
		}
		_h_v[j] = sigm(vt + _h_bias[j]);
	}

	double *o = new double[_o_neuo_cnt];
	double ret = 0.0;
	for ( int k = 0; k < _o_neuo_cnt; k ++) {
		double vt = 0.0;
		for ( int j = 0; j < _h_neuo_cnt; j ++) {
			vt += _h_v[j] * _w_h_o[j][k];
		}
		o[k] = sigm(vt + _o_bias[k]);
	}
	return o;
}

double BPNN::_calc_val_sig(double*v, int *y) {

	for ( int j = 0; j < _h_neuo_cnt; j ++) {
		
		double vt = 0.0;
		for ( int i = 0; i < _i_neuo_cnt; i ++) {
			vt += v[i] * _w_i_h[i][j];
		}
		_h_v[j] = sigm(vt + _h_bias[j]);
	}

	double ret = 0.0;
	for ( int k = 0; k < _o_neuo_cnt; k ++) {
		double vt = 0.0;
		for ( int j = 0; j < _h_neuo_cnt; j ++) {
			vt += _h_v[j] * _w_h_o[j][k];
		}
		_o_v[k] = sigm(vt + _o_bias[k]);
		ret += (_o_v[k] - y[k]) * (_o_v[k] - y[k]);
	}

	return 0.5 * ret;
}

void BPNN::_load_train_data() {
	
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
		double val[28][28];
		for(int i = 0; i < 28; i ++)
		{
			for(int j = 0; j < 28; j ++)
			{
				char st[4] ={'0'};
				ifs.read(st, 1);
				int t = 0;
				memcpy(&t, st, sizeof(t));
				// load _x feature
				// _x[idx][pt ++] = t;
				val[i][j] = t;
			}
		}
		int tot = 0;
		for ( int i = 0; i < 7; i ++) {
			for ( int j = 0; j < 7; j ++) {
				int cnt = 0;
				for ( int k = i * 4; k < i * 4 + 4; k ++) {
					for ( int l = j * 4; l < j * 4 + 4; l ++) {
						if ( val[k][l] > 0 ) {
							cnt += 1;
						}

					}
				}
				_x[idx][pt ++] = cnt;
				tot += cnt;
			}
		}
		for ( int i = 0; i < pt; i ++) {
			_x[idx][i] /= tot*1.0;
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

void BPNN::_load_test_data() {
	
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
		double val[28][28];
		for(int i = 0; i < 28; i ++)
		{
			for(int j = 0; j < 28; j ++)
			{
				char st[4] ={'0'};
				ifs.read(st, 1);
				int t = 0;
				memcpy(&t, st, sizeof(t));
				// load _x feature
				// _t_x[idx][pt ++] = t;
				val[i][j] = t;
			}
		}
		
		int tot = 0;
		for ( int i = 0; i < 7; i ++) {
			for ( int j = 0; j < 7; j ++) {
				int cnt = 0;
				for ( int k = i * 4; k < i * 4 + 4; k ++) {
					for ( int l = j * 4; l < j * 4 + 4; l ++) {
						if ( val[k][l] > 0 ) {
							cnt += 1;
						}

					}
				}
				_x[idx][pt ++] = cnt;
				tot += cnt;
			}
		}
		for ( int i = 0; i < pt; i ++) {
			_x[idx][i] /= tot*1.0;
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

void BPNN::_test() {
	int right_cnt = 0, tot_cnt = 0;
	for ( int i = 0; i < _test_sample_cnt; i ++) {
		double *ry = _calculate(_t_x[i]);
		int index = 0;
		double vmax = -1000000.0;
		for ( int j = 0; j < 10; j ++) {
			if (vmax < ry[j]) {
				vmax = ry[j];
				index= j ;
			}
		}
		
		if ( ry != NULL ) {
			delete [] ry;
			ry = NULL;
		}
		if ( _t_y[i][index] == 1)
		{
			right_cnt += 1;
		}
		tot_cnt += 1;
	}
	cout << "[LOG] right cnt : " << right_cnt << " " << "total cnt: " << tot_cnt << endl;
	
}

