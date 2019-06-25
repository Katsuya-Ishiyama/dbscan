#include <stdio.h>
#include "points.h"

// class Point

Point::Point(float x_, float y_, int cluster_id_, int index_) {
    x = x_;
    y = y_;
    set_cluster_id(cluster_id_);
    set_index(index_);
}

void Point::set_cluster_id(int cluster_id_) {
    cluster_id = cluster_id_;
}

void Point::set_index(int index_) {
    index = index_;
}

// class Points

Points::Points(float (*Distance) (Point *, Point *)) {
    set_distance(Distance);
}

bool Points::is_empty() {
    return points_.empty();
}

void Points::set_distance(float (*Distance) (Point *, Point *)) {
    Distance_ = Distance;
}

void Points::append(int index, Point *point) {
    point->set_index(index);
    points_.push_back(point);
}

void Points::remove(Point *point) {
    if (points_.empty()) {
        throw;
    }

    int target = TARGET_NOT_FOUND;
    for (int i = 0; i < points_.size(); ++i) {
        if (points_[i]->index == point->index) {
            target = i;
            break;
        }
    }

    if (target == TARGET_NOT_FOUND) {
        throw;
    }

    std::vector<Point *>::iterator it = points_.begin() + target;
    points_.erase(it);
}

Point *Points::get(int index) {
    if (points_.empty()) {
        throw;
    }

    if ( (index < 0) || (points_.size() <= index) ) {
        throw;
    }

    return points_[index];
}

int Points::size() {
    return points_.size();
}

Points Points::region_query(Point *point, float eps) {
    Points neighborhood(Distance_);

    for (int i = 0; i < points_.size(); i++) {
        Point *neighbor_point = points_[i];
        float d = Distance_(point, neighbor_point);
        if (d <= eps) {
            int index = neighbor_point->index;
            neighborhood.append(index, neighbor_point);
        }
    }

    return neighborhood;
}

void Points::change_cluster_id(int cluster_id) {
    for (int i = 0; i < points_.size(); i++) {
        points_[i]->set_cluster_id(cluster_id);
    }
}