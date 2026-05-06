# Lab 09 — TLV parser

## Purpose

Parse **type–length–value** tuples with strict **remaining-length** checks.

## Vulnerable pattern

Using `len` from the wire without verifying `offset + len <= message_bytes`.

## Detection

- **ASan** on crafted buffers (`make vulnerable`).
- Fuzzing (see Lab 10) on parsers derived from this pattern.

## Remediation

Track cursor + `MAX_TLV_LEN`, reject overflow and truncation.

## Commands

`make fixed`, `make analyze-safe`, `make vulnerable` (local).

## Security scope

Educational TLV bounds enforcement.
