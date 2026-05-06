# Lab 16 — Memory canary guard

## Purpose

Show how **sentinel values** (canaries) placed **around** a sensitive buffer can detect **adjacent memory corruption** when you **check them** before trusting the buffer.

## Concept

Compilers insert stack canaries automatically, but you can use the same idea for **hand-rolled structs**: a known pattern before/after `scratch[]` that must remain unchanged after writes.

## Vulnerable pattern

Copying with `strcpy` into a small field **without** length discipline **and** **without** verifying guards—overflow silently clobbers metadata you care about.

## Detection

- **Manual checks**: compare `pre_guard` / `post_guard` after operations.
- **ASan** (`make vulnerable`): still catches the overflow; canaries are a **logic** safety net when sanitizers are not enabled.

## Remediation

- Enforce **bounded** copies (`memcpy` with validated lengths).
- **Verify** guards on every exit path that mutates the buffer.

## Commands

`make fixed`, `make analyze-safe`, `make vulnerable` (local ASan crash expected).

## Security scope

Defensive pattern only; not a substitute for memory-safe languages or platform exploit mitigations.
