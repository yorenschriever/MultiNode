CC=g++
CFLAGS=-I. -std=c++11
DEPS = Socket.h Nodes.h NodeManager.h
OBJ = main.o Socket.o Nodes.o NodeManager.o

%.o: %.cpp $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

hellomake: $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS)