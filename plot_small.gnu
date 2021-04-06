set terminal pngcairo enhanced fontscale 0.7 size 800, 600
set output "timing_small.png"
set ylabel 'Time [ns]'

#set xlabel 'Log_2 of tree/map number of nodes'
set xlabel 'tree/map number of nodes'

set title "bst vs map timing"

#set logscale x 2

plot "tree_unbalanced_small_mean.txt" w e ps 1 linetype 1 title "unbalanced", "" w l lw 1 linetype 1 not, "tree_balanced_small_mean.txt" w e ps 1 linetype 2 title "balanced", "" w l lw 1 linetype 2 not, "map_small_mean.txt" w e ps 1 linetype 3 title "map", "" w l lw 1 linetype 3 not 
