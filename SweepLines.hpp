#pragma once

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

        std::size_t other_id;
        bool is_right;

    public:

        RealType x;
        RealType y;

        Endpoint();

        Endpoint(RealType x, RealType y);

        bool operator<(const Endpoint &endpoint) const;

        bool operator!=(const Endpoint &endpoint) const;

        bool operator==(const Endpoint &endpoint) const;

        struct T_compare {
            bool operator() (const Endpoint &e1, const Endpoint &e2) const {
                return e1.y > e2.y;
            }
        };
    };

    friend class Endpoint;

    explicit SweepLines(std::vector<Endpoint> endpoints);

    static std::vector<Endpoint> draw_endpoints(std::size_t n, RealType min, RealType max);

    void print();

    void print_with_other();

    bool any_segments_intersect();

private:

    std::vector<Endpoint> endpoints;

    class uniform_endpoint_distribution {

    public:
        uniform_endpoint_distribution(RealType a, RealType b);

        template<class Generator>
        Endpoint operator()(Generator &g);

    private:
        std::uniform_real_distribution<RealType> dist;
    };

    void bind();

    bool intersect(Endpoint above, Endpoint below);

    RealType value_at(Endpoint endpoint, RealType x);

};

#include "SweepLines.tpp"