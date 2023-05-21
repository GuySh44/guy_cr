#!/bin/bash

perm1="$1 $2 "
perm2="$2 $3 "
perm3="$1 $3 "

perm4="$1 $2 $3 "

echo $1>list.txt
echo $2>>list.txt
echo $3>>list.txt
crunch 3 3 -p $perm4 >> list.txt
crunch 3 3 -p $perm1 >> list.txt
crunch 3 3 -p $perm2 >> list.txt
crunch 3 3 -p $perm3 >> list.txt


