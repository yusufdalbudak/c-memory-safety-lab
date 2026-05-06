CC=clang

CFLAGS_COMMON=-std=c17 -Wall -Wextra -Wpedantic -Wconversion -Wshadow -Wformat=2
DEV_FLAGS=$(CFLAGS_COMMON) -g -O0 -fsanitize=address,undefined -fno-omit-frame-pointer
HARD_FLAGS=$(CFLAGS_COMMON) -O2 -D_FORTIFY_SOURCE=2 -fstack-protector-strong -g

SRC=src/bounds_demo.c
OUT_DEV=build/bounds-dev
OUT_HARD=build/bounds-hardened

.PHONY: dev hardened analyze clean

dev:
	mkdir -p build
	$(CC) $(DEV_FLAGS) $(SRC) -o $(OUT_DEV)
	./$(OUT_DEV)

hardened:
	mkdir -p build
	$(CC) $(HARD_FLAGS) $(SRC) -o $(OUT_HARD)
	./$(OUT_HARD)

analyze:
	cppcheck --enable=all --inconclusive --std=c17 --suppress=missingIncludeSystem $(SRC)

clean:
	rm -rf build *.dSYM
