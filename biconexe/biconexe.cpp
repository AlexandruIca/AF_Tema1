#include <algorithm>
#include <array>
#include <deque>
#include <fstream>
#include <iostream>
#include <stack>
#include <unordered_map>
#include <utility>
#include <vector>

#include <cstring>

std::ifstream f{ "biconex.in" };
std::ofstream g{ "biconex.out" };

constexpr int nmax = 100'005;

std::array<std::vector<int>, nmax> g_graph{};
std::array<std::vector<int>, nmax> g_biconexe{};
std::array<int, nmax> g_high{};
std::array<char, nmax> g_viz{};
std::array<int, nmax> g_level{};
std::array<int, nmax> g_dfs_sons{};
std::array<bool, nmax> g_critic{};
int g_num_nodes = 0;
int g_num_biconexe = 0;

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
        g_graph[y].push_back(x);
    }
}

auto dfs_critic(int const node) -> void
{
    g_viz[node] = 1;

    for(auto const vecin : g_graph[node]) {
        if(g_viz[vecin]) {
            g_high[node] = std::min(g_high[node], g_level[vecin]);
        }
        else {
            g_level[vecin] = g_level[node] + 1;
            g_dfs_sons[node]++;
            dfs_critic(vecin);

            if(g_high[vecin] >= g_level[node]) {
                g_critic[node] = true;
            }

            g_high[node] = std::min(g_high[node], g_high[vecin]);
        }
    }
}

auto split_biconexe(int) -> void;
auto dfs_biconexe(int, int) -> void;

auto dfs_biconexe(int const node, int const index_bic) -> void
{
    g_viz[node] = 1;
    g_biconexe[index_bic].push_back(node);

    for(auto const vecin : g_graph[node]) {
        if(g_viz[vecin]) {
            continue;
        }

        if(g_critic[vecin]) {
            g_biconexe[index_bic].push_back(vecin);
            split_biconexe(vecin);
        }
        else {
            dfs_biconexe(vecin, index_bic);
        }
    }
}

auto split_biconexe(int const node) -> void
{
    g_viz[node] = 1;

    for(auto const vecin : g_graph[node]) {
        if(g_viz[vecin]) {
            continue;
        }

        g_biconexe[++g_num_biconexe].push_back(node);

        if(g_critic[vecin]) {
            g_biconexe[g_num_biconexe].push_back(vecin);
            split_biconexe(vecin);
        }
        else {
            dfs_biconexe(vecin, g_num_biconexe);
        }
    }
}

auto main() noexcept -> int
{
    read_graph();

    for(int i = 1; i <= g_num_nodes; ++i) {
        g_high[i] = 1e9;
    }

    dfs_critic(1);
    g_critic[1] = (g_dfs_sons[1] > 1);
    g_viz.fill(0);

    for(int i = 1; i <= g_num_nodes; ++i) {
        if(g_critic[i]) {
            split_biconexe(i);
            break;
        }
    }

    g << g_num_biconexe << '\n';
    for(int i = 1; i <= g_num_biconexe; ++i) {
        for(auto elem : g_biconexe[i]) {
            g << elem << ' ';
        }
        g << '\n';
    }
}
