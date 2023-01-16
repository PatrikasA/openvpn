BIN:=openvpntest
CC:=gcc
LDFLAGS:=
OBJ:=$(SRC:.c=.o)
SRC:=$(wildcard *.c)


.PHONY: all clean

all: $(BIN)

$(BIN): $(SRC)
		$(CC) -o $@ $^ $(LDFLAGS)

clean:
		$(RM) $(BIN) $(OBJ)
