#!/bin/bash
n=7516
MAX=7525
file="c_many_ingredients.in"

while (( $n <= MAX ))
do
    alpha=$(python -c "print($n*0.0001)")
    score=$(./main4.out $alpha < ../in/$file)
    echo "$alpha $score"
    n=$((n+1))
done