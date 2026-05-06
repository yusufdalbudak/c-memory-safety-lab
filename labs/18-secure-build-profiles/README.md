# Lab 18 — Secure build profiles (architecture)

## Purpose

Connect **environment design** to **compile-time defenses**: the same small program can be built as a **developer / sanitizer** binary (high detection) or a **hardened release-style** binary (FORTIFY_SOURCE, stack protector, optimization).

## Concept

Security architecture for C code is layered:

- **Dev builds** prioritise **observability** (ASan/UBSan, assertions, logging).
- **Release-style builds** prioritise **hardening flags** appropriate to your threat model—but hardened builds **do not** prove absence of bugs; they raise the cost of exploitation and catch some API misuses at compile/runtime.

## Commands

```sh
cd labs/18-secure-build-profiles
make dev       # AddressSanitizer + UndefinedBehaviorSanitizer + -O0 + debug info
make hardened  # -O2 -D_FORTIFY_SOURCE=2 -fstack-protector-strong
make analyze   # cppcheck
make clean
```

## Expected output

Both `dev` and `hardened` print the same demo line; the **difference** is the **compiler/link flags** (inspect the `Makefile`). Use `llvm-objdump`, `otool`, or size(1) locally if you want to compare binaries.

## Security scope

**Educational.** This lab does **not** exploit anything—it illustrates how **toolchain choices** are part of a **secure delivery architecture**. Read [docs/secure-environment-architecture.md](../../docs/secure-environment-architecture.md) for the full defensive model (zones, CI vs local-only vulnerable runs).

## Relation to “attack execution”

In this repository, **attack execution** means **reproducing a defect class under controlled conditions** (e.g. `make vulnerable` with synthetic input on your own machine), **not** attacking third-party systems. **CI** (`make ci`) stays on **safe** targets only.
