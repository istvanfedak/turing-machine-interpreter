CC = g++
CDFLAGS = -Wall -g
SRC = main.cpp shell.cpp print.cpp Tape.cpp read.cpp assert.cpp compareState.cpp getNewState.cpp sortTable.cpp State.cpp StateTable.cpp
OBJ = $(SRC:%.cpp=%.o)
EXE = tm

all: $(EXE)
	@echo Done!
	@echo
	@echo Usage: ./$(EXE) \<TM file name\> \<input-string\> 
	@echo \ \ \ or: ./$(EXE) \<TM file name\> -f \<input-file-name\>

$(EXE): $(OBJ)
	@echo Linking...
	@$(CC) $(OBJ) -o $@

$(OBJ): $(SRC)
	@echo Compiling...
	@$(CC) $(CDFLAGS) -c $(SRC) $<

clean:
	@echo Cleaning up...
	@rm -f *.o
	@rm -f *.core
	@rm -f *.out
	@rm -f $(EXE)
