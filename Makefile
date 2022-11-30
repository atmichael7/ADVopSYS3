output: main.o block.o sdisk.o filesys.o
	g++ main.o block.o sdisk.o filesys.o -o output
	

filesys.o:
	g++ -c filesys.cpp

sdisk.o:
	g++ -c sdisk.cpp

block.o:
	g++ -c block.cpp

main.o: main.cpp
	g++ -c main.cpp

clean:
	rm *.o
