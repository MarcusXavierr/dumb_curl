CC=clang
BIN=dumbcurl
CFLAGS= -Wall -Wextra -lcurl -lSDL2 -lSDL2_mixer

all: dumbcurl

%.o: %.c %.h
	$(CC) $(CFLAGS) -c $^

dumbcurl: main.c utils.c music.c
	$(CC) $(CFLAGS) $^ -o $@

debug: main.c utils.c music.c
	$(CC) $(CFLAGS) -g -o $@ $^

clean:
	rm *.o $(BIN)
