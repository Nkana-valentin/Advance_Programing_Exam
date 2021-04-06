BEGIN { FS = "[;, ]"; items = 0; sum = 0; sum2 = 0 }
NR > 2 { if ($1!="") items += 1; if ($1!="") sum += $1; if ($1!="") sum2 += ($1)^2 }
END { print I, sum/items, sqrt((sum2 - ((sum)^2)/items)/items) }
