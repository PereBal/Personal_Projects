CC=gcc
CFLAGS= -O2 -Wall -std=c99
LFLAGS=
LEX=a_lex
SINT=a_sint
CAL=calculator
OBJS= $(LEX).o $(SINT).o $(CAL).o


all: calc

calc: $(LEX).o $(SINT).o $(CAL).o
		$(CC) $(CAL).o $(SINT).o $(LEX).o -o $@ $(LFLAGS)

$(SINT): $(SINT).o
		$(CC) $(SINT).o -o $@ $(LFLAGS)

$(LEX): $(LEX).o
		$(CC) $(LEX).o -o $@ $(LFLAGS)

%.o: %.c
	$(CC) -c $(CFLAGS) $< -o $@

.PHONY: clean
clean:
		rm -f $(OBJS) calc
