#include <random>
#include <iostream>
#include <utility>
#include <functional>
#include <algorithm>

template<class RealType = double>
class uniform_pair_distribution {

public:
    uniform_pair_distribution(RealType a, RealType b) {
        dist = std::uniform_real_distribution<RealType>(a, b);
    }

    template<class Generator>
    std::pair<RealType, RealType> operator()(Generator &g) {
        return std::make_pair(dist(g), dist(g));
    }

private:
    std::uniform_real_distribution<RealType> dist;

};

std::vector<std::pair<double, double>> draw_lines(unsigned long n, double min, double max) {

    std::vector<std::pair<double, double>> lines(n);

    std::random_device rnd_device;
    std::mt19937 mersenne_engine(rnd_device());
    uniform_pair_distribution<double> dist(min, max);

    auto gen = std::bind(dist, mersenne_engine);
    std::generate(std::begin(lines), std::end(lines), gen);

    return lines;
}

int main() {
    std::vector<std::pair<double, double>> lines = draw_lines(10, 0, 10);
    for (auto i : lines) {
        std::cout << i.first << " " << i.second << std::endl;
    }

    return 0;
}