#!/usr/bin/env bash

main(){

    local inp sum doubled count
    inp=$(echo "$1" | tr -d "[:space:]")
    sum=0
    count=1

    if (( ${#inp} <= 1 )) || ! [[ $inp =~ ^[0-9]+$ ]]; then
        echo false && exit 0
    fi

    inp=$(echo "$inp" | rev)

    while IFS= read -r -n1 dig; do
        [[ -z $dig ]] && break
        if (( (count % 2) == 0 )); then
            if (( (dig * 2) > 9 )); then
                sum=$((sum + (dig * 2 - 9) ))
            else
                sum=$((sum + dig * 2))
            fi
        else
            sum=$((sum + dig))
        fi
        ((count++))
    done <<< "$inp"

    (( sum % 10 == 0 )) && echo true || echo false


}
main "$@"
