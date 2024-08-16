CFLAGS=-Wall -Wextra -O2
LFLAGS=-lm -lraylib
OBJS=chart.o chartclassic.o

ex.out: main.cpp $(OBJS)
	g++ main.cpp $(OBJS) -o ex.out $(CFLAGS) $(LFLAGS)

chart.o: charts/chart.cpp
	g++ charts/chart.cpp -o chart.o -c $(CFLAGS) $(LFLAGS)

chartclassic.o: charts/chartclassic.cpp
	g++ charts/chartclassic.cpp -o chartclassic.o -c $(CFLAGS) $(LFLAGS)

clean:
	rm -rf *.o *.out
