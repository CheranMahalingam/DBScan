#include <dbscan/point.hpp>

namespace dbscan {

Point::Point(double x, double y, double z)
    : x_(x), y_(y), z_(z), state(PointState::unclassified) {}

double Point::EuclideanDistance(Point const& p) const {
    return std::pow(std::pow(x() - p.x(), 2) + std::pow(y() - p.y(), 2) + std::pow(z() - p.z(), 2), 0.5);
}

bool Point::IsClassified() const {
    return state == PointState::classified; 
}

double Point::x() const {
    return x_;
}

double Point::y() const {
    return y_;
}

double Point::z() const {
    return z_;
}

}
