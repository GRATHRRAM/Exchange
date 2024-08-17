FLAGS=-Wall -Wextra -g
LFLAGS=-lm -lraylib
OBJS=stock.o chartclassic.o

../ex.out: main.cpp $(OBJS)
	g++ main.cpp $(OBJS) -o ../ex.out $(CFLAGS) $(LFLAGS)

stock.o: stock.cpp
	g++ stock.cpp -o stock.o -c $(CFLAGS) $(LFLAGS)

chartclassic.o: charts/chartclassic.cpp
	g++ charts/chartclassic.cpp -o chartclassic.o -c $(CFLAGS) $(LFLAGS)

clean:
	rm -rf *.o ../*.out
