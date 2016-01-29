DIR=./


GCC=g++
INC=-I ${DIR}/ -I ${DIR}/../DE -I ${DIR}/../IDE -I ${DIR}/../FUNC -I ${DIR}/../CNN -I ${DIR}/../BPNN

MDE=${DIR}/../mde
TEST_MDE_O=${DIR}/../Obj/TEST_MDE.o
MDE_O=${DIR}/../Obj/MDE.o
UTIL_O=${DIR}/../Obj/util.o
CNN_O=${DIR}/../Obj/cnn.o
LAYER_O=${DIR}/../Obj/layer.o
BPNN_O=${DIR}/../Obj/bpnn.o
MDE_SRC=${DIR}/MDE.cpp
TEST_MDE_SRC=${DIR}/test_mde.cpp

${MDE}:${TEST_MDE_O} ${MDE_O} ${UTIL_O} ${BPNN_O} ${CNN_O} ${LAYER_O}
	${GCC} -o ${MDE} ${TEST_MDE_O} ${BPNN_O} ${MDE_O} ${UTIL_O} ${CNN_O} ${LAYER_O} ${INC} -g
	
${TEST_MDE_O}:${TEST_MDE_SRC}
	${GCC} -c ${TEST_MDE_SRC} -g ${INC} -o ${TEST_MDE_O}

${MDE_O}:${MDE_SRC}
	${GCC} -c ${MDE_SRC} -g ${INC} -o ${MDE_O}

clean:
	rm -rf ${DIR}/../Obj/MDE.o ${DIR}/../Obj/TEST_MDE.o *.o
