# Lab 10 — Fuzzing harness

## Purpose

Introduce **libFuzzer-style** harnesses that exercise a small **bounded parser** (`parse_record`) with random inputs.

## Concept

Fuzzing complements static analysis by exploring shallow parser states quickly **locally**.

## Commands

```sh
cd labs/10-fuzzing-harness
make run     # canned acceptance/rejection vectors
make stress  # deterministic pseudo-random probe loop (runs in CI)
make analyze
make fuzz-libfuzzer   # optional: needs libFuzzer runtime from your Clang build
```

## Detection / workflow

- Regression-test `make run` + `make stress` in CI.
- Run `make fuzz-libfuzzer` locally when your toolchain ships the fuzzer runtime (some Xcode installs omit `libclang_rt.fuzzer_osx`).

## Security scope

**Local-only** probing; no network or dataset exfiltration.
