#!/usr/bin/env bash

function quit {
    echo "invalid arguments" && exit 1
}

function main {

    (( ($# != 2) && ($# != 4) )) && quit

    for i; do [[ $i =~  ^-?[0-9]+$ || $i =~ [+-] ]] || quit; done

    local hour minute minus_hour operator operand
    hour=$(( (24 + ($1 % 24)) % 24 ))
    minute=$2
    minus_hour=0


    if (( $# > 2 )); then
        local operator operand
        shift 2
        operator=$1
        operand=$2
    fi

    if (( minute >= 60 )); then
        hour=$(( (hour + minute / 60) % 24 ))
        minute=$(( minute % 60 ))
    elif (( minute < 0 )); then

        while (( minute < 0 )); do
            minute=$(( minute + 60 ))
            (( ++minus_hour ))
        done

        hour=$(( (24 + (hour - minus_hour % 24)) % 24 ))

    fi

    if [[ -n $operator && -n $operand ]]; then
        case $operator in 
            +) 
                minute=$(( minute + operand ))

                if (( minute >= 60 )); then
                    hour=$(( (hour + minute / 60) % 24 ))
                    minute=$(( minute % 60 ))
                fi ;;

            -)

            minute=$(( minute - operand ))

            if (( minute < 0 )); then 

                while (( minute < 0 )); do
                    minute=$(( minute + 60 ))
                    (( ++minus_hour ))
                done

                hour=$(( (24 + (hour - minus_hour % 24)) % 24 ))

            fi
            ;;

            *) quit ;;
        esac
    fi

    printf "%02d:%02d" "$hour" "$minute"
}
main "$@"
