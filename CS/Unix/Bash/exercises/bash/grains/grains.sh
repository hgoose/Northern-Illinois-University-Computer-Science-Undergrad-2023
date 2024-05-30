#!/usr/bin/env bash

main() {

    if [[ $(echo "$1" | tr "[:upper:]" "[:lower:]") == "total" ]]; then
        echo $(echo "2^63" | bc)
    fi

    if ! [[$1 =~ ^[0-9]+$ ]] || [[ $1 -lt 1 ]] || [[ $1 -gt 64 ]]; then
        echo "Error: invalid input"
        exit 1
    fi

    total_grains=$(echo "2^(($1 -1))" | bc)
    echo "$total_grains"
}
main "$@"

