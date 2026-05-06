# Lab 06 — Format string misuse

## Purpose

Demonstrate why **`printf(variable)`** is unsafe: format specifiers in the string drive reads from the **varargs area** and can leak stack/register-backed data or invoke **`%n`**-style writes on older or careless code paths.

## Concept

The format string is **code**, not data. Untrusted input must not become the first argument to `printf`/`sprintf`/similar.

## Vulnerable pattern

`printf(user_input);` instead of `printf("%s", user_input);`

## Detection

- **Compiler warnings** (`-Wformat-security`) where applicable.
- **cppcheck** on the vulnerable source.
- **Code review** for variable format arguments.

## Remediation

Always use a **constant** format; pass dynamic content as `%s`, `%d`, etc., with matching arguments. For logging, prefer **`fprintf(stderr, "%s", msg)`** or bounded APIs (`snprintf` with limits).

## Commands

```sh
cd labs/06-format-string
make fixed
make analyze-safe
make analyze-vuln
make clean
```

Local-only demo (may leak stack values to stdout; run only in lab):

```sh
make vulnerable
```

## Expected output

- `make fixed`: prints the literal `%x %x %x` as text.
- `make vulnerable`: prints hex values from the varargs/stack area (information disclosure demo).

## Security scope

**Educational.** Do not point this at real secrets or production logs. Keep output on **local** terminals only.
