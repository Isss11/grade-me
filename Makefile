gpa: bin/Calculator.o bin/Course.o
	g++ bin/Calculator.o bin/Course.o -o bin/gpa

bin/Calculator.o: src/Calculator.cpp include/header.h
	g++ src/Calculator.cpp -c -o bin/Calculator.o
bin/Course.o: src/Course.cpp include/header.h
	g++ src/Course.cpp -c -o bin/Course.o

clean:
	rm -rf bin/gpa