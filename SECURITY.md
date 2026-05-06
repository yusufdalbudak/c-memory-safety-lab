# Security policy and scope

## Nature of this project

This is an **educational** and **defensive** project. It teaches secure C practices, static analysis, and sanitizer-assisted verification using **synthetic** examples.

## Intentionally vulnerable examples

Some source files are **deliberately unsafe** (for example, a stack buffer overflow demo). They exist **only** to support **local** learning with **AddressSanitizer**, **UndefinedBehaviorSanitizer**, and **static analysis**. They are **not** production code.

**The project must only be used in local or authorised environments.** Do not run untrusted inputs through sample programs, deploy lab binaries to production, or use vulnerable demos outside a controlled lab setup.

For a defensive framing of **where** vulnerable code may run versus **CI / production**, and how **toolchain hardening** fits your architecture, see [docs/secure-environment-architecture.md](docs/secure-environment-architecture.md).

## Out of scope

This repository does **not** endorse or provide:

- Exploit chains, shellcode, or weaponised proofs of concept  
- Credential theft, persistence, or defence bypass  
- Unauthorised network scanning or access  

Contributions should stay aligned with **defensive** security engineering.

## Reporting

Use GitHub Issues for **non-sensitive** documentation or lab correctness problems. For sensitive coordination, follow any contact instructions posted in the repository or organisation profile.

## Disclaimer

Materials are provided **as-is** for learning. Authors and contributors are not responsible for misuse outside educational, authorised contexts.
