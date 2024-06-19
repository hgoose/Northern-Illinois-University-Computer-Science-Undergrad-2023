#!/usr/bin/env bash

function main {

    local inp sum
    sum=""
    inp="${@,,}"
    
    for item in $inp; do
        [[ ${#sum} -eq 2 ]] && break
        case "${item}" in 
            black) sum+="0" ;;
            brown) sum+="1" ;;
            red) sum+="2" ;;
            orange) sum+="3" ;;
            yellow) sum+="4";;
            green) sum+="5";;
            blue) sum+="6";;
            violet) sum+="7";;
            grey) sum+="8";;
            white) sum+="9";;
            *) echo "invalid color" && exit 1;; 
        esac
    done

    echo "$((10#$sum))"

}
main "$@"
