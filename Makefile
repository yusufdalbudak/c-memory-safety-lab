CC=clang

CFLAGS=-std=c17 -Wall -Wextra -Wpedantic -Wconversion -Wshadow -Wformat=2 -g
SANFLAGS=-fsanitize=address,undefined -fno-omit-frame-pointer

SRC=src/main.c
OUT=build/c-memory-safety-lab
SANOUT=build/c-memory-safety-lab-sanitize

.PHONY: all run sanitize analyze analyze-vuln overflow-demo overflow-fixed ci clean

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
	cppcheck --enable=all --inconclusive --std=c17 --suppress=missingIncludeSystem src/main.c src/fixed_overflow.c

analyze-vuln:
	cppcheck --enable=all --inconclusive --std=c17 --suppress=missingIncludeSystem src/vulnerable_overflow.c || true

clean:
	rm -rf build *.dSYM

overflow-demo:
	mkdir -p build
	$(CC) $(CFLAGS) $(SANFLAGS) src/vulnerable_overflow.c -o build/vulnerable-overflow
	./build/vulnerable-overflow

overflow-fixed:
	mkdir -p build
	$(CC) $(CFLAGS) $(SANFLAGS) src/fixed_overflow.c -o build/fixed-overflow
	./build/fixed-overflow

ci: clean run sanitize analyze overflow-fixed
