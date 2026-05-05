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

## After fixing: verify

Re-run analysis and sanitizer builds. For labs with a **fixed** target, ensure the remediated path passes your safe CI recipe.
