#include <algorithm>
#include <functional>
#include <iostream>
#include <random>
#include <set>

template<class RealType = double>
class SweepLines {
public:

    class Endpoint {
        friend class SweepLines;

        RealType x;
        RealType y;
        Endpoint *other;

    public:
        Endpoint() {}

        Endpoint(RealType x, RealType y) :
                x(x), y(y) {}

        bool operator<(const Endpoint &endpoint) const {
            return (x < endpoint.x) ||
                   (x == endpoint.x && is_right() < endpoint.is_right()) ||
                   (x == endpoint.x && is_right() == endpoint.is_right() && y < endpoint.y);
        }

        bool operator!=(const Endpoint &endpoint) const {
            return other != endpoint.other;
        }

        bool operator==(const Endpoint &endpoint) const {
            return other == endpoint.other;
        }

        bool is_right() const {
            return x > other->x;
        }
    };


    static std::vector<Endpoint> draw_endpoints(unsigned long n, RealType min, RealType max) {

        std::vector<Endpoint> endpoints(n * 2);

        std::random_device rnd_device;
        std::mt19937 mersenne_engine(rnd_device());
        uniform_endpoint_distribution dist(min, max);

        auto gen = std::bind(dist, mersenne_engine);
        std::generate(std::begin(endpoints), std::end(endpoints), gen);

        return endpoints;
    }

    static void print(const std::vector<Endpoint> &endpoints) {
        for (auto &endpoint : endpoints) {
            std::cout << endpoint.x << " " << endpoint.y << " " << std::endl;
        }
    }

    static bool any_segments_intersect(std::vector<Endpoint> &endpoints) {
        std::set<Endpoint> T;
        bind(endpoints);
        std::sort(endpoints.begin(), endpoints.end());
        print(endpoints);
        for (auto &endpoint : endpoints) {
            if (endpoint.is_right()) {
                auto it = T.find(*endpoint.other);
                if (*it != *T.begin() &&
                    *it != *std::prev(T.end()) &&
                    intersect(*std::prev(it), *std::next(it))) {
                    return true;
                }
                T.erase(*it->other);
            } else {
                T.insert(endpoint);
                auto it = T.find(endpoint);
                if ((*it != *T.begin() &&
                     intersect(*std::prev(it), *it)) ||
                    (*it != *std::prev(T.end()) &&
                    intersect(*it, *std::next(it)))) {
                    return true;
                }
            }
        }
        return false;
    }

private:

    static void bind(std::vector<Endpoint> &endpoints) {
        for (int i = 0; i < endpoints.size() / 2; i++) {
            endpoints[2 * i].other = &endpoints[2 * i + 1];
            endpoints[2 * i + 1].other = &endpoints[2 * i];
        }
    }

    static bool intersect(Endpoint above, Endpoint below) {
        if (above.other->x < below.other->x) {
            return value_at(*below.other, above.other->x) >= above.other->y;
        } else {
            return value_at(*above.other, below.other->x) <= below.other->y;
        }
    }

    static RealType value_at(Endpoint endpoint, RealType x) {
        RealType a = (endpoint.other->y - endpoint.y) / (endpoint.other->x - endpoint.x);
        return endpoint.y + a * (x - endpoint.x);
    }

    class uniform_endpoint_distribution {

    public:
        uniform_endpoint_distribution(RealType a, RealType b) {
            dist = std::uniform_real_distribution<RealType>(a, b);
        }

        template<class Generator>
        Endpoint operator()(Generator &g) {
            return Endpoint(dist(g), dist(g));
        }

    private:
        std::uniform_real_distribution<RealType> dist;
    };
};

int main() {
//    std::vector<SweepLines<double>::Endpoint> endpoints = SweepLines<double>::draw_endpoints(10, 0, 10);
    std::vector<SweepLines<double>::Endpoint> endpoints = {SweepLines<double>::Endpoint(0, 2),
                                                           SweepLines<double>::Endpoint(2, 0),
                                                           SweepLines<double>::Endpoint(0, 0),
                                                           SweepLines<double>::Endpoint(2, 2)};
    std::cout << SweepLines<double>::any_segments_intersect(endpoints) << std::endl;
    return 0;
}