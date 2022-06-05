all : exe

exe : projet.o function.o seCo.o newIndi.o
	gcc -o exe projet.o function.o seCo.o newIndi.o

projet.o : projet.c
	gcc -o projet.o -c projet.c
	
function.o : function.c
	gcc -o function.o -c function.c
	
seCo.o : seCo.c
	gcc -o seCo.o -c seCo.c
	
newIndi.o : newIndi.c
	gcc -o newIndi.o -c newIndi.c