output: main.o block.o sdisk.o filesys.o
	g++ main.o block.o sdisk.o filesys.o -o output

main.o: main.cpp
	g++ -c main.cpp

block.o:
	g++ -c block.cpp

sdisk.o:
	g++ -c sdisk.cpp
	
filesys.o:
	g++ -c filesys.cpp

clean:
	rm *.o
