#include "utils.h"
#include "distance.h"
#include "csv.h"

std::vector<std::string> CsvReader::split(std::string& input, char delimiter) {
    std::istringstream stream(input);
    std::string field;
    std::vector<std::string> result;

    while (getline(stream, field, delimiter)) {
        result.push_back(field);
    }

    return result;
}

Points CsvReader::load(std::string path, int header_, char *delimiter) {
    std::ifstream ifs(path);

    std::string line;
    Points points = Points(EuclidDistance);
    int current_row = -1;
    int point_index = 0;
    while (getline(ifs, line)) {
        ++current_row;
        if (current_row <= header_) {
            continue;
        }

        std::vector<std::string> str_vector = split(line, *delimiter);
        float x = std::stof(str_vector[1]);
        float y = std::stof(str_vector[2]);
        points.append(point_index, new Point(x, y));
        ++point_index;
    }

    return points;
}

void WriteCsv(Points *points, char *filename) {

    if (points->is_empty()) {
        throw;
    }

    FILE *fp;
    //fp = fopen("dbscan_result.csv", "w");
    fp = fopen(filename, "w");
    fprintf(fp, "x,y,cluster_id\n");
    for (int i = 0; i < points->size(); ++i) {
        Point *pt = points->get(i);
        fprintf(fp, "%f,%f,%d\n", pt->x, pt->y, pt->cluster_id);
    }
    fclose(fp);
}
