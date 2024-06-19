#!/usr/bin/env bash

function quit {
    echo $1 && exit 0
}

function main {

    local inp ret
    inp=$1
    ret=true

    inp=$(echo "$inp" | tr -cd '(){}[]')

    (( ${#inp} % 2 != 0 )) && quit false

    while [[ -n ${inp} ]]; do
        if [[ $inp =~ .*\(\).* ]]; then
            inp=$(echo "$inp" | sed 's/()//g')
        elif [[ $inp =~ .*\[\].* ]]; then
            inp=$(echo "$inp" | sed 's/\[\]//g')
        elif [[ $inp =~ .*\{\}.* ]]; then
            inp=$(echo "$inp" | sed 's/{}//g')
        else 
            quit false
        fi
    done

    quit true
}
main "$@"
