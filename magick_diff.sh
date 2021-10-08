#!/bin/bash

H=512
# schemx.rom = 4232878B = 4MiB+37KiB+686B
W=$((8192+128))
D=/tmp/im

function md2 {
  printf "\e[32m%s\e[0m\n" "${FUNCNAME[0]}()"
  { [ 2 -eq "$#" ] && [ -f "$1" ] && [ -f "$2" ]; } || return
  rm -rf $D
  mkdir -pv $D
  for i in "$@"; do
    [ "$(stat -c %s "$i")" -le $((H*W)) ] || return
  done
  { cat "$1"; tr "\000" "$(printf "\%03o" $((16#AA)))" </dev/zero; } | head -c $((H*W)) >$D/x1
  { cat "$2"; tr "\000" "$(printf "\%03o" $((16#AA)))" </dev/zero; } | head -c $((H*W)) >$D/x2
  (
    cd $D || exit
    magick convert \( -depth 8 -size ${H}x${W}+0 gray:x1      \) -rotate 270       x1.bmp      || exit
    magick convert \( -depth 8 -size ${H}x${W}+0 gray:x2      \) -rotate 270 -flip x2_flip.bmp || exit
    magick convert \(          -size    1x${W}+0   xc:#FFBF80 \) -rotate 270       split.bmp   || exit
    magick convert -append {x1,split,x2_flip}.bmp diff.bmp || exit
    printf "\e[32m  %s\e[0m\n" "done"
    background gimp $D/diff.bmp
  )
}

function mdN {

  printf "\e[32m%s\e[0m\n" "${FUNCNAME[0]}()"

  (($#>=1)) || { echo "err $LINENO"; return; }
  for i in "$@"; do
    echo "$i"
    [ -f "$i" ] || { echo "err $LINENO"; return; }
  done

  rm -rf $D
  mkdir -pv $D
  for i in "$@"; do
    [ "$(stat -c %s -- "$i")" -le $((H*W)) ]
    NORM="$(tr '/$' '_#' <<<"$i")"
    [[ $NORM =~ [0-9a-zA-Z._#]+ ]] || { echo "err $LINENO"; return; }
    { cat -- "$i"; tr "\000" "$(printf "\%03o" $((16#FF)))" </dev/zero; } | head -c $((H*W)) >$D/"$NORM" || { echo "err $LINENO"; return; }
  done

  cd $D || { echo "err $LINENO"; return; }
  # for i in !(*.bmp); do
  for i in *; do
    [[ $i =~ .*bmp ]] && { echo "err $LINENO"; return; }
    magick convert \( -depth 8 -size ${H}x${W}+0 gray:"$i" \) -rotate 270 "$i".bmp
  done

  # printf "%s.bmp split.bmp " "$@"; printf diff.bmp;
  ARR=()
  for i in *.bmp
    do echo "$i"
    ARR+=("$i" split.bmp)
  done

  [ -e split.bmp ] && { echo "err $LINENO"; return; }
  magick convert \( -size 1x${W}+0 xc:#FFBF80 \) -rotate 270 split.bmp
  magick convert -append "${ARR[@]}" diff.bmp
  printf "\e[32m  %s\e[0m\n" "done"
  background gimp diff.bmp

}

{
  if ((2==$#)); then
    md2 "$1" "$2"
  else
    mdN "$@"
  fi
}; exit
