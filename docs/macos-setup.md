# macOS setup — tools for these labs

This project targets **macOS** on **Apple Silicon** (and Intel) using the **Xcode Command Line Tools** toolchain.

## Apple Clang

Install the command line tools (includes `clang`, `ld`, headers):

```sh
xcode-select --install
```

Verify:

```sh
clang --version
```

Labs use `-fsanitize=address,undefined` for sanitizer builds.

## GNU Make

macOS ships **GNU Make** as `make`. Verify:

```sh
make --version
```

## cppcheck

Install via [Homebrew](https://brew.sh/):

```sh
brew install cppcheck
```

Labs invoke `cppcheck` from each module’s `Makefile`.

## GitHub CLI

Optional, for forks and CI debugging:

```sh
brew install gh
gh auth login
```

## AddressSanitizer (ASan)

ASan is enabled through Clang (`-fsanitize=address`). On Apple platforms it is supported for local development builds; run sanitizer targets only on **non-production** binaries and data.

## UndefinedBehaviorSanitizer (UBSan)

Enabled with `-fsanitize=undefined` (combined in these labs with ASan via `-fsanitize=address,undefined`). Helps catch shifting, alignment, and other undefined behaviors that can accompany memory bugs.

## Running checks

From the repository root:

```sh
make ci
```

Or:

```sh
./scripts/run-safe-checks.sh
```

## Git identity

Configure Git before committing:

```sh
git config --global user.name "Your Name"
git config --global user.email "you@example.com"
```
