#!/usr/bin/env bash

function main {

    declare -a control primes

    for (( i=2; i<=$1; ++i )); do control[$i]=1; done

    for (( i=2; i<=$1; ++i )); do
        (( control[i] )) || continue
        primes+=($i)

        for (( j=i*2; j<=$1; j+=i )); do control[$j]=0; done
    done

    echo "${primes[@]}"

}
main "$@"
