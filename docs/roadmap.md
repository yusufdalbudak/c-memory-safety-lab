# Roadmap — progressive C cybersecurity labs

This roadmap orders topics from foundational memory and string safety toward **defensive** parsing, tooling, and **offline** analysis. Future labs should stay **educational**, include **safe** CI targets, and isolate any **crash demos** to explicit local-only goals.

| # | Topic | Focus |
|---|--------|--------|
| 01 | Secure string handling | Bounds, truncation policy, bounded APIs |
| 02 | Stack buffer overflow | ASan signals, cppcheck, remediation |
| 03 | Heap overflow | Allocator discipline, overrun detection |
| 04 | Use-after-free | Lifetime, pointers, sanitizer reports |
| 05 | Integer overflow | Width, signedness, allocation sizing |
| 06 | Format string bugs | Safe logging, constant format strings |
| 07 | Secure file parsing | Size limits, schemas, rejection on anomaly |
| 08 | Binary inspector | **Defensive** structure/size validation (no exploits) |
| 09 | TLV parser | Type-length-value bounds and rejection |
| 10 | Fuzzing harness | libFuzzer/AFL-style **local** fuzzing of parsers |
| 11 | PCAP offline analysis | Parse **captured** files locally; no live scanning |
| 12 | DNS response parser | **Defensive** parsing of saved messages |
| 13 | TCP metadata checker | Header sanity checks on **stored** segments |
| 14 | Hashing integrity checker | Compare digests for file **integrity** |
| 15 | Secure mini toolkit | Composed patterns: config, logging, errors |
| 16 | Memory canary guard | Detect spills with sentinel words around buffers |
| 17 | Secure memory zeroization | Volatile clearing before secret buffers are reused |

Status: **01–17** are implemented in this repository.
