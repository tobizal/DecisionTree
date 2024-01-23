#!/bin/zsh

argc=$#
REQUIRED_ARGC=1

if [[ argc -ne REQUIRED_ARGC ]]; then
	echo "Invalid arguments. Use: $0 <filename>"
	exit 1
fi


g++ $1 `ls ../src | grep .cpp | grep -v main.cpp | awk '$0="../src/"$0'` `ls ../src/algorithms | grep .cpp | grep -v main.cpp | awk '$0="../src/algorithms/"$0'` -o `echo "${1[0, -5]}"` -w
