#!/bin/bash

cyan=`tput setaf 51`
green=`tput setaf 46`
yellow=`tput setaf 226`
red=`tput setaf 196`

filename=$1

# for filename in 1 2 3 4; 
# do
    printf "${yellow}Running test case: ${cyan}Q$filename"
    ./$filename.out < ./testcases/Q$filename.txt > $filename.result
    temp=`diff -u ./testcases/A$filename.txt $filename.result`

    if [ $? -eq 0 ]
    then
        printf "  ==>  ${green}Pass!"
    else 
        printf "  ==>  ${red}Fail! Please check the diff output message below:\n"
    fi

    echo "$temp" | sed "s/^-/$(tput setaf 1)&/; s/^+/$(tput setaf 2)&/; s/^@/$(tput setaf 6)&/; s/$/$(tput sgr0)/"
    
    rm -f $filename.result
    rm -f $filename.out
# done
