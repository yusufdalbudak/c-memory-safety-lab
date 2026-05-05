# Security Guidance

This repository includes learning material and example code to demonstrate memory safety concepts in C.

## Important notes
- Do not treat this code as production-ready security software.
- The sample code is intended for educational use only.
- Always review and sanitize inputs when writing C code.
- Avoid storing secrets, credentials, or sensitive data in Git repositories.

## Secure coding best practices shown here
- Validate buffer sizes before copying data
- Prefer bounded APIs such as `strlcpy` and `snprintf`
- Use compiler warnings and sanitizers to catch unsafe behavior
- Document unsafe code paths clearly so reviewers understand the risk
