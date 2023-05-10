all:
	g++ -o triangle triangle.cpp -L "D:/TOOL/mingw64/bin/" -lfreeglut -lglu32 -lopengl32
	./triangle
	
test:
	g++ -o triangle triangle.cpp -lGLU -lGL -lglut
	./triangle
	
test1:
	g++ -c -o test.o test.cpp -I "C:\MinGW\include"
	g++ -o test test.o -L "C:\MinGW\lib\x64" -lfreeglut -lglu32 -lopengl32
	./test

default:
	gcc test.c -o run -lfreeglut -lglu32 -lopengl32
	./run
	del run.exe
	
default1:
	g++ test.cpp -o run -lfreeglut -lglu32 -lopengl32
	./run
	del run.exe