#pragma once

#include <dbscan/point.hpp>

#include <iostream>
#include <vector>

namespace dbscan {

class Cluster {
public:
    Cluster(std::vector<Point> const& points);

    int id() const;

    std::vector<Point> points;

    static int current_id;

    friend std::ostream& operator<<(std::ostream &out, const Cluster &c);

private:
    int id_;
};

}
