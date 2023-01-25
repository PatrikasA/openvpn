BIN:=ovpn_tel
CC:=gcc
LDFLAGS:= -lblobmsg_json -lubox -lubus -largp
OBJ:=$(SRC:.c=.o)
SRC:=$(wildcard *.c)


.PHONY: all clean

all: $(BIN)

$(BIN): $(SRC)
		$(CC) -o $@ $^ $(LDFLAGS)

clean:
		$(RM) $(BIN) $(OBJ)
