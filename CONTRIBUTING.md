# Contributing

Thank you for helping improve this **educational, defensive** C lab series.

## Principles

- Keep content **defensive**: teach **detection**, **analysis**, and **remediation** — not exploitation, shellcode, persistence, credential theft, bypass tricks, or unauthorised scanning.
- **Intentionally vulnerable** code must be **clearly labelled**, confined to specific labs, and **excluded** from `make ci` if it is expected to crash under sanitizers.
- Do not commit **secrets**, credentials, **real** PCAPs with sensitive traffic, or **build outputs** (`build/`, `*.o`, etc.).
- Prefer **Apple Clang**-compatible C17 and POSIX-friendly patterns that work on **macOS** / **Apple Silicon**.

## Suggested workflow

1. Open an issue or draft PR describing the lab or doc change.
2. Add or extend a lab under `labs/<nn-topic>/` with `README.md`, `Makefile`, and sources.
3. Extend **root** `Makefile` `ci` only with **safe** targets.
4. Run `make clean && make ci` before pushing.
5. Update `docs/roadmap.md` if you add or reorder planned topics.

## Code style

- Match existing Makefiles and C style (clear names, minimal magic numbers, explicit error messages).
- Document **Security scope** in each lab README.

## Security reports

If you discover a **real-world** security issue in how this repo is **consumed** (for example, misleading instructions that encourage unsafe deployment), please open a private discussion or follow repository contact guidance rather than filing public exploit detail.
