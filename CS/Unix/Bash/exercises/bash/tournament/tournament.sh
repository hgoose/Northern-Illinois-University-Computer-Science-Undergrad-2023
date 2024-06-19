#!/usr/bin/env bash

function main {

    local t1 t2 result fmt
    fmt='%-30s | %2s | %2s | %2s | %2s | %2s\n'

    declare -A played wins loss draw

    while IFS=\; read -r t1 t2 result; do

        [[ "$t1" && "$t2" && "$result" ]] || continue

        (( ++played[$t1], ++played[$t2] ))

        case "$result" in 
            win) (( ++wins[$t1], ++loss[$t2] )) ;;
            loss) (( ++ wins[$t2], ++loss[$t1] ));;
            draw) (( ++draw[$t1], ++draw[$t2] ));;
        esac
    done 

    printf "$fmt" Team MP W D L P

    local p w l d pt
    for team in "${!played[@]}"; do
        p=${played[$team]:-0}
        w=${wins[$team]:-0}
        l=${loss[$team]:-0}
        d=${draw[$team]:-0}

        pt=$(( (3*w) + (1*d) ))
        printf "$fmt" "$team" "$p" "$w" "$d" "$l" "$pt"
    done | sort -t \| -k 6nr -k 1
} 
main "$@"
