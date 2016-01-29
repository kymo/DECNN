/* FileName : util.cpp */
#include "util.h"


double sigm(double x) {
	return 1.0 / ( 1 + exp( - x));
}

void swap_buffer(char* buf)  
{  
    char temp;
    temp = *(buf);  
    *buf = *(buf + 3);  
    *(buf + 3) = temp;  
    temp = *(buf + 1);  
    *(buf + 1) = *(buf + 2);  
    *(buf + 2) = temp;  
}  
