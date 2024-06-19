#!/usr/bin/env bash

function nullput {
    echo "" && exit 0 
}

function out {
    echo "For want of a $1 the $2 was lost."
}

function main {

    local arr; declare -a arr

    for i; do arr+=("$i"); done

    (( ${#arr[@]} == 0 )) && nullput

    for (( i=0; i<${#arr[@]}-1; ++i )); do
        out "${arr[i]}" "${arr[i+1]}"
    done

    echo "And all for the want of a ${arr[0]}."
}
main "$@"
