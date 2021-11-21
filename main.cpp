#include <dbscan/evaluate.hpp>
#include <dbscan/point.hpp>

#include <fstream>
#include <iostream>
#include <sstream>
#include <string>

std::vector<dbscan::Point> read_file() {
    std::vector<dbscan::Point> points;
    std::ifstream newfile("data/cluster_data.txt");
    std::string data;
    std::vector<std::string> coordinates;
    double x, y, z;
    while (std::getline(newfile, data)) {
        std::stringstream input(data);
        while (std::getline(input, data, ',')) {
            coordinates.push_back(data);
        }
    }

    for (int i = 0; i < coordinates.size(); i++) {
        if (i%4 == 0) {
            x = std::stof((coordinates[i]));
        } else if (i%4 == 1) {
            y = std::stof(coordinates[i]);
        } else if (i%4 == 2) {
            z = std::stof(coordinates[i]);
            points.push_back(dbscan::Point(x, y, z));
        }
    }

    return points;
}

int main() {
    std::vector<dbscan::Point> points = read_file();

    dbscan::Evaluate check;
    double epsilon;
    int min_points;
    double score;
    std::tie(epsilon, score, min_points) = check.TuneParams(points);
    std::cout << epsilon << " " << min_points << " " << score << "\n";

    return 0;
}
