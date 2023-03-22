#!/bin/bash

str=$1

if ! [[ $str =~ ^[0-9]{1,3}\.[0-9]{1,3}\.[0-9]{1,3}\.[0-9]{1,3}$ ]];
	then
	    echo "not of type n.n.n.n"
	    exit
fi

IFS='.'
ip=($str)
IFS=$OIFS

if [[ $((ip[0])) -ge 256 ]] || [[ $((ip[1])) -ge 255 ]]	|| [[ $((ip[2])) -ge 255 ]] || [[ $((ip[3])) -ge 255 ]]; then
    echo "not a valid ip, out of range"
    exit
fi

ping $str	
	
