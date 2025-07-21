#!/bin/bash

flag_i=false
flag_v=false

# Обработка флагов
while [[ "$1" == -* ]]; do
  case "$1" in
    -i) flag_i=true ;;
    -v) flag_v=true ;;
    -*) echo "Неизвестный флаг: $1" >&2 ;;
  esac
  shift
done

pattern="$1"
shift

for file in "$@"; do
  if [ ! -f "$file" ]; then
    echo "Файл $file не найден"
    continue
  fi

  while IFS= read -r line; do
    match=false

    if [ "$flag_i" = true ]; then
      lower_line=$(echo "$line" | tr '[:upper:]' '[:lower:]')
      lower_pattern=$(echo "$pattern" | tr '[:upper:]' '[:lower:]')
      [[ "$lower_line" == *"$lower_pattern"* ]] && match=true
    else
      [[ "$line" == *"$pattern"* ]] && match=true
    fi

    if [ "$flag_v" = true ]; then
      # выводим, если НЕ совпало
      if [ "$match" = false ]; then
        echo "$line"
      fi
    else
      # выводим, если совпало
      if [ "$match" = true ]; then
        echo "$line"
      fi
    fi
  done < "$file"
done