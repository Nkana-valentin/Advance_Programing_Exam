#!/bin/bash
 
for i in 16 32 64 128 256 512 1024 2048 4096 8192 16384 32768 65536 131072 
do
./benchmark.x $i > times_$i.txt
done 

for i in 16 32 64 128 256 512 1024 2048 4096 8192 16384 32768 65536 131072 
do 
head -n 11 times_$i.txt > tree_unbalanced_$i.txt
head -n 23 times_$i.txt | tail -n 11 > tree_balanced_$i.txt
tail -n 11 times_$i.txt > map_$i.txt
done 

rm tree_unbalanced_mean.txt 
rm tree_balanced_mean.txt 
rm map_mean.txt 
for i in 16 32 64 128 256 512 1024 2048 4096 8192 16384 32768 65536 131072 
do 
awk -v I=$i -f mean_std.awk  tree_unbalanced_$i.txt >> tree_unbalanced_mean.txt
awk -v I=$i -f mean_std.awk  tree_balanced_$i.txt >> tree_balanced_mean.txt
awk -v I=$i -f mean_std.awk  map_$i.txt >> map_mean.txt 
rm tree_unbalanced_$i.txt
rm tree_balanced_$i.txt
rm map_$i.txt
rm times_$i.txt
done 
