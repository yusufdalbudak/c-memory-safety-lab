# Lab 13 — TCP metadata checker (offline)

## Purpose

Interpret a **stored TCP header prefix**, validating **data offset** against segment length.

## Concept

`doff * 4` must fit in the bytes you actually captured.

## Vulnerable pattern

`memcpy` based on declared header length that exceeds the segment buffer.

## Commands

`make fixed`, `make analyze-safe`, `make vulnerable` (local).

## Security scope

Offline defensive parsing; not a live traffic interceptor.
