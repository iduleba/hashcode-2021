#!/bin/bash
n=761590
MAX=761600
file="c_many_ingredients.in"

while (( $n < MAX ))
do
    alpha=$(python -c "print($n*0.000001)")
    score=$(./main4.out $alpha < ../in/$file)
    echo "$alpha $score"
    n=$((n+1))
done