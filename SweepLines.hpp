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

        Endpoint *other;

    public:

        RealType x;
        RealType y;

        Endpoint();

        Endpoint(RealType x, RealType y);

        bool operator<(const Endpoint &endpoint) const;

        bool operator!=(const Endpoint &endpoint) const;

        bool operator==(const Endpoint &endpoint) const;

        bool is_right() const;
    };

    static std::vector<Endpoint> draw_endpoints(std::size_t n, RealType min, RealType max);

    static void print(const std::vector<Endpoint> &endpoints);

    static bool any_segments_intersect(std::vector<Endpoint> &endpoints);

private:


    class uniform_endpoint_distribution {

    public:
        uniform_endpoint_distribution(RealType a, RealType b);

        template<class Generator>
        Endpoint operator()(Generator &g);

    private:
        std::uniform_real_distribution<RealType> dist;
    };

    static void bind(std::vector<Endpoint> &endpoints);

    static bool intersect(Endpoint above, Endpoint below);

    static RealType value_at(Endpoint endpoint, RealType x);

};

#include "SweepLines.tpp"