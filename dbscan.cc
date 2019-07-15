#include <stdio.h>
#include "utils.h"
#include "dbscan.h"
#include "distance.h"

Points Dbscan(Points points, float eps, int min_num_points) {
    int cluster_id = 0;

    for (int i = 0; i < points.size(); ++i) {
        Point *point = points.get(i);
        printf("Start: assign cluster for index %d: (%0.3f, %0.3f)\n", point->index, point->x, point->y);
        if (point->cluster_id != UNDEFINED) {
            printf("Already assigned clusterID.\n");
            continue;
        }
        if (ExpandCluster(points, point, cluster_id, eps, min_num_points)) {
            printf("The point was assigned clusterID: %d\n", cluster_id);
            ++cluster_id;
        }
    }

    return points;
}

bool ExpandCluster(Points points,
                   Point  *point,
                   int    cluster_id,
                   float  eps,
                   int    min_num_points) {

    Points seeds = points.region_query(point, eps);

    printf("size of seeds: %d\n", seeds.size());
    if (seeds.size() < min_num_points) {
        point->set_cluster_id(NOISE);
        printf("clusterID of point index %d was set to NOISE because of size of seeds.\n", point->index);
        return false;
    }

    seeds.change_cluster_id(cluster_id);
    printf("clusterID was set to %d\n", cluster_id);
    seeds.remove(point);

    while (!seeds.is_empty()) {
        Point *current_point = seeds.get(0);
        Points neighbor_points = points.region_query(current_point, eps);

        if (neighbor_points.size() < min_num_points) {
            seeds.remove(current_point);
            continue;
        }

        for (int i = 0; i < neighbor_points.size(); i++) {
            printf("neighbor_points: %d\n", i);
            Point *neighbor_point = neighbor_points.get(i);
            int neighbor_cluster_id = neighbor_point->cluster_id;
            printf("assign cluster for index %d: (%0.3f, %0.3f), cluster %d\n", neighbor_point->index, neighbor_point->x, neighbor_point->y, neighbor_cluster_id);

            // Skip following procedure if the point is already assigned.
            if ((neighbor_cluster_id != UNDEFINED) && (neighbor_cluster_id != NOISE)) {
                printf("skip this point since it already has clusterID.\n");
                continue;
            }

            // Drop a point if it is noise.
            if (neighbor_cluster_id == NOISE) {
                seeds.remove(neighbor_point);
                printf("remove this neighbor_point because it is NOISE\n");
            }

            // As a result of above, the point is not assigned any cluster_id yet.
            // So, we will make the point have cluster_id.
            neighbor_point->set_cluster_id(cluster_id);
            printf("the clusterID of neighbor_point was set as %d\n", cluster_id);
        }

        seeds.remove(current_point);
    }

    return true;
}