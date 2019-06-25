#include <stdio.h>
#include <list>

#include "utils.h"
#include "points.h"
#include "distance.h"
#include "csv.h"
#include "dbscan.h"

int main (int argc, char *argv[]) {

    CommandlineArguments args;
    args = ParseCommandlineArguments(argc, argv);

    CsvReader csv_reader = CsvReader();
    Points points_csv = csv_reader.load(args.input_filename);
    Points clustered_points = Dbscan(points_csv, args.eps, args.min_num_points);

    WriteCsv(&clustered_points, args.output_filename);

    return 0;
}
