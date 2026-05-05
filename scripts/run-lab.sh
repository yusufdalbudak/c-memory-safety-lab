#!/usr/bin/env bash
set -euo pipefail

ROOT="$(cd "$(dirname "${BASH_SOURCE[0]}")/.." && pwd)"
cd "$ROOT"

usage() {
  echo "Usage: $(basename "$0") <01|02>" >&2
  echo "  01 — secure string handling (make run)" >&2
  echo "  02 — stack buffer overflow safe path (make fixed)" >&2
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
  *)
    usage
    ;;
esac
