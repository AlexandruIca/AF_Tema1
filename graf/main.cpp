#include <array>
#include <deque>
#include <fstream>
#include <iostream>
#include <set>
#include <unordered_map>
#include <vector>

std::ifstream f{ "graf.in" };
std::ofstream g{ "graf.out" };

std::array<std::vector<int>, 7'501> g_graph{};

using dist_t = std::array<int, 7'501>;

dist_t g_dist_start{}; // distances starting from the first node
dist_t g_dist_end{};   // distances starting from the last node
int g_num_nodes = 0;
int g_start_node = 0;
int g_end_node = 0;

enum class kind
{
    start,
    end
};

auto read_graph() -> void
{
    int n = 0;
    int m = 0;
    int s = 0;
    int e = 0;

    f >> n >> m >> s >> e;

    g_num_nodes = n;
    g_start_node = s;
    g_end_node = e;

    for(int i = 0; i < m; ++i) {
        int x = 0;
        int y = 0;

        f >> x >> y;

        g_graph[x].push_back(y);
        g_graph[y].push_back(x);
    }
}

auto bfs(int const start_node, kind const k) -> void
{
    dist_t& d = (k == kind::start) ? g_dist_start : g_dist_end;
    std::deque<int> queue{};
    std::array<bool, 7'501> visited{};

    visited.fill(false);
    queue.push_back(start_node);
    d[start_node] = 0;

    while(!queue.empty()) {
        int const node = queue.front();

        visited[node] = true;

        for(auto const v : g_graph[node]) {
            if(!visited[v]) {
                d[v] = d[node] + 1;
                queue.push_back(v);
            }
        }

        queue.pop_front();
    }
}

auto main() noexcept -> int
{
    read_graph();

    bfs(g_start_node, kind::start);
    bfs(g_end_node, kind::end);

    std::set<int> final_nodes{};

    final_nodes.insert(g_start_node);
    final_nodes.insert(g_end_node);

    std::unordered_map<int, std::set<int>> dist_level{};

    for(int i = 1; i <= g_num_nodes; ++i) {
        if(g_dist_start[i] + g_dist_end[i] == g_dist_start[g_end_node]) {
            dist_level[g_dist_start[i]].insert(i);
        }
    }

    for(int i = 1; i <= g_dist_start[g_end_node]; ++i) {
        if(dist_level[i].size() == 1) {
            final_nodes.insert(*(dist_level[i].begin()));
        }
    }

    g << final_nodes.size() << '\n';

    for(int const n : final_nodes) {
        g << n << ' ';
    }
}
