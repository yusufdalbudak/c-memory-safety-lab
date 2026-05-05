# Lab methodology

Each lab follows a consistent **defensive** learning loop so skills transfer from exercises to real code review and assurance work.

## 1. Vulnerable pattern

We state a **clearly labelled** unsafe pattern (for example, unbounded copy into a stack buffer). Where code is intentionally unsafe, it is kept for **local** sanitizer and static-analysis demos, never as a shipped “feature.”

## 2. Static analysis

We run **cppcheck** (and compiler warnings) against scoped sources. You compare messages on **vulnerable** vs **remediated** code to see how tools surface risky APIs and control flow.

## 3. Runtime sanitizer detection

With **AddressSanitizer** and **UndefinedBehaviorSanitizer**, illegal memory accesses and certain undefined behaviors fail fast with actionable reports. Labs separate:

- **CI-safe** targets (no intentional crash), and  
- **Local-only** targets that are **expected** to abort when demonstrating a bug class.

## 4. Root-cause analysis

You connect the tool output to **why** the program violated the language memory model: which assumption failed (size, lifetime, encoding, integer range).

## 5. Secure remediation

The lab ends with a **fixed** variant or checklist: validation order, bounded APIs, error handling, tests, and documentation so reviewers understand trust boundaries.

This methodology is **not** about building exploits; it is about **recognising** defects, **proving** them with tools, and **fixing** them systematically.
