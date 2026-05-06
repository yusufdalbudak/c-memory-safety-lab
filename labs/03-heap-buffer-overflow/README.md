# Lab 03 — Heap buffer overflow

## Purpose

Show how **heap** allocations still need strict bounds: writing past the end of a `malloc`'d object corrupts the heap and is caught by **AddressSanitizer** much like stack overflows.

## Concept

The heap allocator hands you a fixed-size object. **`strcpy`**, **`memcpy`** without a proven length, or arithmetic errors can **overflow** that object into adjacent metadata or data.

## Vulnerable pattern

Allocating a small buffer, then copying a long string into it without checking **`strlen` vs capacity + 1** (for the terminator).

## Detection

- **ASan** (local `make vulnerable`): illegal write past the allocation.
- **cppcheck** (`make analyze-vuln`): unsafe API usage on `vulnerable.c`.
- **Fixed path** (`make fixed`, `make analyze-safe`): validates static cap before copy.

## Remediation

Reject oversize inputs, use **known-length** `memcpy` with `strlen + 1` only after checks, or size the allocation from validated demand (with **overflow-checked** sizing — see Lab 05).

## Commands

```sh
cd labs/03-heap-buffer-overflow
make fixed
make analyze-safe
make analyze-vuln
make clean
```

Local-only crash demo (ASan abort expected):

```sh
make vulnerable
```

## Expected output

- `make fixed`: rejects the long payload; exits 0.
- `make analyze-safe`: cppcheck on `fixed.c`.
- `make vulnerable`: ASan heap-buffer-overflow report and non-zero exit.

## Security scope

**Educational and defensive.** Use `vulnerable.c` only in a **local** sanitizer lab. Do not ship this pattern in production code.
