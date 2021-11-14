#include <dbscan/dbscan.hpp>
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
    const double epsilon = 0.76;
    const int min_points = 4;

    dbscan::Dbscan scan(points, min_points, epsilon);
    scan.CreateClusters();

    for (auto cluster:scan.clusters) {
        std::cout << cluster;
    }

    return 0;
}
