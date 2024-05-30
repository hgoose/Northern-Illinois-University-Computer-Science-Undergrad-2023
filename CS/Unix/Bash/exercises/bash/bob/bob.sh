#!/usr/bin/env bash

main() {

    local input=$1
    if [[ $input =~ ^[A-Z0-9[:space:][:punct:]]+\?$ ]] && [[ $input =~ [A-Z] ]]; then
        echo "Calm down, I know what I'm doing!"
    elif [[ $input =~ .*\?[[:space:]]*$ ]]; then
        echo "Sure."
    elif [[ $input =~ ^[A-Z0-9[:space:][:punct:]]+$ ]] && [[ $input =~ [A-Z] ]]; then
        echo "Whoa, chill out!"
    elif [[ $input =~ ^[[:space:]]*$ ]]; then
        echo "Fine. Be that way!"
    else
        echo "Whatever."
    fi
}
main "$@"

