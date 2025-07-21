#!/bin/bash

flag_n=false
flag_b=false
flag_s=false
flag_t=false

# Поддержка нескольких флагов
while [[ "$1" == -* ]]; do
  case "$1" in
    -n) flag_n=true ;;
    -b) flag_b=true ;;
    -s) flag_s=true ;;
    -t) flag_t=true ;;
    -*) echo "Неизвестный флаг: $1" >&2 ;;
  esac
  shift
done

for file in "$@"; do
  if [ ! -f "$file" ]; then
    echo "Файл $file не найден"
    continue
  fi

  line_number=1
  prev_empty=false

  while IFS= read -r line; do
    # -t: замена табов на ^I
    if [ "$flag_t" = true ]; then
      tab_char=$'\t'
      line="${line//    /^I}"
    fi

    # -s: подавление повторяющихся пустых строк
    if [ "$flag_s" = true ]; then
      if [ -z "$line" ]; then
        if [ "$prev_empty" = true ]; then
          continue
        fi
        prev_empty=true
      else
        prev_empty=false
      fi
    fi

    # -b: нумерация только непустых строк
    if [ "$flag_b" = true ]; then
      if [ -n "$line" ]; then
        printf "%6d\t%s\n" "$line_number" "$line"
        ((line_number++))
      else
        echo ""
      fi

    # -n: нумерация всех строк (если -b не указан)
    elif [ "$flag_n" = true ]; then
      printf "%6d\t%s\n" "$line_number" "$line"
      ((line_number++))

    else
      echo "$line"
    fi
  done < "$file"
done