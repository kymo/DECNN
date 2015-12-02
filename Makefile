
## makefile for de

.PHONY : all target clean

all:
	cd ./DE && make
	cd ./MDE && make
	
clean:
	cd DE && make clean
	cd MDE && make clean
