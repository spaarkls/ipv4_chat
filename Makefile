CC=g++
CFLAGS=-std=c++17
LIBS=-lpthread
EXEC_FILE=ipv4_chat

all: install

install: exceptions.o helper.o ipv4_chat.o main.o
	$(CC) $(CFLAGS) $^ -o $(EXEC_FILE) $(LIBS)

exceptions.o: src/exceptions/exceptions.cpp src/exceptions/exceptions.h
	$(CC) -c $(CFLAGS) src/exceptions/exceptions.cpp -o $@

helper.o: src/helper.cpp src/helper.h src/common/object.h
	$(CC) -c $(CFLAGS) src/helper.cpp -o $@

ipv4_chat.o: src/ipv4_chat.cpp src/ipv4_chat.h src/common/object.h
	$(CC) -c $(CFLAGS) src/ipv4_chat.cpp -o $@

main.o: main.cpp src/exceptions/exceptions.h src/helper.h
	$(CC) -c $(CFLAGS) main.cpp -o $@


clean:
	rm -rf *.o ipv4_chat