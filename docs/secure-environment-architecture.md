# Secure environment architecture (defensive)

This document describes how to think about **architecture**, **controlled execution**, and **layers of mitigation** when you work in C—especially with **intentionally vulnerable** teaching code. It stays on the **defensive** side: how to **design** and **operate** environments so memory-safety work improves real systems rather than widening risk.

## 1. Goals

- **Contain defect demonstrations** to machines and accounts you control.
- **Separate** “learning / sanitizer / static-analysis” workflows from anything that looks like production or shared multi-tenant hosting.
- **Make policy explicit**: which binaries may crash, which networks they may touch, which data they may see.

## 2. Execution zones (mental model)

| Zone | Role | Typical activities | Vulnerable crash demos |
|------|------|--------------------|-------------------------|
| **Dev workstation** | Authoring, debugging | `make`, local `make vulnerable`, ASan/UBSan | Allowed **only** with synthetic data, no secrets, no elevated privilege you do not need |
| **CI / automation** | Regression gates | `make ci` (safe targets only) | **Not allowed**—CI must not rely on intentional aborts |
| **Staging / prod-style** | Integration, real services | Hardened builds, monitoring, least privilege | **Never** run this repository’s vulnerable targets here |

“Attack **reproduction**” in this course means: **reproduce the *mechanism*** (illegal read/write, UAF, overflow) under **sanitizers** to **learn detection and fixes**—not to craft reliable exploitation chains, shellcode, or bypasses.

## 3. Architectural layers (where mitigations live)

A simplified stack for memory-corruption risk:

1. **Language and API choice** — bounded length discipline (`strlcpy`, explicit sizes), overflow-checked sizing (`__builtin_mul_overflow`), fewer foot-guns.
2. **Compiler / linker** — high warning levels, `-Wformat`, `-fstack-protector` (where appropriate), **FORTIFY_SOURCE** with optimizations, **Link Time Optimization** only when your team owns the validation cost.
3. **Dynamic verification** — **ASan**, **UBSan** in **dev** and targeted tests; **fuzzing** (Lab 10) on parsers; **cppcheck** / other static analysis in CI.
4. **Process isolation & OS** — separate UID/working directory, no shared secrets in env, filesystem permissions, macOS **hardened runtime** and platform defaults (ASLR, etc.) where applicable to your deliverable—not to the tiny lab binaries themselves.
5. **Operational** — patch cadence, dependency review, minimal blast radius if a bug ships.

Labs **16–17** add **application-level** patterns (canaries, zeroization) that complement—but do **not** replace—platform mitigations.

## 4. Build profiles: “dev insight” vs “hardened shape”

- **Dev / sanitizer profile** (`-fsanitize=address,undefined`, `-g`, strong warnings): maximizes **detectability** during development; binaries are slower and not for production.
- **Hardened profile** (e.g. `-O2`, `-D_FORTIFY_SOURCE=2`, `-fstack-protector-strong`): closer to how many teams compile **release** servers and agents—**defense in depth** at compile time, not proof of memory safety.

See **Lab 18 — Secure build profiles** for a minimal side-by-side build you can compile locally.

## 5. Data and secrets

- Vulnerable programs must **never** process real credentials, customer data, or live traffic captures unless your organisation explicitly authorises a **controlled** forensic lab.
- After handling sensitive **test** material, use patterns like **volatile zeroization** (Lab 17) or platform APIs (`explicit_bzero` where available) for **short-lived** buffers—not as a full key-management story.

## 6. What this repository does *not* teach

No **credential theft**, **persistence**, **bypass** of platform protections, **unauthorised scanning**, or **weaponised** exploit engineering. Those are out of scope for both **SECURITY.md** and this architecture note.

## 7. Related documents

- [SECURITY.md](../SECURITY.md) — legal/educational scope
- [lab-methodology.md](lab-methodology.md) — vulnerable → static analysis → sanitizer → fix
- [macos-setup.md](macos-setup.md) — tools on Apple platforms
- [secure-c-coding-notes.md](secure-c-coding-notes.md) — concise C defensive habits
