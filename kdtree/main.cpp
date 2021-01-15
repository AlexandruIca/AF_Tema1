#include <algorithm>
#include <array>
#include <fstream>
#include <iterator>
#include <tuple>
#include <vector>

constexpr int max_num = 2e5 + 1;
constexpr int start_node = 1;

int max_distance;
int num_nodes;

std::array<std::vector<int>, max_num> g_graph;
std::array<bool, max_num> g_visited;
std::array<int, max_num> g_height;
std::array<int, max_num> g_parent;
int answer = 0;

// parcurg cu dfs graful pornind de la 'node', retinand parintele fiecarui nod
auto dfs(int node) -> void
{
    g_visited[node] = true;

    for(auto const neighbor : g_graph[node]) {
        if(!g_visited[neighbor]) {
            g_parent[neighbor] = node;
            dfs(neighbor);
        }
    }

    // pentru nodul 'node', daca are tata si l-as lega cu parintele, ar avea distanta mai mare decat k?
    if(g_parent[node] != 0 && (g_height[node] + 1) + g_height[g_parent[node]] > max_distance) {
        // daca da, atunci muchia ar trebui stearsa, am o solutie
        ++answer;
        g_height[g_parent[node]] = std::min(g_height[node] + 1, g_height[g_parent[node]]);
    }
    else {
        // daca nu, atunci formez un kdtree si in parinte retin distanta cea mai mare pana la fiii sai la momentul
        // curent
        g_height[g_parent[node]] = std::max(g_height[node] + 1, g_height[g_parent[node]]);
    }
}

auto main() noexcept -> int
{
    std::ifstream f{ "kdtree.in" };
    std::ofstream g{ "kdtree.out" };

    f >> num_nodes >> max_distance;

    for(int i = 1; i < num_nodes; ++i) {
        int from = 0;
        int to = 0;

        f >> from >> to;

        g_graph[from].push_back(to);
        g_graph[to].push_back(from);
    }

    // mereu pornesc de la nodul 1
    dfs(start_node);

    g << answer << std::endl;
}
