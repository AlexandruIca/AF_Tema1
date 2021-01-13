#include <array>
#include <fstream>
#include <iostream>
#include <vector>

std::ifstream f{ "sortaret.in" };
std::ofstream g{ "sortaret.out" };

std::array<std::vector<int>, 50001> g_graph{};
std::array<bool, 50001> g_visited{};
int g_num_nodes = 0;

auto read_graph() -> void
{
    int n = 0;
    int m = 0;

    f >> n >> m;

    g_num_nodes = n;

    for(int i = 0; i < m; ++i) {
        int x = 0;
        int y = 0;

        f >> x >> y;

        g_graph[y].push_back(x);
    }
}

auto dfs(int i) -> void
{
    if(g_visited[i]) {
        return;
    }

    g_visited[i] = true;

    for(auto const node : g_graph[i]) {
        dfs(node);
    }

    g << i << ' ';
}

auto main() noexcept -> int
{
    read_graph();

    for(int i = 1; i <= g_num_nodes; ++i) {
        dfs(i);
    }
}
