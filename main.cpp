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

    static void bind(std::vector<Endpoint> &endpoints) {
        for (int i = 0; i < endpoints.size() / 2; i++) {
            endpoints[2 * i].other = &endpoints[2 * i + 1];
            endpoints[2 * i + 1].other = &endpoints[2 * i];
        }
    }


    static void print(const std::vector<Endpoint> &endpoints) {
        for (auto endpoint : endpoints) {
            std::cout << endpoint.x << " " << endpoint.y << " " << std::endl;
        }
    }


    static std::vector<Endpoint> find_intersections(std::vector<Endpoint> &endpoints) {
        bind(endpoints);
        std::sort(endpoints.begin(), endpoints.end());
        print(endpoints);
        return endpoints;
    }

private:
    class uniform_endpoint_distribution {

    public:
        uniform_endpoint_distribution(RealType a, RealType b) {
            dist = std::uniform_real_distribution<RealType>(a, b);
        }

        template<class Generator>
        Endpoint operator()(Generator &g) {
            Endpoint endpoint(dist(g), dist(g));
            count++;
            return endpoint;
        }

    private:
        unsigned long count = 0;
        std::uniform_real_distribution<RealType> dist;
    };


};

int main() {
    std::vector<SweepLines<double>::Endpoint> endpoints = SweepLines<double>::draw_endpoints(10, 0, 10);
    SweepLines<double>::find_intersections(endpoints);
    return 0;
}