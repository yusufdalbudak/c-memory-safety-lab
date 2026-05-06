# Lab 05 — Integer overflow in sizing

## Purpose

Show how **unsigned size computation** for `malloc` / `memcpy` lengths can **wrap**, producing a **tiny allocation** while the program assumes a huge one—leading to **heap overflows** when it writes further.

## Concept

On a 64-bit platform, multiplying two large `size_t` values can wrap modulo 2⁶⁴. The product is **wrong** but not “undefined” for unsigned types—it is the wrong **logical** size for your safety story.

## Vulnerable pattern

`bytes = count * element` without **`__builtin_mul_overflow`** (or equivalent wide arithmetic) before `malloc(bytes)` and `memset`/`memcpy` with the **untruncated** intent.

## Detection

- **ASan** (`make vulnerable`): illegal store after the true allocated size.
- **UBSan** on **signed** overflow paths (not the primary bug here); still compile with `undefined` for other issues.
- **Code review** and **`__builtin_mul_overflow`** in the fixed path.

## Remediation

Use **overflow-checked multiplication** for allocation sizes; cap untrusted counts and element sizes **before** multiply; reject on overflow or absurd totals.

## Commands

```sh
cd labs/05-integer-overflow
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

- `make fixed`: detects overflow in multiply, prints rejection, exits 0 (no allocation attempt with wrapped size).
- `make vulnerable`: small malloc, `memset(..., 1024)` overflows → ASan error.

## Security scope

**Defensive.** Real parsers and network decoders must size allocations from **checked** arithmetic.
