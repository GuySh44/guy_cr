#!/bin/bash

file=$1

i=1
while read line; do
	last_word=""
	for word in $line; do
		if [[ $word == $last_word ]]
			then
			echo "Line No. $i: $line"
		fi		
		last_word=$word
	done
i=$((i+1))
done < $file

