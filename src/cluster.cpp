#include <dbscan/cluster.hpp>

#include <algorithm>

namespace dbscan {

Cluster::Cluster(std::vector<Point> const& points)
    : id_(current_id++), points(points) {}

Cluster::BoundingBox Cluster::ConstructBoundingBox() {
    double x_min, y_min, z_min = std::numeric_limits<double>::max();
    double x_max, y_max, z_max = std::numeric_limits<double>::min();

    for (auto point:points) {
        x_min = std::min(x_min, point.x());
        y_min = std::min(y_min, point.y());
        z_min = std::min(z_min, point.z());
        x_max = std::max(x_max, point.x());
        y_max = std::max(y_max, point.y());
        z_max = std::max(z_max, point.z());
    }

    Cluster::BoundingBox new_box(x_min, y_min, z_min, x_max, y_max, z_max);
    return new_box;
}

int Cluster::id() const {
    return id_;
}

int Cluster::current_id = 0;

std::ostream& operator<<(std::ostream& out, const Cluster& c) {
    for (auto point:c.points) {
        out << point.x() << "," << point.y() << "," << point.z() << "," << c.id() << "\n";
    }
    return out;
}

}
