# Lab 04 — Use-after-free

## Purpose

Illustrate **use-after-free (UAF)**: dereferencing memory after **`free`** yields undefined behavior and is detected by **AddressSanitizer** as a heap use-after-free.

## Concept

Ownership and **lifetime** end at `free`. Any pointer to that block must not be read or written afterward unless re-assigned from a new valid allocation.

## Vulnerable pattern

`free(p);` followed by `*p` or `p[i]` (or passing `p` to an API) without resetting `p` or establishing a new owner.

## Detection

- **ASan** (`make vulnerable`): reports heap-use-after-free on read.
- **cppcheck** may flag patterns; primary signal here is runtime.

## Remediation

Copy needed data **before** `free`, set pointers to **`NULL`**, prefer **single-owner** discipline, or use arenas/clear ownership in larger designs.

## Commands

```sh
cd labs/04-use-after-free
make fixed
make analyze-safe
make analyze-vuln
make clean
```

Local-only ASan demo:

```sh
make vulnerable
```

## Expected output

- `make fixed`: prints stored value; no dereference after free.
- `make vulnerable`: ASan error and abort.

## Security scope

**Defensive only.** UAF is a common precondition for real-world memory corruption; this lab shows **detection**, not exploitation.
