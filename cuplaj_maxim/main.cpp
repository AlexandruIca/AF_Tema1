#include <algorithm>
#include <array>
#include <fstream>
#include <limits>
#include <vector>

constexpr auto max_num_nodes = 10'000;

std::array<std::vector<int>, max_num_nodes> g_graph;
std::array<bool, max_num_nodes> g_visited;
std::array<int, max_num_nodes> g_tied_to;

// Intoarce 'true' daca pornind de la start, se poate gasi un nod cu care se poate face legatura
auto dfs(int const start) noexcept -> bool
{
    // Pentur fiecare vecin al nodului dat
    for(auto const neighbor : g_graph[start]) {
        if(!g_visited[neighbor]) {
            g_visited[neighbor] = true;

            // - Nu e legat cu nimeni? Am gasit o legatura.
            // - Vecinul este legat cu cineva, dar daca pornim de la nodul cu care e legat vecinul, putem gasi un
            //   nod liber? Daca da, am gasit o legatura.
            if(g_tied_to[neighbor] < 0 || dfs(g_tied_to[neighbor])) {
                g_tied_to[neighbor] = start;
                return true;
            }
        }
    }

    return false;
}

auto main() noexcept -> int
{
    std::ifstream f{ "cuplaj.in" };
    std::ofstream g{ "cuplaj.out" };

    int n = 0;
    int m = 0;
    int num_edges = 0;

    f >> n >> m >> num_edges;

    for(int i = 0; i < num_edges; ++i) {
        int from = 0;
        int to = 0;

        f >> from >> to;
        // Tin vecinii de la 'dreapta' la 'stanga'
        g_graph[to - 1].push_back(from - 1);
    }

    g_tied_to.fill(-1);

    int max_match = 0;

    for(int right = 0; right < m; ++right) {
        g_visited.fill(false);

        // Daca se poate gasi o legatura de la nodul curent, adaugam la cuplaj
        if(dfs(right)) {
            ++max_match;
        }
    }

    g << max_match << std::endl;

    for(int i = 0; i < n; ++i) {
        if(g_tied_to[i] >= 0) {
            g << i + 1 << ' ' << g_tied_to[i] + 1 << std::endl;
        }
    }
}
