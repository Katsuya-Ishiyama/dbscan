#pragma once

#include <stdlib.h>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>

#include "points.h"

class CsvReader {
        std::vector<std::string> split(std::string& input, char delimiter);
    public:
        Points load(std::string path, int header_ = 0, char *delimiter = (char *) ",");
};

void WriteCsv(Points *points, char *filename);