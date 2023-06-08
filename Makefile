analyzer: test.o tokenizer.o myFunction.o
	g++ test.o tokenizer.o myFunction.o -o analyzer
	make clean
test.o: test.cpp tokenizer.hpp myFunction.hpp
	g++ test.cpp -c -o test.o
tokenizer.o: tokenizer.cpp tokenizer.hpp
	g++ tokenizer.cpp -c -o tokenizer.o
myFunction.o: myFunction.cpp myFunction.hpp
	g++ myFunction.cpp -c -o myFunction.o
.PHONY: clean
clean:
	rm -rf *.o