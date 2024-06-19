#!/usr/bin/env bash

function quit {
    echo ${1%,} && exit 0
}

function main {

    [[ -z $1 ]] && quit ""
    (( $1 < 1 || $1 > 31 )) && quit ""

    local bin actions count res rev

    bin=$(echo "obase=2; $1" | bc)
    actions=("wink," "double blink," "close your eyes," "jump,")
    count=0
    res=""
    rev=true

    bin=$(printf "%05d" "$bin")
    (( ${bin:0:1} != 1 )) && rev=false && bin=$(echo ${bin:1} | rev) || bin=$(echo ${bin:1}) 

    if [[ $rev == true ]]; then
        for (( i=${#bin}-1; i >= 0; i-- )); do
            (( ${bin:count:1} == 1 )) && res+=${actions[i]}
            (( count++ ))
        done

    else
        for item in $(echo $bin | grep -o .); do
            (( $item == 1 )) && res+=${actions[count]} 
            (( count++ ))
        done
    fi

    echo ${res%,}


    

}
main "$@"
