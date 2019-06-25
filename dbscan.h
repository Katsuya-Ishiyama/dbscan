#include "points.h"

Points Dbscan(Points points, float eps, int min_num_points);

bool ExpandCluster(Points points,
                   Point  *point,
                   int    cluster_id,
                   float  eps,
                   int    min_num_points);