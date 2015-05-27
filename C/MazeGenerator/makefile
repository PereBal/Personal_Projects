CC=gcc
LFLAGS= -lm 
CFLAGS= -O2 -Wall
LST=list
MG=mazeGenerator
EXE=main-test
OBJ=$(LST).o $(MG).o $(EXE).o

all: $(LST).o $(MG).o $(EXE)

$(EXE): $(LST).o $(MG).o $(EXE).o
	$(CC) $(LST).o $(MG).o $(EXE).o -o $@ $(LFLAGS)

%.o: %.c
	$(CC) -c $(CFLAGS) $< -o $@

.PHONY: clean
clean:
	rm -f $(OBJ) $(EXE)
