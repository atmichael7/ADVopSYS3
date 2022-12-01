output: newmain.cpp block.o sdisk.o filesys.o shell.o table.o
	g++ newmain.cpp block.o sdisk.o filesys.o shell.o table.o -o output

table.o: table.cpp
	g++ -c table.cpp

shell.o: shell.cpp
	g++ -c shell.cpp

filesys.o: filesys.cpp
	g++ -c filesys.cpp

sdisk.o: sdisk.cpp
	g++ -c sdisk.cpp

block.o: block.cpp
	g++ -c block.cpp

clean:
	rm *.o