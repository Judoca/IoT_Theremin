CC = gcc
CFLAGS = -Iinclude
LIBS = -lwiringPi -lasound -lm -lcurl

all: theremin

theremin: src/main.o src/sensor.o src/sound.o
	$(CC) -o theremin src/main.o src/sensor.o src/sound.o $(LIBS)

src/main.o: src/main.c
	$(CC) -c src/main.c -o src/main.o $(CFLAGS) $(LIBS)

src/sensor.o: src/sensor.c
	$(CC) -c src/sensor.c -o src/sensor.o $(CFLAGS) $(LIBS)

src/sound.o: src/sound.c
	$(CC) -c src/sound.c -o src/sound.o $(CFLAGS) $(LIBS)

clean:
	rm -f src/*.o theremin
