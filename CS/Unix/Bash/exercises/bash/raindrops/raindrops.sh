#!/usr/bin/env bash

main() {

    res=""

    if  (( $1 % 3 == 0 )); then
        res+="Pling"
    fi

    if (( $1 % 5 == 0 )); then
        res+="Plang"
    fi

    if (( $1 % 7 == 0 )); then
        res+="Plong"
    fi

    if [[ -z $res ]]; then
        echo $1
    else 
        echo $res
    fi

}
main "$@"

