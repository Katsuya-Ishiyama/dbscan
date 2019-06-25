#include <stdio.h>
#include <list>

#include "utils.h"
#include "points.h"
#include "distance.h"
#include "csv.h"
#include "dbscan.h"

int Test () {

    Point pt1 = Point(0.0, 0.0, 1);
    Point pt2 = Point(1.0, 1.0, 1);
    printf("pt1: (%0.2f, %0.2f, %d)\n", pt1.x, pt1.y, pt1.cluster_id);
    printf("pt2: (%0.2f, %0.2f, %d)\n", pt2.x, pt2.y, pt2.cluster_id);

    pt2.set_cluster_id(2);
    printf("pt2: (%0.2f, %0.2f, %d)\n", pt2.x, pt2.y, pt2.cluster_id);

    float dist = EuclidDistance(&pt1, &pt2);
    printf("EuclidDistance(pt1, pt2) = %0.3f\n", dist);

    Points set_of_points = Points(EuclidDistance);

    set_of_points.set_distance(EuclidDistance);
    set_of_points.append(0, &pt1);
    set_of_points.append(1, &pt2);
    Point pt3 = Point(0.0, 1.0, 3);
    set_of_points.append(2, &pt3);

    printf("Size of set_of_points: %d\n", set_of_points.size());

    for (int i = 0; i < set_of_points.size(); i++) {
        Point *pt = set_of_points.get(i);
        printf("pt%d = (%0.2f, %0.2f, %d, %d)\n", i, pt->x, pt->y, pt->cluster_id, pt->index);
    }

    Points neighborhood = set_of_points.region_query(new Point(1.0, 1.0, 2), 1);
    printf("Size of neighborhood: %d\n", neighborhood.size());
    for (int i = 0; i < neighborhood.size(); i++) {
        Point *pt = neighborhood.get(i);
        printf("pt%d = (%0.2f, %0.2f, %d, %d)\n", i, pt->x, pt->y, pt->cluster_id, pt->index);
    }

    printf("----- change_cluster_id -----\n");
    neighborhood.change_cluster_id(NOISE);
    for (int i = 0; i < neighborhood.size(); i++) {
        Point *pt = neighborhood.get(i);
        printf("pt%d = (%0.2f, %0.2f, %d, %d)\n", i, pt->x, pt->y, pt->cluster_id, pt->index);
    }
    printf("-----------------------------\n");

    neighborhood.remove(&pt2);
    for (int i = 0; i < neighborhood.size(); i++) {
        Point *pt = neighborhood.get(i);
        printf("pt%d = (%0.2f, %0.2f, %d)\n", i, pt->x, pt->y, pt->cluster_id);
    }

    neighborhood.remove(&pt3);
    if (neighborhood.is_empty()) {
        printf("neighborhood is empty.\n");
    }

    printf("-------------------------------\n");
    printf("Test CsvReader\n\n");
    CsvReader csv_reader = CsvReader();
    char input_filename[] = "/home/katsuya/dbscan/src/data/sample_dataset.csv";
    Points points_csv = csv_reader.load(input_filename);
    for (int i = 0; i < points_csv.size(); ++i) {
        Point *pt = points_csv.get(i);
        printf("pt%d = (%0.2f, %0.2f, %d)\n", i, pt->x, pt->y, pt->cluster_id);
    }

    Points clustered_points = Dbscan(points_csv, 1, 20);
    for (int i = 0; i < clustered_points.size(); ++i) {
        Point *pt = clustered_points.get(i);
        printf("pt%d = (%0.2f, %0.2f, %d)\n", i, pt->x, pt->y, pt->cluster_id);
    }

    char filename[] = "dbscan_result.csv";
    WriteCsv(&clustered_points, filename);

    return 0;
}
