
LDFLAGS += -lncurses

.PHONY: all clean

all: enigma

enigma: main.c ./plugins/*.c ./cfgs/*.c ./utils/*.c
	@gcc -o $@ $^ $(LDFLAGS)

clean:
	@rm -f enigma
