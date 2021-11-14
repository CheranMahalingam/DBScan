#pragma once

#include <dbscan/point.hpp>

#include <iostream>
#include <vector>

namespace dbscan {

class Cluster {
public:
    struct BoundingBox {
        double x_min, y_min, z_min;
        double x_max, y_max, z_max;
        BoundingBox(double x_min, double y_min, double z_min, double x_max, double y_max, double z_max)
            : x_min(x_min), y_min(y_min), z_min(z_min), x_max(x_max), y_max(y_max), z_max(z_max) {} 
    };

    Cluster(std::vector<Point> const& points);

    BoundingBox ConstructBoundingBox();

    int id() const;

    std::vector<Point> points;

    static int current_id;

    friend std::ostream& operator<<(std::ostream& out, const Cluster& c);

private:
    int id_;
};

}
