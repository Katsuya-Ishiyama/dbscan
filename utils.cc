#include <stdio.h>
#include <stdlib.h>
#include "utils.h"

CommandlineArguments ParseCommandlineArguments(int argc, char *argv[]) {
    if (argc != 5) {
        printf("Invalid commandline arguments.\n");
        throw;
    }

    CommandlineArguments args;
    args.input_filename  = argv[1];
    args.output_filename = argv[2];
    args.eps             = std::atof(argv[3]);
    args.min_num_points  = std::atoi(argv[4]);

    return args;
}