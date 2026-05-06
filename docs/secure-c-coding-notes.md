# Secure C coding notes

Short reminders for **defensive** C on **macOS** (Apple Clang). These support the labs; they are not exhaustive.

## Treat sizes as part of the API

Every function that writes into a buffer should know **destination capacity** in bytes and enforce it before writing. Document whether the API **truncates** or **fails** on overflow.

## Prefer clarity over cleverness

Explicit checks and early returns are easier to audit than compact pointer arithmetic. Pair every `memcpy`/`memmove` with a length derived from verified inputs or constants.

## Enable warnings and sanitizers in development

Use strong warning flags in development builds. Run **ASan** and **UBSan** on unit-style programs and fuzz harnesses **locally**, on non-sensitive data.

## Static analysis in the loop

Run **cppcheck** or your organisation’s analyser on changed files. Treat new findings as regressions unless documented and accepted with compensating controls.

## String and encoding traps

`strlen` is O(n) and says nothing about **allocated** size. Mixing UTF-8 **characters** with **byte** counts causes subtle bugs; be explicit about what “length” means.

## Memory canaries and guard words

Place **known sentinel values** adjacent to high-risk buffers (or rely on compiler stack canaries) and **verify** them after every writer completes. This catches many **single-sided** overflows when sanitizers are not running.

## Zeroize secrets on all paths before reuse

Plain `memset` before `return` may be optimized away. Use **volatile** clearing helpers (or `explicit_bzero` / `memset_s` when available) so credentials do not linger in stack or static storage.

## After fixing: verify

Re-run analysis and sanitizer builds. For labs with a **fixed** target, ensure the remediated path passes your safe CI recipe.
