# Lab 14 — Hashing integrity checker

## Purpose

Demonstrate **SHA-256** over a canonical string using **CommonCrypto** and compare to an **embedded expected digest** (macOS).

## Concept

Integrity checks require deterministic inputs, stable encoding, and careful handling of comparisons.

## Commands

```sh
cd labs/14-hashing-integrity-checker
make run
make analyze
```

## Security scope

Integrity illustration only; not a full HSM/KMS lesson.
