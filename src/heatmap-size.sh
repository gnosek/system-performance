#!/bin/bash

awk '
/IO_END/ {
    printf "%.f %.f\n", $5 * 1000000, $4
}
' | HeatMap/trace2heatmap.pl --unitstime us --unitslatency ' sectors' --grid --title "I/O size" "$@"

