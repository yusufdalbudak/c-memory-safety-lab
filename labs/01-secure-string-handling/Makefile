CC=clang

CFLAGS=-std=c17 -Wall -Wextra -Wpedantic -Wconversion -Wshadow -Wformat=2 -g
SANFLAGS=-fsanitize=address,undefined -fno-omit-frame-pointer

SRC=src/main.c
OUT=build/lab-01
SANOUT=build/lab-01-sanitize

.PHONY: all run sanitize analyze clean

all:
	mkdir -p build
	$(CC) $(CFLAGS) $(SRC) -o $(OUT)

run: all
	./$(OUT)

sanitize:
	mkdir -p build
	$(CC) $(CFLAGS) $(SANFLAGS) $(SRC) -o $(SANOUT)
	./$(SANOUT)

analyze:
	cppcheck --enable=all --inconclusive --std=c17 --suppress=missingIncludeSystem $(SRC)

clean:
	rm -rf build *.dSYM
