#!/bin/bash

awk '
/IO_BEGIN/ {
    ts[$2, $3] = $5;
}

/IO_END/ {
    if (req_start = ts[$2, $3]) {
        printf "%.f %.f\n", $5 * 1000000, ($5 - req_start) * 1000000;
        ts[$2, $3] = 0
    }
}
' | HeatMap/trace2heatmap.pl --unitstime us --unitslatency us --grid "$@"
