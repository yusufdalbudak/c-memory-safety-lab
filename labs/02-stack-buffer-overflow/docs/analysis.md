# Stack buffer overflow: AddressSanitizer indicators (defensive notes)

This document supports **local, educational** analysis of how a classic stack buffer overflow surfaces under modern sanitizers. It does not teach exploitation.

## Observed pattern

A fixed-size stack array receives more bytes than its length (for example via `strcpy` without a prior bound check). Execution may appear to succeed without sanitizers; with **AddressSanitizer (ASan)** and **UndefinedBehaviorSanitizer (UBSan)** enabled, the illegal write is detected when it crosses the redzone past the buffer.

## What ASan typically reports (Apple Clang, aarch64)

When you run the **lab 02** `vulnerable` target (not part of CI), you may see:

- **ERROR: AddressSanitizer: stack-buffer-overflow**
- A **WRITE** at an address immediately past the end of the stack object
- A **stack trace** pointing at the offending store (often inside `strcpy` or inlined memory copy)
- **Shadow memory** summary showing the access was classified as invalid

Treat the report as confirmation that the write violated memory safety, not as a map for weaponisation.

## Static analysis (cppcheck)

`cppcheck` on `vulnerable.c` can flag dangerous use of `strcpy` and related APIs depending on configuration. Compare with `analyze-safe` on `fixed.c`, where length validation and rejection of oversized input remove the unsafe write.

## Remediation summary

- **Validate** length (or use bounded APIs with explicit limits) **before** copying.
- Prefer **bounded** interfaces (`strlcpy`, `memcpy` with explicit count, etc.) appropriate to your trust model.
- **Compile** with warnings and run **sanitizers** during development on non-production datasets.

## References

- [Apple Clang documentation](https://developer.apple.com/documentation/xcode) (toolchain and sanitizer flags)
- [AddressSanitizer](https://clang.llvm.org/docs/AddressSanitizer.html) (LLVM project)
