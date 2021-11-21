#pragma once

#include <dbscan/dbscan.hpp>
#include <dbscan/point.hpp>

#include <tuple>
#include <vector>

namespace dbscan {

class Evaluate {
public:
    Evaluate();

    double AverageIntraClusterDistance(const Dbscan& scan);

    double AverageInterClusterDistance(const Dbscan& scan);

    double SilhouetteScore(const Dbscan& scan);

    std::tuple<double, double, int> TuneParams(const std::vector<Point>& points);
};

}
