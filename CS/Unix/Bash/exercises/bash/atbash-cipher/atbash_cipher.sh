#!/usr/bin/env bash

main() {

    result=$( tr "abcdefghijklmnopqrstuvwxyz" "zyxwvutsrqponmlkjihgfedcba" <<< ${2,,} | tr -d " .," )

    [ "$1" == "encode" ] && result=$(fold -w 5 <<< $result)

    echo $result
}
main "$@"

# function encode {
#
#     local letter_idx count
#
#     count=0
#
#     for char in $(echo "$inp" | grep -o .); do
#         (( count % 5  == 0 )) && res+=' '
#         found=0
#         for (( letter_idx=0; letter_idx<${#n_alp[@]}; letter_idx++ )); do
#             if [[ $char == ${n_alp[$letter_idx]} ]]; then
#                 res+=${r_alp[$letter_idx]}
#                 found=1
#                 break
#             fi
#         done
#         [[ $found -eq 0 ]] && res+=$char
#
#         ((count++))
#     done
#
#     echo $res
# }
#
# function decode {
#
#     local letter_idx
#
#     for char in $(echo "$inp" | grep -o .); do
#         found=0
#         for (( letter_idx=0; letter_idx<${#r_alp[@]}; letter_idx++ )); do
#             if [[ $char == ${r_alp[$letter_idx]} ]]; then
#                 res+=${n_alp[$letter_idx]}
#                 found=1
#                 break
#             fi
#         done
#         [[ $found -eq 0 ]] && res+=$char
#     done
#
#     echo $res
#
#
# }
#
# main() {
#
#     n_alp=("a" "b" "c" "d" "e" "f" "g" "h" "i" "j" "k" "l" "m" "n" "o" "p" "q" "r" "s" "t" "u" "v" "w" "x" "y" "z")
#
#     for (( i=${#n_alp[@]}-1; i>=0; i-- )); do
#         r_alp+=("${n_alp[i]}")
#     done
#
#     inp=$(echo "$2" | tr "[:upper:]" "[:lower:]" | tr -d "[:space:][:punct:]")
#     res=""
#
#     if [[ $1 == encode ]]; then
#         encode
#     elif [[ $1 == decode ]]; then
#         decode
#     fi
#
#     [[ $1 == encode ]] && encode 
#     [[ $1 == decode ]] && decode
#
# }
#
# main "$@"
