#!/usr/bin/env bash

main() {

    ac=""

    str=$(echo "$1" | sed 's/[^[:alnum:][:space:][:digit:]-]//g')

    [[ ${str:0:1} =~ [[:alpha:]] ]] && ac+=${str:0:1}

    for (( i=0; i<${#str}; i++ )); do
        [[ ${str:i:1} =~ [[:space:]-] ]]  && [[ ${str:i+1:1} =~ [[:alpha:]] ]] && ac+=$(echo ${str:i+1:1} | tr "[:lower:]" "[:upper:]")
    done

    echo $ac

}
main "${@}"
