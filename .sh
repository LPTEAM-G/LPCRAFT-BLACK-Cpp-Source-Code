#!/usr/bin/env bash
set -euo pipefail

SRC_DIR="${1:-src}"

if [ ! -d "$SRC_DIR" ]; then
    echo "错误：目录不存在：$SRC_DIR" >&2
    exit 1
fi

find "$SRC_DIR" -type f -name '*.hpp' -print0 |
while IFS= read -r -d '' file; do
    # 找第一个 #ifndef
    ifndef_line=$(grep -n -m1 -E '^[[:space:]]*#ifndef[[:space:]]+' "$file" | cut -d: -f1 || true)
    if [ -z "$ifndef_line" ]; then
        continue
    fi

    # 在 #ifndef 之后找第一个 #define
    define_line=$(awk -v s="$ifndef_line" \
        'NR > s && /^[[:space:]]*#define[[:space:]]+/ { print NR; exit }' "$file")
    if [ -z "$define_line" ]; then
        echo "[跳过] 未找到 #define：$file"
        continue
    fi

    # 确认两个宏名一致
    ifndef_macro=$(sed -n "${ifndef_line}p" "$file" \
        | sed -E 's/^[[:space:]]*#ifndef[[:space:]]+([A-Za-z_][A-Za-z0-9_]*).*/\1/')
    define_macro=$(sed -n "${define_line}p" "$file" \
        | sed -E 's/^[[:space:]]*#define[[:space:]]+([A-Za-z_][A-Za-z0-9_]*).*/\1/')
    if [ "$ifndef_macro" != "$define_macro" ]; then
        echo "[跳过] #ifndef/#define 宏名不一致：$file"
        continue
    fi

    # 从底部往上找最后一个 #endif
    endif_line=$(grep -n -E '^[[:space:]]*#endif' "$file" | tail -n1 | cut -d: -f1 || true)
    if [ -z "$endif_line" ] || [ "$endif_line" -le "$define_line" ]; then
        echo "[跳过] 未找到匹配的 #endif：$file"
        continue
    fi

    # 用 #pragma once 替换 #ifndef，删掉 #define 和末尾 #endif
    tmp=$(mktemp)
    awk -v il="$ifndef_line" -v dl="$define_line" -v el="$endif_line" '
        NR == il { print "#pragma once"; next }
        NR == dl { next }
        NR == el { next }
        { print }
    ' "$file" > "$tmp"

    mv "$tmp" "$file"
    echo "[已改] $file"
done