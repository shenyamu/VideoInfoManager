CC=g++ -lncurses -lsqlite3
CXX=g++ -g
ELF=main
SRC=$(shell find ./ -name '*.cpp')
OBJ=$(SRC:.cpp=.o)
$(ELF):$(OBJ)
$(OBJ):
clean:
	rm -f $(OBJ) $(ELF)
