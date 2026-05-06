# Lab 11 — PCAP offline analysis

## Purpose

Parse a **PCAP global header** from an **in-memory capture** with defensive checks on **snaplen** and available bytes.

## Concept

Offline analysis of **saved** captures; **no live network sniffing** or scanning.

## Vulnerable pattern

Trusting `snaplen` (or packet lengths) for `memcpy` without relating it to actual buffer size.

## Commands

`make fixed`, `make analyze-safe`, `make vulnerable` (local ASan demo).

## Security scope

Defensive parsing instructional content only.
