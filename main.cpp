#include "SweepLines.hpp"

int main() {
//    std::vector<SweepLines<double>::Endpoint> endpoints = SweepLines<double>::draw_endpoints(10, 0, 10);
    std::vector<SweepLines<double>::Endpoint> endpoints = {SweepLines<double>::Endpoint(0, 2),
                                                           SweepLines<double>::Endpoint(2, 0),
                                                           SweepLines<double>::Endpoint(0, 0),
                                                           SweepLines<double>::Endpoint(2, 2)};
    std::cout << SweepLines<double>::any_segments_intersect(endpoints) << std::endl;
    return 0;
}