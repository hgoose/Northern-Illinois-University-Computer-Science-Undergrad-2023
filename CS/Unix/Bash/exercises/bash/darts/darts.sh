#!/usr/bin/env bash

function quit {
    echo "# there is _some_ output" && exit 1
}


function main {

    (( $# != 2 ))  && quit

    if ! [[ $1 =~ ^-?[0-9]+(\.[0-9]+)?$ && $2 =~ ^-?[0-9]+(\.[0-9]+)?$ ]]; then
        quit
    fi

    local x y sum_squares res
    x=$1;y=$2
    res=0

    sum_squares=$(echo "$x^2 + $y^2" | bc -l)

    if (( $(echo "$sum_squares <= 1" | bc -l)  )); then 
        (( res+=10 ))
    elif (( $(echo "$sum_squares <= 25"  | bc -l) )); then
        (( res+= 5 ))
    elif (( $(echo "$sum_squares <= 100" | bc -l) )); then
        (( res+= 1 ))
    fi

    echo $res




}
main "$@"
