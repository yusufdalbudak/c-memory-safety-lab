# Progressive C cybersecurity labs

Structured, **defensive** C exercises from beginner patterns to advanced topics (static analysis, sanitizers, safe parsing, and **authorised** network-data handling). Each directory under `labs/` is a self-contained module with its own `Makefile` and `README.md`.

## Vision

- Teach **memory safety**, **secure API choice**, and **verification** (compile-time warnings, cppcheck, ASan/UBSan).
- Keep **intentionally vulnerable** programs **labelled**, **local**, and **out of CI** where they are expected to crash.
- Stay suitable for **macOS / Apple Silicon** using Apple Clang and GNU Make.

## Repository layout

```text
labs/01-secure-string-handling/   # Bounded vs unbounded string handling
labs/02-stack-buffer-overflow/    # Stack overflow + remediation
labs/03-heap-buffer-overflow/     # Heap overflow + remediation
labs/04-use-after-free/          # UAF + remediation
labs/05-integer-overflow/         # Allocation sizing + overflow checks
labs/06-format-string/           # Format string misuse vs constant format
docs/                            # Roadmap, methodology, setup, notes
scripts/                         # Convenience wrappers
```

## Roadmap

See [docs/roadmap.md](docs/roadmap.md) for the full progression (heap overflow, use-after-free, integer issues, format strings, parsing, fuzzing, offline PCAP/DNS/TCP defensive checks, and more).

## Quick start

Requirements: **Apple Clang**, **GNU Make**, **cppcheck** (see [docs/macos-setup.md](docs/macos-setup.md)).

```sh
git clone https://github.com/yusufdalbudak/c-memory-safety-lab.git
cd c-memory-safety-lab
make ci
```

### Run individual labs

```sh
make lab-01    # secure string handling (run)
make lab-02    # stack overflow — safe `fixed` demo
make lab-03    # heap overflow — safe `fixed` demo
make lab-04    # use-after-free — safe `fixed` demo
make lab-05    # integer overflow — safe `fixed` demo
make lab-06    # format string — safe `fixed` demo
```

### Safe CI target (no crash demo)

`make ci` runs Lab 01 `run`, `sanitize`, `analyze`, then Labs 02–06 `fixed` and `analyze-safe`. It never runs **vulnerable** / ASan-aborting targets from those labs.

## Documentation

| Document | Description |
|----------|-------------|
| [docs/roadmap.md](docs/roadmap.md) | Planned lab sequence |
| [docs/lab-methodology.md](docs/lab-methodology.md) | How each lab is structured |
| [docs/secure-c-coding-notes.md](docs/secure-c-coding-notes.md) | Short defensive C notes |
| [docs/macos-setup.md](docs/macos-setup.md) | Toolchain and tools on macOS |
| [SECURITY.md](SECURITY.md) | Scope and responsible use |
| [CONTRIBUTING.md](CONTRIBUTING.md) | How to contribute |

## License

See [LICENSE.md](LICENSE.md).
