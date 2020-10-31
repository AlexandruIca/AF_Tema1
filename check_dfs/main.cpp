#include <algorithm>
#include <iostream>
#include <vector>
using namespace std;

const int g_max = 1e5 + 5;

bool g_visited[g_max];
std::vector<int> g_graph[g_max];
int g_order[g_max];
std::vector<int> g_dfs_order;

void dfs(int start)
{
    g_dfs_order.push_back(start);
    g_visited[start] = true;

    for(auto node : g_graph[start]) {
        if(!g_visited[node]) {
            dfs(node);
        }
    }
}

int main()
{
    int n = 0;
    int m = 0;
    std::vector<int> permutation{};

    std::cin >> n >> m;

    permutation.reserve(n);

    for(int i = 0; i < n; ++i) {
        int x = 0;
        std::cin >> x;
        permutation.push_back(x);
        g_order[x] = i;
    }

    for(int i = 0; i < m; ++i) {
        int a = 0;
        int b = 0;
        std::cin >> a >> b;
        g_graph[a].push_back(b);
        g_graph[b].push_back(a);
    }

    for(int i = 1; i <= n; ++i) {
        std::sort(g_graph[i].begin(), g_graph[i].end(), [](int a, int b) { return g_order[a] < g_order[b]; });
    }

    dfs(1);
    std::cout << (permutation == g_dfs_order);
}
