# C Memory Safety Lab

This lab is designed to teach secure C programming concepts that are directly relevant to cybersecurity.

## Goals
- Understand common C memory safety issues
- Compare unsafe and safe string handling patterns
- Build secure C code with macOS-friendly APIs
- Document secure coding choices for sharing on GitHub

## Build and run
```sh
cd c-memory-safety-lab
clang -Wall -Wextra -Werror -o build/main src/main.c
./build/main
```

## What this example shows
- an unsafe string copy pattern using `strcpy`
- a safer alternative using `strlcpy`
- why explicit bounds checking matters in security-sensitive C code

## Recommendations
- Use `-Wall -Wextra -Werror` when compiling
- Run sanitizers when experimenting with vulnerable code:
  - `clang -fsanitize=address,undefined -g src/main.c -o build/main`
- Keep vulnerable examples clearly labeled and never reuse them in production code

## GitHub sharing
For guidance on GitHub setup and project sharing on macOS, see `docs/github-on-macos.md`.
