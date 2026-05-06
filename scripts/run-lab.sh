#!/usr/bin/env bash
set -euo pipefail

ROOT="$(cd "$(dirname "${BASH_SOURCE[0]}")/.." && pwd)"
cd "$ROOT"

usage() {
  echo "Usage: $(basename "$0") <01–15, zero-padded>" >&2
  echo "  01 — secure string handling (make run)" >&2
  echo "  02–09,11–13 — safe path (make fixed)" >&2
  echo "  10 — fuzzing harness demo (make run)" >&2
  echo "  14–15 — toolkit / hashing demo (make run)" >&2
  exit 1
}

[[ ${1-} ]] || usage

case "$1" in
  01) exec make -C labs/01-secure-string-handling run ;;
  02) exec make -C labs/02-stack-buffer-overflow fixed ;;
  03) exec make -C labs/03-heap-buffer-overflow fixed ;;
  04) exec make -C labs/04-use-after-free fixed ;;
  05) exec make -C labs/05-integer-overflow fixed ;;
  06) exec make -C labs/06-format-string fixed ;;
  07) exec make -C labs/07-secure-file-parsing fixed ;;
  08) exec make -C labs/08-binary-inspector fixed ;;
  09) exec make -C labs/09-tlv-parser fixed ;;
  10) exec make -C labs/10-fuzzing-harness run ;;
  11) exec make -C labs/11-pcap-offline-analysis fixed ;;
  12) exec make -C labs/12-dns-response-parser fixed ;;
  13) exec make -C labs/13-tcp-metadata-checker fixed ;;
  14) exec make -C labs/14-hashing-integrity-checker run ;;
  15) exec make -C labs/15-secure-mini-toolkit run ;;
  *) usage ;;
esac
