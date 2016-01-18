
## makefile for de

.PHONY : all clean

all:
	cd ./CNN && make target
	cd ./DE && make
	cd ./MDE && make
	
clean:
	cd DE && make clean
	cd MDE && make clean
	cd CNN && make clean
	rm de.exe mde.exe
