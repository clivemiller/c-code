#!/bin/bash

x=$1
expression=$2
y=$3

# Check if all arguments are provided
if [ -z "$x" ] || [ -z "$expression" ] || [ -z "$y" ]; then
    echo "Usage: $0 <number> <operator> <number>"
    echo "Operators: +, -, *, /"
    exit 1
fi

if [ "$expression" = "+" ]; then
    echo $((x + y))
elif [ "$expression" = "-" ]; then
    echo $((x - y))
elif [ "$expression" = "*" ]; then
    echo $((x * y))
elif [ "$expression" = "/" ]; then
    if [ "$y" -eq 0 ]; then
        echo "Error: Division by zero"
        exit 1
    fi
    echo $((x / y))
else
    echo "Error: Invalid operator '$expression'"
    echo "Valid operators: +, -, *, /"
    exit 1
fi