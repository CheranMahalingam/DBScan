#include <vector>
#include <unordered_map>
#include <cmath>
#include <fstream>
#include <iostream>
#include <string>
#include <sstream>

typedef enum {
    UNCLASSIFIED = 0,
    NOISE,
    CLASSIFIED
} ClusterState;

struct Point {
    float x, y, z;
    int cluster_id;
    ClusterState state;
    Point(float x, float y, float z) : x(x), y(y), z(z), cluster_id(0), state(UNCLASSIFIED) {}
    bool operator!=(const Point& a) {
        return this->x != a.x || this->y != a.y || this->z != a.z;
    }
};

void check(std::vector<Point>& points) {
    int classified = 0;
    int unclassified = 0;
    int noise = 0;
    for (auto point:points) {
        if (point.state == CLASSIFIED) {
            classified++;
        } else if (point.state == NOISE) {
            noise++;
        } else if (point.state == UNCLASSIFIED) {
            unclassified++;
        }
    }
}

float get_distance(const Point& p, const Point& q) {
    return std::pow(std::pow(p.x - q.x, 2) + std::pow(p.y - q.y, 2) + std::pow(p.z - q.z, 2), 0.5);
}

std::vector<int> create_cluster(const int curr_index, const std::vector<Point>& points, const float epsilon) {
    std::vector<int> neighbour_points;
    for (int i = 0; i < points.size(); i++) {
        if (get_distance(points[curr_index], points[i]) <= epsilon && i != curr_index) {
            neighbour_points.push_back(i);
        }
    }
    return neighbour_points;
}

void nearest_neighbour_search(const int curr_index, std::vector<Point>& points, const float epsilon, const int min_points, const int cluster_id) {
    std::vector<int> cluster_seeds = create_cluster(curr_index, points, epsilon);

    if (cluster_seeds.size() < min_points) {
        points[curr_index].state = NOISE;
    } else {
        points[curr_index].state = CLASSIFIED;
        points[curr_index].cluster_id = cluster_id;
        for (auto index:cluster_seeds) {
            points[index].cluster_id = cluster_id;
            points[index].state = CLASSIFIED;
        }

        int i = 0;
        while (i < cluster_seeds.size()) {
            std::vector<int> neighbours = create_cluster(cluster_seeds[i], points, epsilon);
            if (neighbours.size() >= min_points) {
                for (auto index:neighbours) {
                    if (points[index].state == UNCLASSIFIED || points[index].state == NOISE) {
                        if (points[index].state == UNCLASSIFIED) {
                            cluster_seeds.push_back(index);
                        }
                        points[index].cluster_id = cluster_id;
                        points[index].state = CLASSIFIED;
                    }
                }
            }
            i++;
        }
    }
}

std::unordered_map<int, std::vector<Point>> create_cluster_map(std::vector<Point>& points, const float epsilon, const int min_points) {
    std::unordered_map<int, std::vector<Point>> res;
    int curr_cluster_id = 1;
    for (int i = 0; i < points.size(); i++) {
        if (points[i].state == UNCLASSIFIED) {
            nearest_neighbour_search(i, points, epsilon, min_points, curr_cluster_id);
            if (points[i].state != NOISE) {
                curr_cluster_id++;
            }
        }
    }
    for (auto point:points) {
        if (point.state == CLASSIFIED) {
            if (res.find(point.cluster_id) == res.end()) {
                res[point.cluster_id] = {point};
            } else {
                res[point.cluster_id].push_back(point);
            }
        }
    }
    return res;
}

std::vector<Point> read_file() {
    std::vector<Point> points;
    std::ifstream newfile("cluster_data.txt");
    std::string data;
    std::vector<std::string> coordinates;
    float x, y, z;
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
            points.push_back(Point(x, y, z));
        }
    }

    return points;
}

int main() {
    std::vector<Point> points = read_file();
    const float epsilon = 0.75;
    const int min_points = 4;
    std::unordered_map<int, std::vector<Point>> clusters = create_cluster_map(points, epsilon, min_points);
    check(points);

    int sum = 0;
    for (auto map:clusters) {
        for (auto point:map.second) {
            std::cout << point.x << "," << point.y << "," << point.z << "," << point.cluster_id << "\n";
        }
    }

    return 0;
}
