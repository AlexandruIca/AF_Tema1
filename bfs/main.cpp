#include <array>
#include <deque>
#include <fstream>
#include <iostream>
#include <vector>

std::ifstream f{ "bfs.in" };
std::ofstream g{ "bfs.out" };

std::array<std::vector<int>, 100001> g_graph{};
std::array<int, 100001> g_dist{};
std::deque<int> g_queue{};
int g_num_nodes = 0;
int g_start_node = 0;

void read_graph()
{
    int n = 0;
    int m = 0;
    int s = 0;

    f >> n >> m >> s;

    g_num_nodes = n;
    g_start_node = s;

    for(int i = 0; i < m; ++i) {
        int x = 0;
        int y = 0;

        f >> x >> y;

        g_graph[x].push_back(y);
    }
}

void bfs()
{
    while(!g_queue.empty()) {
        int const node = g_queue.front();

        for(auto const neighbor : g_graph[node]) {
            if(g_dist[neighbor] == -1) {
                g_queue.push_back(neighbor);
                g_dist[neighbor] = g_dist[node] + 1;
            }
        }

        g_queue.pop_front();
    }
}

int main()
{
    g_dist.fill(-1);
    read_graph();

    g_queue.push_back(g_start_node);
    g_dist[g_start_node] = 0;

    bfs();

    for(int i = 1; i <= g_num_nodes; ++i) {
        g << g_dist[i] << ' ';
    }
}
