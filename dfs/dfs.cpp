#include <array>
#include <deque>
#include <fstream>
#include <iostream>
#include <vector>

std::ifstream f{ "dfs.in" };
std::ofstream g{ "dfs.out" };

std::array<std::vector<int>, 100'001> g_graph{};
std::array<int, 100'001> g_mark{};
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

        g_graph[x].push_back(y);
    }
}

auto dfs(int const i, int const val) -> void
{
    g_mark[i] = val;

    for(auto v : g_graph[i]) {
        if(g_mark[v] == 0) {
            dfs(v, val);
        }
    }
}

auto main() noexcept -> int
{
    read_graph();

    int num_comp = 0;

    for(int i = 1; i <= g_num_nodes; ++i) {
        if(g_mark[i] == 0) {
            dfs(i, ++num_comp);
        }
    }

    g << num_comp;
}
