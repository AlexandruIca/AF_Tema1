#include <algorithm>
#include <array>
#include <fstream>
#include <queue>
#include <vector>

constexpr auto max_num_nodes = 1001;
constexpr auto start_node = 1;

std::array<std::vector<int>, max_num_nodes> g_graph;
std::array<int, max_num_nodes> g_parent; // pentru a reconstrui drumul obtinut in BFS
std::array<std::array<int, max_num_nodes>, max_num_nodes> g_capacity;
int g_num_nodes = 0;

// BFS pentru a gasi drumul de ameliorare
// Pornind de la sursa iau toate muchiile care au fluxul curent strict mai mic decat capacitatea
auto bfs() -> int
{
    std::queue<int> nodes{};

    nodes.push(start_node);

    while(!nodes.empty()) {
        auto const current = nodes.front();
        nodes.pop();

        for(auto const neighbor : g_graph[current]) {
            if(g_parent[neighbor] == 0 && g_capacity[current][neighbor] > 0) {
                g_parent[neighbor] = current;
                nodes.push(neighbor);
            }
        }
    }

    return g_parent[g_num_nodes];
}

auto main() noexcept -> int
{
    std::ifstream f{ "maxflow.in" };
    std::ofstream g{ "maxflow.out" };

    int n = 0;
    int m = 0;

    f >> n >> m;

    g_num_nodes = n;

    for(int i = 1; i <= m; ++i) {
        int from = 0;
        int to = 0;
        int capacity = 0;

        f >> from >> to >> capacity;

        g_graph[from].push_back(to);
        g_capacity[from][to] = capacity;

        g_graph[to].push_back(from);
        g_capacity[to][from] = 0; // graful rezidual
    }

    int flux = 0;

    while(bfs() != 0) {
        for(auto const neighbor : g_graph[n]) {
            auto min_capacity = g_capacity[neighbor][n];

            // calculez capacitatea minima pornind de la destinatie pe drumul gasit cu BFS
            for(auto i = neighbor; i != start_node; i = g_parent[i]) {
                min_capacity = std::min(min_capacity, g_capacity[g_parent[i]][i]);
            }

            // pentru graful normal capacitatea scade, pentru cel rezidual creste
            for(auto i = neighbor; i != start_node; i = g_parent[i]) {
                g_capacity[g_parent[i]][i] -= min_capacity;
                g_capacity[i][g_parent[i]] += min_capacity;
            }

            // nu este acoperit de for-ul de mai sus
            g_capacity[neighbor][n] -= min_capacity;
            g_capacity[n][neighbor] += min_capacity;

            flux += min_capacity;
        }

        // reset pentru vectorul in care tin parintii, drumul se va construi de la zero data viitoare
        g_parent.fill(0);
    }

    g << flux << std::endl;
}
