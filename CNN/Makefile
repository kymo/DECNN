DIR=./


GCC=g++
INC=-I ${DIR}/


#cnn.o:cnn.cpp
#	g++ -c cnn.cpp -g ${INC} -o cnn.o
target:cnn.o layer.o util.o
	
cnn.o:cnn.cpp
	g++ -c cnn.cpp -g ${INC} -o ../Obj/cnn.o
	
layer.o:layer.cpp
	g++ -c layer.cpp -g ${INC} -o ../Obj/layer.o
	
util.o:util.cpp
	g++ -c util.cpp -g ${INC} -o ../Obj/util.o

clean:
	rm -rf ../Obj/layer.o ../Obj/cnn.o ../Obj/util.o 
