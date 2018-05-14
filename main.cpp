#include <random>
#include <iostream>
#include <utility>
#include <functional>
#include <algorithm>


std::vector<std::pair<double, double>> draw_lines(unsigned long n, double min, double max) {

    std::vector<std::pair<double, double>> lines(n);

    std::random_device rnd_device;
    std::mt19937 mersenne_engine(rnd_device());
    std::uniform_real_distribution<double> dist(min, max);

    auto gen = std::bind(dist, mersenne_engine);
    std::vector<int> vec(10);
    std::generate(std::begin(vec), std::end(vec), gen);

    for (auto i : vec) {
        std::cout << i << " ";
    }

    return lines;

}

int main() {
    draw_lines(10, 0, 10);
    return 0;
}