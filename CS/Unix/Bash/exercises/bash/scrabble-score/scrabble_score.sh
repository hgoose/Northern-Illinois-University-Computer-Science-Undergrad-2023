#!/usr/bin/env bash

main() {
    local count=0
    local inp=$(echo $1 | tr "[:upper:]" "[:lower:]")

    while IFS= read -r -n1 char; do 
        if [[ $char =~ [aeioulnrst] ]]; then
            count=$(( $count + 1 ))
        elif [[ $char =~ [dg] ]]; then
            count=$(($count + 2))
         elif [[ $char =~ [bcmp] ]]; then
            count=$(($count + 3))
         elif [[ $char =~ [fhvwy] ]]; then
            count=$(($count + 4))
         elif [[ $char =~ [k] ]]; then
            count=$(($count + 5))
          elif [[ $char =~ [jx] ]]; then
            count=$(($count + 8))
        elif [[ $char =~ [qz] ]]; then
            count=$(($count + 10))
        fi
    done <<< "$inp"

    echo "$count"
}
main "$@"
