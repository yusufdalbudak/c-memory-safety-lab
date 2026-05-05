# Lab 02 — Stack buffer overflow

## Purpose

Demonstrate a **deliberate** stack buffer overflow for **static analysis** and **sanitizer** study, alongside a **remediated** program that avoids the unsafe write.

## Concept

A **stack-allocated** buffer has a compile-time-fixed size. Writing past its end corrupts adjacent stack state; sanitizers catch this as an illegal store.

## Vulnerable pattern

Copying an attacker-sized (or in this demo, simply oversized) string into a small stack buffer using `strcpy` **without** a length guard.

## Detection

- **AddressSanitizer**: run `make vulnerable` locally — the process is expected to **abort** when the overflow is detected (this target is **not** run in CI).
- **Static analysis**: `make analyze-vuln` runs cppcheck on `src/vulnerable.c`.
- **Safe comparison**: `make analyze-safe` analyzes `src/fixed.c`.

## Remediation

The `fixed` example validates length before copy and rejects oversized input, avoiding the out-of-bounds write on the synthetic payload.

## Commands

```sh
cd labs/02-stack-buffer-overflow
make fixed
make analyze-safe
make analyze-vuln
make clean
```

**Vulnerable runtime demo** (crashes under ASan — local only):

```sh
make vulnerable
```

From repository root:

```sh
make lab-02
```

## Expected output

- `make fixed`: prints validation message and safely rejects the long payload; exits 0.
- `make analyze-safe`: cppcheck on `fixed.c`.
- `make analyze-vuln`: cppcheck on `vulnerable.c` (may report unsafe API usage).
- `make vulnerable`: ASan **error** and process exit (non-zero); do not automate this in CI.

## Security scope

**Educational and defensive.** `vulnerable.c` exists **only** for controlled local demonstration with sanitizers and static analysis. Do **not** deploy or reuse vulnerable patterns in production. Use only in **local** or **authorised** environments.
