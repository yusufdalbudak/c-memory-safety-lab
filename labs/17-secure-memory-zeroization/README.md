# Lab 17 — Secure memory zeroization

## Purpose

Demonstrate why **sensitive buffers must be cleared** when the secret is retired (logout, credential rotation, error paths). Residual bytes in `.bss`/static storage can **leak** into later logic or debugging output.

## Concept

`memset` on a buffer ending its lifetime can be **optimized away** if the compiler proves the write is dead. A **volatile** clearing loop (`secure_zero`) models the defensive pattern used by many crypto libraries (until platform-specific intrinsics such as `explicit_bzero`/`memset_s` are available).

## Vulnerable pattern

Reusing a **global scratch** for secrets without wiping before reassignment—`strncpy(..., "", ...)` does **not** clear trailing bytes from the previous secret.

## Detection

- Code review of secret lifetimes.
- Dynamic tools (Valgrind-like confidentiality checks are rare); rely on **policy** + review.

## Remediation

- `secure_zero` (or platform `explicit_bzero` where available) **before** releasing a buffer.
- Prefer **scoped** secrets with documented lifetime; avoid long-lived `static` buffers when possible.

## Commands

`make fixed`, `make analyze-safe`, `make vulnerable` (shows stale preview).

## Security scope

Illustrates **confidentiality hygiene** in C; combine with privilege separation and hardware protections in real systems.
