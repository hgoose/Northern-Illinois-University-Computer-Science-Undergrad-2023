#!/usr/bin/env bash

function usage {
    echo "Usage: ./grep.sh [-n] [-l] [-i] [-v] [-x] <file> <string>" && exit 1
}

function negate {
    ret=$1
    if $ret; then
        ret=false
    else
        ret=true
    fi

    echo $ret
}


function main {

    (( $# )) || usage

    local n_flag l_flag i_flag v_flag x_flag any_flag file string
    n_flag=false;l_flag=false;i_flag=false;v_flag=false;x_flag=false; any_flag=false

    while getopts "nlivx" opt; do
        case $opt in
            n) n_flag=true; any_flag=true ;;
            l) l_flag=true; any_flag=true ;;
            i) i_flag=true; any_flag=true ;;
            v) v_flag=true; any_flag=true ;;
            x) x_flag=true; any_flag=true ;;
        esac
    done

    shift $((OPTIND - 1))

    (( $# < 2 )) && usage

    string=$1
    shift && files=("$@")
    matches=()

    $i_flag && string=$(echo "$string" | tr "[:upper:]" "[:lower:]")

    for file in "${files[@]}"; do
        line_num=0
        while IFS= read -r line; do 
            (( ++line_num ))

            compare=$line
            $i_flag && compare=$(echo "$line" | tr "[:upper:]" "[:lower:]")

            match=false
            if $x_flag; then
                [[ "$compare" == "$string" ]]  && match=true
            else
                [[ "$compare" =~ "$string" ]] && match=true
            fi

            $v_flag && match=$(negate $match)

            if $match; then
                if $l_flag; then
                    matches+=($file)
                    break
                else
                    output=""

                    if $n_flag; then
                        if (( "${#files[@]}" == 1 )); then
                            output="${line_num}:${line}"
                        else
                            output="${file}:${line_num}:${line}"
                        fi
                    else
                        if (( "${#files[@]}" == 1 )); then
                            output="${line}"
                        else
                            output="${file}:${line}"
                        fi
                    fi
                    matches+=("$output")
                fi
            fi

            
        done < ${file}
    done

    if $l_flag; then
        printf "%s\n" "${matches[@]}" | sort -u
    else
        printf "%s\n" "${matches[@]}"
    fi
    

}
main "$@"
