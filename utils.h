#pragma once

#define MAX_DATA_SIZE 100000
#define UNDEFINED 0
#define NOISE -1

struct CommandlineArguments {
    char  *input_filename;
    char  *output_filename;
    float eps;
    int   min_num_points;
};

CommandlineArguments ParseCommandlineArguments(int argc, char *argv[]);