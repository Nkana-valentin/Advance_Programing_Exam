#!/bin/bash
 
for i in 12 16 20 24 28 32 36 40 44 48 52 56 60 64 
do
./benchmark.x $i > times_$i.txt
done 

for i in 12 16 20 24 28 32 36 40 44 48 52 56 60 64 
do 
head -n 11 times_$i.txt > tree_unbalanced_$i.txt
head -n 23 times_$i.txt | tail -n 11 > tree_balanced_$i.txt
tail -n 11 times_$i.txt > map_$i.txt
done 

rm tree_unbalanced_small_mean.txt 
rm tree_balanced_small_mean.txt 
rm map_small_mean.txt 
for i in 12 16 20 24 28 32 36 40 44 48 52 56 60 64
do 
awk -v I=$i -f mean_std.awk  tree_unbalanced_$i.txt >> tree_unbalanced_small_mean.txt
awk -v I=$i -f mean_std.awk  tree_balanced_$i.txt >> tree_balanced_small_mean.txt
awk -v I=$i -f mean_std.awk  map_$i.txt >> map_small_mean.txt 
rm tree_unbalanced_$i.txt
rm tree_balanced_$i.txt
rm map_$i.txt
rm times_$i.txt
done 
