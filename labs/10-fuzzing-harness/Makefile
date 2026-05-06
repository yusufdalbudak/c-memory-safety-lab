CC=clang

CFLAGS=-std=c17 -Wall -Wextra -Wpedantic -Wconversion -Wshadow -Wformat=2 -g -Iinclude
SANFLAGS=-fsanitize=address,undefined -fno-omit-frame-pointer
FUZZFLAGS=-fsanitize=fuzzer,address,undefined -fno-omit-frame-pointer

.PHONY: run stress fuzz-libfuzzer analyze clean

run:
	mkdir -p build
	$(CC) $(CFLAGS) $(SANFLAGS) src/main.c src/parser.c -o build/demo
	./build/demo

stress:
	mkdir -p build
	$(CC) $(CFLAGS) $(SANFLAGS) src/stress.c src/parser.c -o build/stress
	./build/stress

# Optional: requires a Clang build with libFuzzer runtime (not all Xcode toolchains ship it).
fuzz-libfuzzer:
	mkdir -p build
	$(CC) $(CFLAGS) $(FUZZFLAGS) src/harness.c src/parser.c -o build/harness
	./build/harness -runs=2048 -max_len=512 -max_total_time=2

analyze:
	cppcheck --enable=all --inconclusive --std=c17 --suppress=missingIncludeSystem -I include src/parser.c src/main.c src/stress.c

clean:
	rm -rf build *.dSYM
