# Lab 07 — Secure file parsing

## Purpose

Practice **bounding file reads**: inspect `stat(2)` size, reject oversize inputs, and avoid loading unbounded data into memory.

## Concept

Treat file length as **untrusted metadata** until capped against a defender-chosen maximum.

## Vulnerable pattern

`malloc(file_size)` / `fread` without a **policy cap**, enabling giant-file DoS or OOM in real programs.

## Detection

- **Code review** of read loops and allocation sites.
- **cppcheck** on sources.
- **Sanitizers** help adjacent logic; primary control is policy.

## Remediation

Enforce `MAX_FILE_BYTES`, verify `S_ISREG`, consider streaming parsers for large inputs.

## Commands

```sh
cd labs/07-secure-file-parsing
make fixed
make analyze-safe
```

## Security scope

**Defensive.** Only read files you own; this lab uses `fixtures/sample.txt`.
