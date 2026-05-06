CC=clang

CFLAGS=-std=c17 -Wall -Wextra -Wpedantic -Wconversion -Wshadow -Wformat=2 -g
SANFLAGS=-fsanitize=address,undefined -fno-omit-frame-pointer

.PHONY: run analyze clean

run:
	mkdir -p build
	$(CC) $(CFLAGS) $(SANFLAGS) src/main.c -o build/toolkit-demo
	./build/toolkit-demo

analyze:
	cppcheck --enable=all --inconclusive --std=c17 --suppress=missingIncludeSystem src/main.c

clean:
	rm -rf build *.dSYM
