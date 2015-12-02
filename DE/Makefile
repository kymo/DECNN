DIR=./


GCC=g++
INC=-I ${DIR}/ -I ${DIR}/../DE -I ${DIR}/../IDE -I ${DIR}/../FUNC


DE=${DIR}/../de
TEST_DE_O=${DIR}/../Obj/TEST_DE.o
DE_O=${DIR}/../Obj/DE.o
DE_SRC=${DIR}/DE.cpp
TEST_DE_SRC=${DIR}/test_de.cpp



${DE}:${TEST_DE_O} ${DE_O}
	${GCC} -o ${DE} ${TEST_DE_O} ${DE_O} ${INC} -g
	
${TEST_DE_O}:${TEST_DE_SRC}
	${GCC} -c ${TEST_DE_SRC} -g ${INC} -o ${TEST_DE_O}

${DE_O}:${DE_SRC}
	${GCC} -c ${DE_SRC} -g ${INC} -o ${DE_O}

clean:
	rm -rf ${DIR}/../Obj/DE.o ${DIR}/../Obj/TEST_DE.o *.o
