#include <array>
#include <bitset>
#include <cstddef>
#include <cstdint>
#include <deque>
#include <fstream>
#include <iostream>
#include <limits>
#include <utility>
#include <vector>

namespace {

using i64 = std::int64_t;

constexpr std::size_t max_num_nodes = 50'001;
constexpr auto inf = 1e9;

using neighbor = std::pair<i64, i64>;

} // namespace

#define /* neighbor. */ to first
#define /* neighbor. */ cost second

auto main() -> int
{
    std::ifstream f{ "bellmanford.in" };
    std::ofstream g{ "bellmanford.out" };

    i64 n = 0;
    i64 m = 0;

    std::array<std::vector<neighbor>, max_num_nodes> graph{};
    std::array<i64, max_num_nodes> distance{};
    std::deque<i64> nodes{};
    std::vector<i64> to_visit{};
    std::bitset<max_num_nodes> visited{};

    f >> n >> m;

    for(i64 i = 1; i <= m; ++i) {
        i64 node_from = 0;
        i64 node_to = 0;
        i64 node_cost = 0;

        f >> node_from >> node_to >> node_cost;

        graph[node_from].emplace_back(node_to, node_cost);
    }

    distance.fill(inf);
    distance[1] = 0;
    nodes.push_back(1);

    for(i64 i = 1; i <= n; ++i) {
        visited.reset();

        while(not nodes.empty()) {
            auto const current = nodes.front();

            for(auto next : graph[current]) {
                if(distance[current] + next.cost < distance[next.to]) {
                    distance[next.to] = distance[current] + next.cost;

                    if(not visited.test(next.to)) {
                        to_visit.push_back(next.to);
                    }

                    visited.set(next.to);
                }
            }

            nodes.pop_front();
        }

        nodes.assign(to_visit.begin(), to_visit.end());
        to_visit.clear();
    }

    if(not nodes.empty()) {
        g << "Ciclu negativ!" << std::endl;
        return EXIT_SUCCESS;
    }

    for(i64 i = 2; i <= n; ++i) {
        g << distance[i] << ' ';
    }
}
