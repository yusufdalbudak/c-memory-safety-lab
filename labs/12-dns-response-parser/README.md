# Lab 12 — DNS response parser (offline)

## Purpose

Walk DNS header fields with strict limits on **QDCOUNT** relative to captured bytes.

## Concept

Counts in protocol headers are not trustworthy until bounded.

## Vulnerable pattern

Indexing `header + count` without proving `count` bytes exist.

## Commands

`make fixed`, `make analyze-safe`, `make vulnerable` (local).

## Security scope

**Offline educational** capture handling; not a resolver or live DNS tool.
