#!/bin/bash
echo "Name of file:"
read name

echo "Number of random numbers:"
read num

#touch "./$name"

for (( i = 0; i < $num; i++ )); do
  n = $RANDOM
  echo >> "./$name"
done
