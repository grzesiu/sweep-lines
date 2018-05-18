template<typename RealType>
SweepLines<RealType>::Endpoint::Endpoint() {}

template<typename RealType>
SweepLines<RealType>::Endpoint::Endpoint(RealType x, RealType y) : x(x), y(y) {}

template<typename RealType>
bool SweepLines<RealType>::Endpoint::operator<(const Endpoint &endpoint) const {
    return (x < endpoint.x) ||
           (x == endpoint.x && is_right() < endpoint.is_right()) ||
           (x == endpoint.x && is_right() == endpoint.is_right() && y < endpoint.y);
}

template<typename RealType>
bool SweepLines<RealType>::Endpoint::operator!=(const Endpoint &endpoint) const {
    return other != endpoint.other;
}

template<typename RealType>
bool SweepLines<RealType>::Endpoint::operator==(const Endpoint &endpoint) const {
    return other == endpoint.other;
}

template<typename RealType>
bool SweepLines<RealType>::Endpoint::is_right() const {
    return x > other->x;
}


template<typename RealType>
std::vector<typename SweepLines<RealType>::Endpoint>
SweepLines<RealType>::draw_endpoints(unsigned long n, RealType min, RealType max) {

    std::vector<Endpoint> endpoints(n * 2);

    std::random_device rnd_device;
    std::mt19937 mersenne_engine(rnd_device());
    uniform_endpoint_distribution dist(min, max);

    auto gen = std::bind(dist, mersenne_engine);
    std::generate(std::begin(endpoints), std::end(endpoints), gen);

    return endpoints;
}

template<typename RealType>
void SweepLines<RealType>::print(const std::vector<Endpoint> &endpoints) {
    for (auto &endpoint : endpoints) {
        std::cout << endpoint.x << " " << endpoint.y << " " << std::endl;
    }
}

template<typename RealType>
bool SweepLines<RealType>::any_segments_intersect(std::vector<Endpoint> &endpoints) {
    print(endpoints);
    std::set<Endpoint> T;
    bind(endpoints);
    std::sort(endpoints.begin(), endpoints.end());
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

template<typename RealType>
void SweepLines<RealType>::bind(std::vector<Endpoint> &endpoints) {
    for (int i = 0; i < endpoints.size() / 2; i++) {
        endpoints[2 * i].other = &endpoints[2 * i + 1];
        endpoints[2 * i + 1].other = &endpoints[2 * i];
    }
}


template<typename RealType>
bool SweepLines<RealType>::intersect(Endpoint above, Endpoint below) {
    if (above.other->x < below.other->x) {
        return value_at(*below.other, above.other->x) >= above.other->y;
    } else {
        return value_at(*above.other, below.other->x) <= below.other->y;
    }
}

template<typename RealType>
RealType SweepLines<RealType>::value_at(Endpoint endpoint, RealType x) {
    RealType a = (endpoint.other->y - endpoint.y) / (endpoint.other->x - endpoint.x);
    return endpoint.y + a * (x - endpoint.x);
}

template<typename RealType>
SweepLines<RealType>::uniform_endpoint_distribution::uniform_endpoint_distribution(RealType a, RealType b) {
    dist = std::uniform_real_distribution<RealType>(a, b);
}

template<typename RealType>
template<typename Generator>
typename SweepLines<RealType>::Endpoint SweepLines<RealType>::uniform_endpoint_distribution::operator()(Generator &g) {
    return Endpoint(dist(g), dist(g));
}