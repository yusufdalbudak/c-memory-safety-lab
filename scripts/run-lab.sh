#!/usr/bin/env bash
set -euo pipefail

ROOT="$(cd "$(dirname "${BASH_SOURCE[0]}")/.." && pwd)"
cd "$ROOT"

usage() {
  echo "Usage: $(basename "$0") <01|02|03|04|05|06>" >&2
  echo "  01 — secure string handling (make run)" >&2
  echo "  02–06 — memory/format labs: safe path (make fixed) or run for 01" >&2
  exit 1
}

[[ ${1-} ]] || usage

case "$1" in
  01)
    exec make -C labs/01-secure-string-handling run
    ;;
  02)
    exec make -C labs/02-stack-buffer-overflow fixed
    ;;
  03)
    exec make -C labs/03-heap-buffer-overflow fixed
    ;;
  04)
    exec make -C labs/04-use-after-free fixed
    ;;
  05)
    exec make -C labs/05-integer-overflow fixed
    ;;
  06)
    exec make -C labs/06-format-string fixed
    ;;
  *)
    usage
    ;;
esac
