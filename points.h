#pragma once

#include <vector>
#include "utils.h"

#define TARGET_NOT_FOUND 1

class Point
{
    public:
        float x;
        float y;
        int   cluster_id;
        int   index;

        Point(float x_, float y_, int cluster_id_ = UNDEFINED, int index_ = 0);
        void set_cluster_id(int cluster_id);
        void set_index(int index_);
};

class Points {
    std::vector<Point *> points_;
    float (*Distance_) (Point *, Point *);

    public:
        Points(float (*Distance) (Point *, Point *));
        bool is_empty();
        void set_distance(float (*Distance) (Point *, Point *));
        std::vector<Point *> get_points();
        void append(int index, Point *point);
        void remove(Point *point);
        Point *get(int index);
        int size();
        Points region_query(Point *point, float eps);
        void change_cluster_id(int cluster_id);
};