#include <algorithm>
#include <array>
#include <fstream>
#include <iterator>
#include <limits>
#include <queue>
#include <tuple>
#include <vector>

constexpr int inf = std::numeric_limits<int>::max();
constexpr int max_num_nodes = 50'001;
constexpr int start_node = 1;

std::vector<int> g_dist(max_num_nodes, inf);
std::array<std::vector<std::pair<int, int>>, max_num_nodes> g_graph;

#define /* g_graph[node]. */ value first
#define /* g_graph[node]. */ weight second

auto dijkstra() -> void
{
    auto comp = [](int const x, int const y) noexcept -> bool { return g_dist[x] > g_dist[y]; };
    std::priority_queue<int, std::vector<int>, decltype(comp)> nodes{ comp };
    std::array<bool, max_num_nodes> is_in_queue{};

    g_dist[start_node] = 0;
    is_in_queue.fill(false);
    is_in_queue[start_node] = true;
    nodes.emplace(start_node);

    while(!nodes.empty()) {
        int const current = nodes.top();

        for(auto const& neighbor : g_graph[current]) {
            if(g_dist[current] + neighbor.weight < g_dist[neighbor.value]) {
                g_dist[neighbor.value] = g_dist[current] + neighbor.weight;

                if(!is_in_queue[neighbor.value]) {
                    nodes.emplace(neighbor.value);
                    is_in_queue[neighbor.value] = true;
                }
            }
        }

        nodes.pop();
        is_in_queue[current] = false;
    }
}

auto main() noexcept -> int
{
    std::ifstream f{ "dijkstra.in" };
    std::ofstream g{ "dijkstra.out" };

    int num_nodes = 0;
    int num_arcs = 0;

    f >> num_nodes >> num_arcs;

    for(int i = 1; i <= num_arcs; ++i) {
        int from = 0;
        int to = 0;
        int cost = 0;

        f >> from >> to >> cost;

        g_graph[from].emplace_back(to, cost);
    }

    dijkstra();

    for(int i = start_node + 1; i <= num_nodes; ++i) {
        g << ((g_dist[i] == inf) ? 0 : g_dist[i]) << ' ';
    }
}
