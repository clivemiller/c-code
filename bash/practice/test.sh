#!/bin/sh

for arg in $*
do
    if echo "$arg" & | grep cat ; then
        echo $arg
    fi
done