all: recommender

recommender: matrix.o model.o
	g++ main.cpp matrix.o model.o -g -o recommender -O3 -Wall -Wextra

model.o: model.cpp
	g++ model.cpp -g -c -o model.o -O3 -Wall -Wextra

matrix.o: matrix.cpp
	g++ matrix.cpp -g -c -o matrix.o -O3 -Wall -Wextra

clean:
	rm recommender
	rm matrix.o
	rm model.o