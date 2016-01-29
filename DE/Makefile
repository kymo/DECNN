DIR=./


GCC=g++
INC=-I ${DIR}/ -I ${DIR}/../DE -I ${DIR}/../IDE -I ${DIR}/../FUNC -I ${DIR}/../CNN -I ${DIR}/../BPNN


DE=${DIR}/../de
TEST_DE_O=${DIR}/../Obj/TEST_DE.o
DE_O=${DIR}/../Obj/DE.o
UTIL_O=${DIR}/../Obj/util.o
CNN_O=${DIR}/../Obj/cnn.o
BPNN_O=${DIR}/../Obj/bpnn.o
LAYER_O=${DIR}/../Obj/layer.o
DE_SRC=${DIR}/DE.cpp
TEST_DE_SRC=${DIR}/test_de.cpp



${DE}:${TEST_DE_O} ${DE_O} ${UTIL_O} ${CNN_O} ${LAYER_O} ${BPNN_O}
	${GCC} -o ${DE} ${TEST_DE_O} ${DE_O} ${UTIL_O} ${CNN_O} ${LAYER_O} ${BPNN_O} ${INC} -g
	
${TEST_DE_O}:${TEST_DE_SRC}
	${GCC} -c ${TEST_DE_SRC} -g ${INC} -o ${TEST_DE_O}

${DE_O}:${DE_SRC}
	${GCC} -c ${DE_SRC} -g ${INC} -o ${DE_O}

clean:
	rm -rf ${DIR}/../Obj/DE.o ${DIR}/../Obj/TEST_DE.o *.o
