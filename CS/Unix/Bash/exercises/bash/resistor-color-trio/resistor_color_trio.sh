#!/usr/bin/env bash

function getValue {
    res=""

    case "${1}" in 
        black) res="0" ;;
        brown) res="1" ;;
        red) res="2" ;;
        orange) res="3" ;;
        yellow) res="4";;
        green) res="5";;
        blue) res="6";;
        violet) res="7";;
        grey) res="8";;
        white) res="9";;
        *) echo "invalid color";; 
    esac

    echo "${res}" 
}

function getSuffix {
    res=""
    remain=0

    case "${1}" in
        3) res="kiloohms";;
        4) res="kiloohms" && remain=1;;
        5) res="kiloohms" && remain=2;;
        6) res="megaohms";;
        7) res="megaohms" && remain=1;;
        8) res="megaohms" && remain=2;;
        9) res="gigaohms";;
    esac

    echo $res
}

function getTZ {

    local num stripped diff
    num=$1
    stripped=${num%%0}
    diff=$(( ${#num}-${#stripped} ))

    echo $diff
}

function main {

    local inp sum count last suffix add
    sum=""
    last=""
    count=0
    inp="${@,,}"
    
    for item in $inp; do
        (( count == 3 )) && break
        (( count != 2)) && sum+=$(getValue "$item") ||  last=$(getValue "$item")
        (( ++count ))
        [[ $last == "invalid color" ]] && echo "invalid color" && exit 1
    done

    add=$(getTZ $sum)
    (( last+=add ))
    sum=${sum%%0}

    if (( $last < 3)); then
        echo "$((10#$sum * 10**$last)) ohms" 
    else
        getSuffix $last > /dev/null
        suffix=$(getSuffix $last)
        echo "$((10#$sum * 10**$remain)) $suffix"
    fi

}
main "$@"

