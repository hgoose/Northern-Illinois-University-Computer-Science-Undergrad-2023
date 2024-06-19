#!/usr/bin/env bash

function usage {
    echo "Usage: leap.sh <year>" && exit 1
}

function True {
    echo true && exit 0
}

function False {
    echo false && exit 0
}

function main {

    if (( $# != 1 )) || ! [[ $1 =~ ^[[:digit:]]+$ ]]; then 
        usage
    fi

    if (( $1 % 4 == 0 )); then
        if (( $1 % 100 == 0 )) && ! (( $1 % 400 == 0 )); then
            False
        fi
        True
    fi
    False

} 
main "$@"
