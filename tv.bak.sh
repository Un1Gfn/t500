#!/bin/bash

# /usr/local/bin/mpv.sh

# TODO
# openvt https://superuser.com/a/819299/

export DISPLAY=:0.0
export XAUTHORITY=/home/darren/.Xauthority
export XDG_RUNTIME_DIR=/run/user/1000

# https://wiki.archlinux.org/title/Youtube-dl#Faster_downloads
EXT="external-downloader=aria2c,external-downloader-args=-j3 -c -x3 -k1M -s3"
ID=""
AO=false
DEBUG=false

MPV=(
  --fs
  --pause
  --cache=yes
  --cache-secs=90
  --demuxer-readahead-secs=180
  --demuxer-max-back-bytes=2G
  --demuxer-max-bytes=2G
  # mpv(1) - Keyboard Control - Q - store the current playback position
  # --no-resume-playback
)

function play_file {
  if "$DEBUG"; then
    echo "("
    for i in "${MPV[@]}"; do
      echo "  $i"
    done
    echo ")"
  fi
  free -h
  source /proxy.bashrc 1>/dev/null
  exec mpv "${MPV[@]}" "$ID"
  echo "${FUNCNAME[0]}() unreachable"
  exit 1
}

function play_stream {
  "$DEBUG" && echo "${MPV[*]}"
  # exit 1
  free -h
  exec streamlink \
    --http-proxy "socks5h://127.0.0.1:1080" \
    -p "mpv" \
    -a "${MPV[*]}" \
    -v \
    --stream-segment-threads 2 \
    --ringbuffer-size 64M \
    "https://www.youtube.com/watch?v=$ID" \
    1080p
  echo "${FUNCNAME[0]}() unreachable"
  exit 1
}

function play_archive {
  if "$DEBUG"; then
    echo "("
    for i in "${MPV[@]}"; do
      echo "  $i"
    done
    echo ")"
  fi
  # exit 1
  # shellcheck disable=SC1091
  free -h
  source /proxy.bashrc 1>/dev/null
  exec mpv "${MPV[@]}" "ytdl://$ID"
  echo "${FUNCNAME[0]}() unreachable"
  exit 1
}

function help {
  echo "$(basename "$0") [-adh] URL"
}

{

  while getopts 'adh' name; do case "$name" in
    a)
      echo audio_only
      AO=true
      ;;
    d)
      DEBUG=true
      ;;
    # Excessive/Superfluous
    # h)
    #   help
    #   exit 1
    #   ;;
    *)
      help
      exit 1
      ;;
  esac;  done
  shift "$((OPTIND-1))"

  [ "$(whoami)" = darren ] || {
    echo "unprivileged user required"
    exit 1
  }

  case "$1" in
    *yandex*|*ipfs.io*)
        MPV+=(--vf-add=fps=30:round=near)
        ID="$1"
        play_file
        ;;
  esac

  case "${1^^?}" in
    "ANN") set -- 'https://www.youtube.com/watch?v=coYw-eVU0Ks' ;;
    "TVBS") set -- 'https://www.youtube.com/watch?v=2mCSYvcfhtc' ;;
  esac

  # set -- 'https://www.youtube.com/watch?v=yL7ndXwvBu4&list=WL&index=5&t=8631s'
  # set -- 'https://www.youtube.com/watch?v=yL7ndXwvBu4&list=WL&index=5'
  if ((1==$#)) && {
    [[ "$1" =~ ^(https://(www.youtube.com/watch\?v=|youtu.be/)([A-Za-z0-9_-]{11})).*t=([0-9]+) ]] ||
    [[ "$1" =~ ^(https://(www.youtube.com/watch\?v=|youtu.be/)([A-Za-z0-9_-]{11})) ]];
  }; then
    # for i in {0..11}; do
    #   echo "[$i] ${BASH_REMATCH[i]}"
    # done
    ID="${BASH_REMATCH[3]}"
    START="${BASH_REMATCH[4]}"
    [[ "$ID" =~ ^[A-Za-z0-9_-]{11}$ ]] || exit 1
    echo "[3] $ID"
    if [ 1 -le "$START" ] 2>/dev/null; then
      echo "[4] $START"
      MPV+=(--start="$START")
    fi
  else
    help
    exit 1
  fi

  X="$(yt-dlp --proxy socks5://127.0.0.1:1080 -q -F "https://www.youtube.com/watch?v=$ID" 2>&1)"
  if [[ "$X" =~ This\ live\ event\ will\ begin\ in\ (.*)\.$ ]]; then
    echo "${BASH_REMATCH[0]}"
    echo "${BASH_REMATCH[1]}"
    # date -ud'19700101 10 minutes' +%s
    # sleep half, then query again
    exit
  fi

  "$AO" && {
    grep -e '^140 .*mp4a\.40\.2 ' <<<"$X" && {
      MPV+=(--vid=no)
      MPV+=(--ytdl-format=140)
      play_archive
    }
    echo "audio not found"
    exit 1
  }

  grep -e '^96.* avc1.640028 ' <<<"$X" && {
    play_stream
  }

  grep -e '^301 .*avc1\.4d402a ' <<<"$X" && {
    MPV+=(--vf-add=fps=30:round=near)
    play_stream
  }

  grep -e '^140 .*mp4a\.40\.2 ' <<<"$X" && {
    MPV+=(--ytdl-raw-options="$EXT")
    grep -e '^137.*avc1\.640028 ' <<<"$X" && {
      MPV+=(--ytdl-format="140+137")
      play_archive
    }
    # grep -e '^299 .*avc1\.64002a ' <<<"$X" && {
    grep -e '^303 .*vp9 ' <<<"$X" && {
      # MPV+=(--ytdl-format="140+299")
      MPV+=(--ytdl-format="140+303")
      MPV+=(--vf-add=fps=30:round=near)
      play_archive
    }
    echo "invalid archive vcodec "
    exit 1
  }

  echo "unknown type"
  exit 1

}; exit
