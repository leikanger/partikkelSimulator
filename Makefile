all: main.o partikkelG.o masseG.o opengl.o vektor.o utproevingAvNyeAspekt.o
	g++ main.o partikkelG.o masseG.o utproevingAvNyeAspekt.o opengl.o vektor.o -march=core2 -O3 -ffast-math -lpthread -lGLU -lGL -lglut -o Partikkel.out
# har tatt bort gruppering.*
#all: main.o partikkelG.o masseG.o gruppering.o opengl.o utproevingAvNyeAspekt.o
#	g++ main.o partikkelG.o masseG.o gruppering.o utproevingAvNyeAspekt.o opengl.o -lpthread -lGLU -lGL -lglut -o Partikkel.out
gammelMake_all : partikkelG.cpp
	g++ main.cpp partikkelG.cpp opengl.cpp  masseG.cpp utproevingAvNyeAspekt.cpp -lGL -lGLU -lpthread -lglut -march=core2 -O3 -ffast-math -o Partikkel.out

debug : 
	g++ -g partikkelG.cpp opengl.cpp gruppering.cpp masseG.cpp utproevingAvNyeAspekt.cpp -lGL -lGLU -lpthread -lglut -o Partikkel.debug
	#gdb Partikkel.debug // Har du forresten huska debugMode i partikkelG.h?

clean :
	rm -rf *.out *.o;
	make
c:
	make clean



main.o: 	main.cpp main.h
	g++ -c main.cpp -march=core2 -O3 -ffast-math
utproevingAvNyeAspekt.o: utproevingAvNyeAspekt.cpp
	g++ -c utproevingAvNyeAspekt.cpp -march=core2 -O3 -ffast-math

partikkelG.o: 	partikkelG.cpp partikkelG.h
	g++ -c partikkelG.cpp -lpthread -march=core2 -O3 -ffast-math
gruppering.o: 	gruppering.cpp gruppering.h
	g++ -c gruppering.cpp -lpthread -march=core2 -O3 -ffast-math
masseG.o: 	masseG.cpp masseG.h
	g++ -c masseG.cpp -lpthread -march=core2 -O3 -ffast-math
vektor.o: vektor.cpp masseG.h
	g++ -c vektor.cpp -march=core2 -O3 -ffast-math
opengl.o: 	opengl.cpp main.h
	g++ -c opengl.cpp -lGL -lGLU -lglut -march=core2 -O3 -ffast-math
