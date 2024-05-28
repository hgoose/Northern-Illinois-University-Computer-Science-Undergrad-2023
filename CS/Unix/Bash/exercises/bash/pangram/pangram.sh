#!/usr/bin/env bash

main() {
    a_letters=("a" "b" "c" "d" "e" "f" "g" "h" "i" "j" "k" "l" "m" "n" "o" "p" "q" "r" "s" "t" "u" "v" "w" "x" "y" "z")
    input=$(echo "$1" | tr "[:upper:]" "[:lower:]")
    ret=true

    for item in "${a_letters[@]}"; do
        if [[ $input != *"$item"* ]]; then
            ret=false
            break
        fi
    done

    echo $ret
}
main "$@"
