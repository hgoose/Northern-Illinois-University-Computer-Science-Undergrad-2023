#!/usr/bin/env bash
total=0
for x in $(echo ${1^^} | grep -o .); do
    case $x in
        [AEIOULNRST]) ((total++));;
        [DG])         ((total+=2));;
        [BCMP])       ((total+=3));;
        [FHVWY])      ((total+=4));;
        K)            ((total+=5));;
        [JX])         ((total+=8));;
        *)            ((total+=10));;
    esac
done
echo $total
