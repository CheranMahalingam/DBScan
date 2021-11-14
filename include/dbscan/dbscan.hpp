#pragma once

#include <dbscan/point.hpp>
#include <dbscan/cluster.hpp>

#include <vector>

namespace dbscan {

class Dbscan {
public:
    Dbscan(std::vector<Point> const& points, const int min_points, const double epsilon);

    std::vector<int> RegionQuery(const int current_index);

    std::vector<int> ExpandCluster(const int current_index);

    void CreateClusters();

    std::vector<Point> points;

    std::vector<Cluster> clusters;

    const int min_points;

    const double epsilon;
};

}
