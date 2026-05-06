# Progressive C cybersecurity labs

Structured, **defensive** C exercises from beginner patterns to advanced topics (static analysis, sanitizers, safe parsing, fuzzing, and **offline** capture handling). Each directory under `labs/` is a self-contained module with its own `Makefile` and `README.md`.

## Vision

- Teach **memory safety**, **secure API choice**, and **verification** (compile-time warnings, cppcheck, ASan/UBSan).
- Explain **defensive architecture**: where vulnerable demos may run, how CI stays safe, and how **hardened builds** complement sanitizers—see [docs/secure-environment-architecture.md](docs/secure-environment-architecture.md).
- Keep **intentionally vulnerable** programs **labelled**, **local**, and **out of CI** where they are expected to crash.
- Stay suitable for **macOS / Apple Silicon** using Apple Clang and GNU Make (`CommonCrypto` in Lab 14).

## Repository layout

```text
labs/01-secure-string-handling/     # Strings & bounds
labs/02-stack-buffer-overflow/
labs/03-heap-buffer-overflow/
labs/04-use-after-free/
labs/05-integer-overflow/
labs/06-format-string/
labs/07-secure-file-parsing/       # File size caps
labs/08-binary-inspector/
labs/09-tlv-parser/
labs/10-fuzzing-harness/          # Parser + deterministic stress loop (+ optional libFuzzer)
labs/11-pcap-offline-analysis/
labs/12-dns-response-parser/
labs/13-tcp-metadata-checker/
labs/14-hashing-integrity-checker/
labs/15-secure-mini-toolkit/
labs/16-memory-canary-guard/    # Manual canaries around buffers
labs/17-secure-memory-zeroization/
labs/18-secure-build-profiles/    # Dev vs hardened compiler profiles
docs/                              # Roadmap, methodology, setup, notes
scripts/                           # Convenience wrappers
```

## Roadmap

See [docs/roadmap.md](docs/roadmap.md) for topic order and focus.

## Quick start

Requirements: **Apple Clang**, **GNU Make**, **cppcheck** (see [docs/macos-setup.md](docs/macos-setup.md)). Lab **10** also runs a **stress** harness under **ASan/UBSan**; optional **`make -C labs/10-fuzzing-harness fuzz-libfuzzer`** needs a Clang build that ships the **libFuzzer** runtime (not present in all Xcode toolchains).

```sh
git clone https://github.com/yusufdalbudak/c-memory-safety-lab.git
cd c-memory-safety-lab
make ci
```

### Run individual labs

```sh
make lab-01    # secure strings (run)
make lab-02    # … through lab-09, 11–13, 16–17: safe `fixed` demo
make lab-10    # harness demo (make run)
make lab-14    # SHA-256 demo (make run)
make lab-15    # mini toolkit (make run)
make lab-16    # memory canaries (fixed)
make lab-17    # secure zeroization (fixed)
make lab-18    # secure build profiles (dev profile)
```

Or: `./scripts/run-lab.sh 07` … `./scripts/run-lab.sh 18`.

### Safe CI target (no intentional crash demos)

`make ci` runs Lab 01 `run`, `sanitize`, `analyze`; Labs **02–09, 11–13, 16–17** `fixed` + `analyze-safe`; Lab **10** `run`, **`stress`**, and **`analyze`**; Labs **14–15** `run` + **`analyze`**; Lab **18** `dev`, **`hardened`**, and **`analyze`**. It never runs **`make vulnerable`** targets.

## Documentation

| Document | Description |
|----------|-------------|
| [docs/roadmap.md](docs/roadmap.md) | Planned lab sequence |
| [docs/lab-methodology.md](docs/lab-methodology.md) | How each lab is structured |
| [docs/secure-c-coding-notes.md](docs/secure-c-coding-notes.md) | Short defensive C notes |
| [docs/secure-environment-architecture.md](docs/secure-environment-architecture.md) | Zones, mitigations, controlled execution model |
| [docs/macos-setup.md](docs/macos-setup.md) | Toolchain and tools on macOS |
| [SECURITY.md](SECURITY.md) | Scope and responsible use |
| [CONTRIBUTING.md](CONTRIBUTING.md) | How to contribute |

## License

See [LICENSE.md](LICENSE.md).
