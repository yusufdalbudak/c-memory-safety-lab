# Lab 01 — Secure string handling

## Purpose

Build intuition for how **unbounded string operations** interact with **fixed buffers**, and how **bounded APIs** and **length checks** reduce risk in defensive C code.

## Concept

Safer string handling in C relies on knowing **source length**, **destination capacity**, and **what happens on truncation** (silent truncate vs reject vs error).

## Vulnerable pattern

Using `strcpy` or similar without a guaranteed bound, or with checks that are easy to get wrong (off-by-one, unsigned wrap, assuming `strlen` is safe alone without tying it to buffer size).

## Detection

- **Compiler warnings** (`-Wall -Wextra -Wpedantic` and friends).
- **Static analysis**: `make analyze` in this lab (cppcheck).
- **Runtime**: `make sanitize` runs the program under ASan/UBSan (this lab’s sample should complete without crashing).

## Remediation

- Prefer **bounded** copies (`strlcpy` where available and appropriate).
- **Reject** or **truncate** explicitly at API boundaries; document the policy.
- Never mix “check then copy” incorrectly; ensure the check matches the **actual** buffer size.

## Commands

```sh
cd labs/01-secure-string-handling
make run
make sanitize
make analyze
make clean
```

From repository root:

```sh
make lab-01
```

## Expected output

- `make run`: prints demonstration of guarded unsafe path vs `strlcpy` path; large input is rejected or truncated with clear messages.
- `make sanitize`: same logical behavior under AddressSanitizer and UndefinedBehaviorSanitizer.
- `make analyze`: cppcheck report for `src/main.c` (informational findings may appear depending on cppcheck version).

## Security scope

**Defensive and educational only.** Sample code illustrates patterns on **synthetic input**; it is not a tool for attacking systems. Use only on **local** or **authorised** machines.
