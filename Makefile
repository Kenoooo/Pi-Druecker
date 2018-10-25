Main: main.o mqtt.o stopwatch.o
	gcc -o Main main.o mqtt.o stopwatch.o -l paho-mqtt3cs

main.o: main.c
	gcc -c main.c

mqtt.o: mqtt.c mqtt.h
	gcc -c mqtt.c

stopwatch.o: stopwatch.c stopwatch.h
	gcc -c stopwatch.c

clean: Main
	rm -f *.o

test: Main Test
	./Test

Test: test.o
	gcc -o Test test.o -l cmocka

test.o:	test.c
	gcc -c test.c
