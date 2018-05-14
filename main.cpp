#include <random>
#include <iostream>
#include <utility>
#include <functional>
#include <algorithm>

template<class RealType = double>
class SweepLines {
public:

    struct Endpoint {
        RealType x;
        RealType y;
        unsigned long line_id;

        Endpoint() {};

        Endpoint(RealType x, RealType y, unsigned long line_id) :
                x(x), y(y), line_id(line_id) {}

        bool operator<(const Endpoint &other) const {
            return (x < other.x) ||
                   (x == other.x && line_id < other.line_id) ||
                   (x == other.x && line_id == other.line_id && y < other.y);
        }
    };


    static std::vector <Endpoint> draw_lines(unsigned long n, RealType min, RealType max) {

        std::vector <Endpoint> endpoints(n * 2);

        std::random_device rnd_device;
        std::mt19937 mersenne_engine(rnd_device());
        uniform_endpoint_distribution dist(min, max);

        auto gen = std::bind(dist, mersenne_engine);
        std::generate(std::begin(endpoints), std::end(endpoints), gen);

        return endpoints;
    }


    static void print(const std::vector <Endpoint> &lines) {
        for (auto i : lines) {
            std::cout << i.x << " " << i.y << " " << i.line_id << std::endl;
        }
    }


    static std::vector <Endpoint> find_intersections(std::vector <Endpoint> &lines) {
        std::vector <Endpoint> intersections;
        std::sort(lines.begin(), lines.end());
        return lines;
    }

private:
    class uniform_endpoint_distribution {

    public:
        uniform_endpoint_distribution(RealType a, RealType b) {
            dist = std::uniform_real_distribution<RealType>(a, b);
        }

        template<class Generator>
        Endpoint operator()(Generator &g) {
            return Endpoint(dist(g), dist(g), count++ % 2);
        }

    private:
        unsigned long count = 0;
        std::uniform_real_distribution <RealType> dist;
    };


};

int main() {
    std::vector <SweepLines<double>::Endpoint> lines = SweepLines<double>::draw_lines(10, 0, 10);
    lines = SweepLines<double>::find_intersections(lines);
    SweepLines<double>::print(lines);
    return 0;
}