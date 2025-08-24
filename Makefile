CC=g++
CFLAGS=-std=c++17
LIBS=-lpthread
EXEC_FILE=ipv4_chat


all: install

install: main.cpp
	$(CC) $(CFLAGS) main.cpp -o $(EXEC_FILE) $(LIBS)
