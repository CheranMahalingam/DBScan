#include <dbscan/cluster.hpp>

namespace dbscan {

Cluster::Cluster(std::vector<Point> const& points)
    : id_(current_id++), points(points) {}

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
