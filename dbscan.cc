#include <stdio.h>
#include "utils.h"
#include "dbscan.h"
#include "distance.h"

Points Dbscan(Points points, float eps, int min_num_points) {
    int cluster_id = 0;

    for (int i = 0; i < points.size(); ++i) {
        Point *point = points.get(i);
        //printf("Start: assign cluster for index %d: (%0.3f, %0.3f)\n", point->index, point->x, point->y);
        if (point->cluster_id != UNDEFINED) {
            //printf("Already assigned clusterID.\n");
            continue;
        }
        if (ExpandCluster(points, point, cluster_id, eps, min_num_points)) {
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

    if (seeds.size() < min_num_points) {
        points.change_cluster_id(NOISE);
        return false;
    }

    seeds.change_cluster_id(cluster_id);
    seeds.remove(point);

    while (!seeds.is_empty()) {
        Point *current_point = seeds.get(0);
        Points neighbor_points = points.region_query(current_point, eps);

        if (neighbor_points.size() < min_num_points) {
            seeds.remove(current_point);
            continue;
        }

        for (int i = 0; i < neighbor_points.size(); i++) {
            Point *neighbor_point = neighbor_points.get(i);
            int neighbor_cluster_id = neighbor_point->cluster_id;

            // Skip following procedure if the point is already assigned.
            if ((neighbor_cluster_id != UNDEFINED) && (neighbor_cluster_id != NOISE)) {
                continue;
            }

            // Drop a point if it is noise.
            if (neighbor_cluster_id == NOISE) {
                seeds.remove(neighbor_point);
            }

            // As a result of above, the point is not assigned any cluster_id yet.
            // So, we will make the point have cluster_id.
            neighbor_point->set_cluster_id(cluster_id);
        }

        seeds.remove(current_point);
    }

    return true;
}