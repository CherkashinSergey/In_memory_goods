CC=g++
CFLAGS=-c -Wall -std=c++17 -g3 -O0

CLASSES= item

all: clean goods

goods: item.o storage.o main.o
	$(CC) item.o storage.o main.o -lpthread -o goods
	#factorial.o hello.o -o hello

main.o: main.cpp
	$(CC) $(CFLAGS) main.cpp

item.o: item.cpp
	$(CC) $(CFLAGS) item.cpp

storage.o: storage.cpp
	$(CC) $(CFLAGS) storage.cpp

#factorial.o: factorial.cpp
#	$(CC) $(CFLAGS) factorial.cpp
#
#hello.o: hello.cpp
#	$(CC) $(CFLAGS) hello.cpp

clean:
	rm -rf *.o goods
