all: scanner.o parser.o testTree.o stack.o semantics.o main.o
	g++ -o comp -g scanner.o parser.o testTree.o stack.o semantics.o main.o

scanner.o: scanner.cpp
	g++ -c -g scanner.cpp

parser.o: parser.cpp
	g++ -c -g parser.cpp

testTree.o: testTree.cpp
	g++ -c -g testTree.cpp

stack.o: stack.cpp
	g++ -c -g stack.cpp 

semantics.o: semantics.cpp
	g++ -c -g semantics.cpp

main.o: main.cpp
	g++ -c -g main.cpp

clean: remove

remove:
	rm *.o comp *.asm

clear:
	clear

success:
	$(info SUCCESS)

readme:
	cat README
