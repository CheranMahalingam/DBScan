#pragma once

#include <cmath>

namespace dbscan {

class Point {
public:
    enum class PointState {
        unclassified,
        noise,
        classified
    };

    Point(double x, double y, double z);

    double EuclideanDistance(Point const& p) const;

    bool IsClassified() const;

    double x() const;

    double y() const;

    double z() const;

    PointState state;

private:
    double x_, y_, z_;
};

}
