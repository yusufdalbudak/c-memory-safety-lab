CC=clang

CFLAGS=-std=c17 -Wall -Wextra -Wpedantic -Wconversion -Wshadow -Wformat=2 -g
SANFLAGS=-fsanitize=address,undefined -fno-omit-frame-pointer

VULN_SRC=src/vulnerable.c
FIXED_SRC=src/fixed.c
VULN_OUT=build/vulnerable
FIXED_OUT=build/fixed

.PHONY: vulnerable fixed analyze-vuln analyze-safe clean

vulnerable:
	mkdir -p build
	$(CC) $(CFLAGS) $(SANFLAGS) $(VULN_SRC) -o $(VULN_OUT)
	./$(VULN_OUT) fixtures/sample.txt

fixed:
	mkdir -p build
	$(CC) $(CFLAGS) $(SANFLAGS) $(FIXED_SRC) -o $(FIXED_OUT)
	./$(FIXED_OUT) fixtures/sample.txt

analyze-vuln:
	cppcheck --enable=all --inconclusive --std=c17 --suppress=missingIncludeSystem $(VULN_SRC) || true

analyze-safe:
	cppcheck --enable=all --inconclusive --std=c17 --suppress=missingIncludeSystem $(FIXED_SRC)

clean:
	rm -rf build *.dSYM
