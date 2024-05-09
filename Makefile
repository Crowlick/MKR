HEADERS=headers/Form.h headers/Primitives.h headers/Object.h headers/Node.h headers/Mesh.h headers/System.h


a.out:	Form.o Primitives.o Object.o Node.o Mesh.o System.o main.o
	g++  Form.o Primitives.o Object.o Node.o Mesh.o System.o main.o

Form.o: Form.cpp $(HEADERS)
	g++ -c Form.cpp

Primitives.o: Primitives.cpp $(HEADERS)
	g++ -c Primitives.cpp

Object.o: Object.cpp $(HEADERS)
	g++ -c Object.cpp

Node.o: Node.cpp $(HEADERS)
	g++ -c Node.cpp

Mesh.o: Mesh.cpp $(HEADERS)
	g++ -c Mesh.cpp

System.o: System.cpp $(HEADERS)
	g++ -c System.cpp
	
main.o: main.cpp $(HEADERS)
	g++ -c main.cpp

clean:
	rm *.o
