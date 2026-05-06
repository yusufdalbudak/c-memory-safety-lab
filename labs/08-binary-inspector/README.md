# Lab 08 — Binary inspector

## Purpose

Parse an ad-hoc binary record **defensively**: verify magic, **clamp** claimed lengths, and ensure copies stay inside the buffer.

## Concept

Length fields inside messages are **attacker-controlled** until authenticated in context.

## Vulnerable pattern

`memcpy(dest, payload, claimed_len)` when `claimed_len` exceeds captured bytes.

## Detection

- **ASan** (`make vulnerable`) for out-of-bounds reads.
- **cppcheck** plus manual length algebra.

## Remediation

`min(claimed, available)` under a **global cap**, explicit checks before every copy.

## Commands

`make fixed`, `make analyze-safe`, `make vulnerable` (local only).

## Security scope

**Defensive structural inspection**, not exploitation.
