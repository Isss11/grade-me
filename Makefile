gpa: bin/Calculator.o bin/Course.o bin/Runner.o
	g++ bin/Calculator.o bin/Course.o bin/Runner.o -o bin/gpa

bin/Calculator.o: src/Calculator.cpp include/header.h
	g++ src/Calculator.cpp -c -o bin/Calculator.o

bin/Course.o: src/Course.cpp include/header.h
	g++ src/Course.cpp -c -o bin/Course.o

bin/Runner.o: src/Runner.cpp include/header.h
	g++ src/Runner.cpp -c -o bin/Runner.o

clean:
	rm -rf bin/*