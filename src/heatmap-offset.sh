#!/bin/bash

awk '
/IO_END/ {
    printf "%.f %.f\n", $5 * 1000000, $3
}
' | HeatMap/trace2heatmap.pl --unitstime us --unitslatency ' sector' --grid --title "I/O pattern" "$@"

