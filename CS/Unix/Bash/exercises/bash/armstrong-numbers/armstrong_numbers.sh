#!/usr/bin/env bash

main() {

    local sum=0

    for (( i=0; i<${#1}; i++ )); do
        sum=$(( sum+${1:i:1}**${#1} ))
    done

    [[ $sum -eq $1 ]] && echo "true"  || echo "false"

}
main "$@"
